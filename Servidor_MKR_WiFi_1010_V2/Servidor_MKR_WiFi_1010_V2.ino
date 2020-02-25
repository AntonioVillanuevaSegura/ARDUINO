/*
 Antonio Villanueva Segura
 Servidor Wifi con activacion de PINs O Leds  tarjeta MKR WiFi 1010
 https://content.arduino.cc/assets/Pinout-MKRwifi1010_latest.png
 Crea un servidor Web , donde podemos activar diferentes reles 0-12 ,desde un
 navegador , por el puerto serie nos reporta informacion de la conexion
 El modelo de tarjeta de Rele es Relay Module HW-316
 https://www.iconshock.com/
 */
 
//**********************************************************************************************
//Configuracion de este programa valor de IP , nombre de SSID, password , retardo ...
#include "configuracion.h"

#include <SPI.h>
#include <WiFiNINA.h>
#include "salidas.h" //Funciones para la gestion de las salida ,LEDs
#include "pagina.h" //Gestion de la pagina WEB , botones

//Recupera el nombre del servidor SSID y el password wifi
char ssid[] = SECRET_SSID;        // nombre servidor SSID
char pass[] = SECRET_PASS;    //  pasword 
int keyIndex = 0;                // Numero de indice (key index) para tu red (solo en WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);//Servidor en el puerto 80

//**********************************************************************************************

void setup() {
  //Inicializa y abre el puerto serie a 9600 bps
  Serial.begin(9600);
  while (!Serial) {//Eliminar si no queremos puerto serie 
    ;//Espera hasta que tengamos una conexion serie por el puerto USB 
  }
  
  #ifdef SERVIDOR
    Serial.println("Servidor Web -Tarjeta como punto de acceso -");//DEBUG
  #else
    Serial.println("Nos conectamos a un router");
  #endif     
  
  //configura_salidas();//Configura los PINs de salida 0 ..12 p.e 
  configura_salidas(PINSSS);//Configura los PINs de salida 0 ..12 p.e 
  //  Verifica el modulo Wifi 
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("La comunicacion con el modulo Wifi no funciona !");
    // No se continua
    while (true);
  }
 
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Actualice el firmware WIFI a la ultima version S");
  }

  #ifdef SERVIDOR
    //Direccion IP por defecto ,recupera del #define IP=192.168.6.1
    WiFi.config(IPAddress(IP));
  #else
    //Conecta con un router SSID y PASSword
     WiFi.begin(SECRET_SSID, SECRET_PASS);//Conecta al router con el SSID y el PWD
  #endif

  #ifdef SERVIDOR  
    // Imprime el nombre de la red  (SSID);
    Serial.print("Creando punto de acceso : ");
    Serial.println(ssid);
  #else
     Serial.print("Servidor Web en IP ");
    
  #endif    

  //Creada open network .Cambiar esta linea si quieres crear una red WEP ...
  #ifdef SERVIDOR
    status = WiFi.beginAP(ssid, pass);
    if (status != WL_AP_LISTENING) {
      Serial.println("Error en la creacion del access point");
      // don't continue
      while (true);//Bucle infinito
    }
  #endif
  // Espera X segundos antes de la conexion , 10000=10 segundos
  delay(RETARDO);

  // Arranca el servidor web en el puerto 80
  server.begin();

  //Estas conectado imprime el status
  printWiFiStatus();
}
//**********************************************************************************************

void loop() {//Bucle principal 
  #ifdef SERVIDOR
    // COmpara el estado anterior con el actual 
    if (status != WiFi.status()) {
      //Si ha cambiado , actualizamos la variable estado 
      status = WiFi.status();
  
      if (status == WL_AP_CONNECTED) {
        // Dispositivo conectado al access point AP 
        Serial.println("Dispositivo conectado al AP");
      } else {
        // Dispositivo desconectado del AP ,volvemos al modo escucha 
        Serial.println("Dispositivo desconectado del AP");
      }
    }
  #endif
  
  WiFiClient client = server.available();   // Espera clientes disponibles 

  if (client) {                             // Si hay un nuevo cliente
    Serial.println("Nuevo cliente");        // imprime mensaje por el puerto serie 
    String currentLine = "";                // Crea una cadena  String para guardar los datos del cliente 
    while (client.connected()) {            // Queda en bucle mientras el cliente este conectado 
      if (client.available()) {             // Hay cliente ,datos , bytes para leer del cliente ? 
        char c = client.read();             // Entonces leemos un dato un caracter char
        //Serial.write(c);                    // imprime en el puerto serie el dato leido
        if (c == '\n') {                    // ha llegado al final?,fin de linea \n ?
          //Si la linea esta vacia , "blanca", obtenemos dos caractares en una linea
          //Es el final de la solicitud HTTP del cliente , entonces enviamos una respuesta
          
          if (currentLine.length() == 0) {
            
            paginaWeb(client);// ofrece la pagina WEB al cliente

            break;// Salir del bucle que muestra la pagina web
          }else {
            currentLine = "";//Si tenemos nueva linea \n ,limpiamos la linea actual currentLine 
          }
        }
        else if (c != '\r') {    // Si tenemos agun caracter diferente al retorno de carro '\r'
          currentLine += c;      // Escribe el nuevo caracter(char) la linea corriente ,currentLine
        }

        //------------------------------------------------------------------------------------------------------------------------
        // Analizamos la respuesta del cliente en la pagina WEB . Termina con "PIN" , recupera el numero de pin o LED
        //https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Referer

        //Invierte el estado de una salida
        if (currentLine.endsWith("PIN")&& currentLine.indexOf("http")<0){//Busca la palabra clave PIN y http
            Serial.println("LINEA org= "+currentLine); 
            currentLine.remove (currentLine.indexOf('_'));//Busca caracter _ en la linea ,elimina el resto  
            currentLine.remove (0,currentLine.indexOf('/')+1);//Busca caracter / en la linea ,elimina el resto                                          
            digitalWrite( currentLine.toInt(),! digitalRead(currentLine.toInt()));//Invierte el estado 
            currentLine="";//Limpia la linea .
        }
        
        //------------------------------------------------------------------------------------------------------------------------        
      }
    }
    // Cerrar la conexion
    client.stop();
    Serial.println("cliente desconectado");
  }
}

//**********************************************************************************************

void printWiFiStatus() {
  //Muestra ,  por el puerto serie  la SSID de la red , donde nos conectamos
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Muestra la IP en la Wifi
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Muestra la IP donde debe conectarse el navegador 
  Serial.print(" Para ver esta pagina en accion abrir en un navegador esta direccion http://");
  Serial.println(ip);

}
