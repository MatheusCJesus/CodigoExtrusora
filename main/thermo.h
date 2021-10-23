/* 
--------------------------------------------------------------------------------
  Biblioteca para controlar os drivers de thermopar
  Placa: v1.0
--------------------------------------------------------------------------------
  Autor: Matheus Cerqueira de Jesus
  Data: 13 de Agosto de 2021
  Bolsista FAPESP
--------------------------------------------------------------------------------
*/

#include "definition.h"
#include "max6675.h"

  // Instânciação dos objetos da classe MAX6675

  MAX6675 thermoN(SCK_1, CS_1, SO_1); // Termopar 1: Nozzle
  MAX6675 thermo2(SCK_2, CS_2, SO_2); // Termopar 2
  MAX6675 thermo3(SCK_3, CS_3, SO_3); // Termopar 3
  MAX6675 thermo4(SCK_4, CS_4, SO_4); // Termopar 4
  MAX6675 thermo5(SCK_5, CS_5, SO_5); // Termopar 5
  MAX6675 thermo6(SCK_6, CS_6, SO_6); // Termopar 6

void define_pwm_res() {

  DDRH |= (1 << DDH4);  // pinMode(7, OUTPUT);

  TCCR4A |= (1 << WGM41);
  TCCR4A |= (1 << WGM40);
  TCCR4A |= (1 << COM4B1);
  TCCR4B &= ~(1 << CS42);

}

void pwm_res(float pwm) {

  float pwm_8bits = ( 1024 * pwm ) / 100;

    OCR4B = uint16_t(pwm_8bits);

}

float current_res1() { // Função para calcular a corrente no ramo 1 de resistências

  float voltage = 0.0;
  float i_res1 = 0.0;
  uint16_t sensor_value = 0;

  sensor_value = analogRead(A8);

  voltage = DIV_VOLTAGE * sensor_value;

  i_res1 = voltage / 0.1;

  return i_res1;

}

float current_res2() { // Função para calcular a corrente no ramo 2 de resistências

  float voltage = 0.0;
  float i_res2 = 0.0;
  uint16_t sensor_value = 0;

  sensor_value = analogRead(A9);

  voltage = DIV_VOLTAGE * sensor_value;

  i_res2 = voltage / 0.1;

  return i_res2;

}
