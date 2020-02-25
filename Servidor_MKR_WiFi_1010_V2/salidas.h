#ifndef _SALIDAS_
#define _SALIDAS_
#import <Arduino.h> 
#define N_SALIDAS 12
//A0 to A6 ==D15 to D21
//uint8_t PINSSS[]={15,16,17,18,19,20,21,0,1,2,3,4,5,6,7,8,9,10};//A0-A6 and D0-D10

void configura_salidas();//Configura los PINs D0-D_NSALIDAS  como salidas
void configura_salidas(uint8_t pins[]);//Configura  los PINS como salidas
#endif
