#include "salidas.h"
//Se puede utilizar la configuracion de salidas digitales 0-11 o una version especificando las salidas utilizadas 

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
