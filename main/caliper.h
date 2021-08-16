/* 
--------------------------------------------------------------------------------
  Biblioteca para aquisição de dados de paquímetro digital
  Placa: v1.0
--------------------------------------------------------------------------------
  Autor: Matheus Cerqueira de Jesus
  Data: 22 de Junho de 2021
  Bolsista FAPESP
--------------------------------------------------------------------------------
*/
#include "definition.h"

static const uint8_t cycleTime = 32;
volatile byte state = LOW;

float finalValue = 0;

void Set_INPUT_pins() {

  DDRE &= ~(1 << DATAPIN_PAQ); // pinMode(DATAPIN_PAQ, INPUT);
  DDRE &= ~(1 << CLKPIN_PAQ);  // pinMode(CLKPIN_PAQ, INPUT);

}

void decode(){

  // Declaração de variáveis locais
   unsigned char dataIn, sign; // dataIn <- Valor lido do pino de informação do paquímetro.
                               // sign <- Sinal do valor medido (+ | -).
   
   uint16_t value = 0;

   unsigned long now, lastInterrupt; // Variaáveis para controle de tempo.
   uint8_t currentBit = 0;           // Variável de controle de bits de comunicação do paquímetro.

   dataIn = digitalRead(DATAPIN_PAQ);
   now = millis();
   
   if((now - lastInterrupt) > cycleTime)
   {
     finalValue = (value * sign) / 100.00;
     currentBit = 0;
     value = 0;
     sign = 1;
   } 
   else if (currentBit < 16 )
   {
     if (dataIn == 0)
     {
       if (currentBit < 16) {
          value |= (1 << currentBit);
       }        
     }

     currentBit++;
     
   }
   else {
          if (currentBit == 20 && dataIn == 0) {
          sign = -1;
       }
       currentBit++;
   }
   
    lastInterrupt = now;
}

float getFinalValue() {

  return finalValue;

}

void Set_EXTERNAL_INTERRUPT() {
/* Configura interrupção externa nos registadores como borda de
   subida para o pino de clock do paquímetro (D3) (CLKPIN_PAQ) */

  EICRB |= (1 << ISC50);
  EICRB |= (1 << ISC51);

  EIMSK |= (1 << INT5);

}

 ISR(INT5_vect){ // Função de interrupção.
   //decode();
  state = ~state;
  digitalWrite(LED_BUILTIN, ~state);
}