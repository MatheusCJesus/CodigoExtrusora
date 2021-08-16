
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

#include "caliper.h"
#include "thermo.h"
#include "timerEvent.h"
#include "stepMotor.h"

/* ------------- Fim das definições ------------- */

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Seta a valocidade da comunicação serial em 9600 baud/s

  define_pwm(); // Define os pinos D11 e D46 como saída de PWM.

  Set_INPUT_pins();

  pinMode(LED_BUILTIN, OUTPUT);

  Set_EXTERNAL_INTERRUPT();

}

void loop() {
  // put your main code here, to run repeatedly:
   
  delay(500);

  if (display_flag) {
    
    Serial.println(thermoN.readCelsius());
    Serial.println(thermo2.readCelsius());
    Serial.println(thermo3.readCelsius());
    Serial.println(thermo4.readCelsius());
    Serial.println(thermo5.readCelsius());
    Serial.println(thermo6.readCelsius());

  }
  
}
