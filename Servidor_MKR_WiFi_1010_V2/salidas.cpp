#include "salidas.h"
uint8_t PINSSS[]={15,16,17,18,19,20,21,0,1,2,3,4,5,6,7,8,9,10};//A0-A6 and D0-D10
//**********************************************************************************************
void configura_salidas(){//Configura los PINs del 0-7 como salidas , gestion de LEDs o Reles
  //A0 to A6 ==D15 to D21
  for (uint8_t pin = 0;pin <N_SALIDAS; pin++) {
     pinMode(pin, OUTPUT);
  }

}
//**********************************************************************************************
void configura_salidas(uint8_t pins[]){//Configura ciertos PINS como salidas , gestion de LEDs o Reles
  //A0 to A6 ==D15 to D21
  for (uint8_t index = 0;index <sizeof(pins) / sizeof(pins[0]); index++) {
     pinMode(pins[index], OUTPUT);
  }

}
