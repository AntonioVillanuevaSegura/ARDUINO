/*
 * Pagina WeEB del servidor web Arduino, MKR WiFi 1010
 */
#include "pagina.h"
#include "salidas.h"
void paginaWeb(WiFiClient client){
    //Respuesta http al cliente
  bool estado;//Lee el estado de una salida 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  
  //Página web en formato HTML
  client.println("<html>");
  client.println("<head>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h1 align='center'>ICARO</h1><h2 align='center'>Servidor web control salidas</h2>");


  client.println("<div style='text-align:center;'>");//Alineacion de botones o grupos 
  //Crea botones .parametros se envian a traves de ? location.href
  for (uint8_t pin=0;pin<N_SALIDAS;pin++){//Crea los elementos para Encender/Apagar los LEDS con los numeros
    estado=digitalRead(pin); //En que estado la salida 0 o 1 
    //client.println("<div style='text-align:center;'>");


      if (!estado){//Dependiendo del estado de la salida muestra un boton ROJO o VERDE
        client.println("<button onClick=location.href=\"/"+String(pin)+"_PIN"+"\" style='margin:auto;background-color: #24A807;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:200px;height: 80px;'>");
      }else{
        client.println("<button onClick=location.href=\"/"+String(pin)+"_PIN"+"\" style='margin:auto;background-color: #BA0B25;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:200px;height: 80px;'>");
      }
      client.println("<font size=\"+4\"> ");
      client.println( !estado ? "ON  "+String(pin) : "OFF  "+String(pin) );//Texto en boton depende del estado de la salida
      client.println("</font>");    
      client.println("</button>");

    if ( ((pin+1)%4)==0){//Agrupa botones por grupo de 4 luego salta la linea detecta 4 8 12 
      client.println("<br /><br />");//Salto de linea
    }

    client.println("</b></body>");
    client.println("</html>");
    client.println();//FIN HTTP    
  }
  
//  break;
}
