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

static const int cycleTime = 32;

float finalValue = 0;

void decodee(){

  // Declaração de variáveis locais
   unsigned char dataIn, sign; // dataIn <- Valor lido do pino de informação do paquímetro
                               // sign <- Sinal do valor medido.
   
   uint16_t value = 0;         // Valor decímetros 

   unsigned long now, lastInterrupt;
   uint8_t currentBit = 0;

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
