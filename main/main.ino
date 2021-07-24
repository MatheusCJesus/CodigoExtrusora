
/* 
--------------------------------------------------------------------------------
  Algoritmo para controlar todo o sistema da máquina extrusora
  Placa: v1.0
--------------------------------------------------------------------------------
  Autor: Matheus Cerqueira de Jesus
  Data: 22 de Junho de 2021
  Bolsista FAPESP
--------------------------------------------------------------------------------
*/
#include "Arduino.h"
#include "definition.h"
#include "stepMotor.h"
#include "caliper.h"

int incomingByte;

/* ------------- Fim das definições ------------- */
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Seta a valocidade da comunicação serial em 9600 baud/s
  
  define_pwm(); // Chama a função que define os pinos x e x como saída de PWM
  

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available() > 0) {

    incomingByte = Serial.read();

    rpm_motor(incomingByte, 10);

  }

}
