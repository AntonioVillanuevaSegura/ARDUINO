/*
 * Parametros de configuracion
 */

//Si queremos que actue como un servidor WIFI independiente
//Si por el contrario queremos que se conecte a un router , poner en comentario //
//#define SERVIDOR


//IP del servidor wifi independiente si se utiliza, ip para navegador
#define IP 192,168,6,1

//Nombre y clave del servidor WIFI (o del acceso al router)
#define SECRET_SSID "Bbox-04140A3E"
#define SECRET_PASS "137E313A722D2463D11F17AD5AAFF1"
  
//Retardo para iniciar
#define RETARDO 1000

//Pins utilizados como salidas para nuestras 3 tarjetas de reles
uint8_t PINSSS[]={15,16,17,18,19,20,21,0,1,2,3,4,5,6,7,8,9,10};//A0-A6 and D0-D10
