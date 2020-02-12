# Arduino

 Test del MKR_WiFi_1010  como servidor wifi para controlar salidas.
 
Creamos un servidor WEB wifi con la IP 192,168,6,1  o se puede conectar a un router y obtener una IP
, puerto 80
, SSID del servidor es icaro , (si MKR_WIFI_1010 hace directamente de servidor)
, password 123456789 
.Podemos cambiar esta configuracion en el fichero configuracion.h

Las salidas que controlamos van de 0 a 11 fichero salidas.h #define N_SALIDAS 12 

La pagina web se crea desde el fichero pagina.cpp

![alt text](https://github.com/AntonioVillanuevaSegura/Servidor_MKR_WiFi_1010/blob/master/doc/photo_2020-01-29_13-14-18.jpg)

