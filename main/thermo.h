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

  MAX6675 thermo1(SCK_1, CS_1, SO_1); // Termopar 1
  MAX6675 thermo2(SCK_2, CS_2, SO_2); // Termopar 2
  MAX6675 thermo3(SCK_3, CS_3, SO_3); // Termopar 3
  MAX6675 thermo4(SCK_4, CS_4, SO_4); // Termopar 4
  MAX6675 thermo5(SCK_5, CS_5, SO_5); // Termopar 5
  MAX6675 thermo6(SCK_6, CS_6, SO_6); // Termopar 6

  // Flag que habilita o controle de temperatura
  bool temp_flag = false;
  // temperatura desejada
  float temp = 0.0;

void define_pwm_res() {

  DDRH |= (1 << DDH4);  // pinMode(7, OUTPUT);

  TCCR4A |= (1 << WGM41);
  TCCR4A |= (1 << WGM40);
  TCCR4A |= (1 << COM4B1);
  TCCR4B &= ~(1 << CS42);

}

void pwm_res(float pwm) {

  if (pwm < 100) {
  
    float pwm_8bits = ( 1023 * pwm ) / 100;

    OCR4B = uint16_t(pwm_8bits);

  } else {

    OCR4B = 1023;
    
  }

}

void temp_control() {

  float temp_media = 0.0;

  temp_media = (thermo2.readCelsius() + thermo3.readCelsius()) / 2;

  if (temp_media < temp) {
    pwm_res(100.0);
    
  } else {
    if (temp_media >= temp) {
    pwm_res(0.0);
    } else {
      Serial.println("Leitura falhou");
    }
  }
  
}

float current_res1() { // Função para calcular a corrente no ramo 1 de resistências

  float voltage1 = 0.0;
  float i_res1 = 0.0;
  uint16_t sensor_value1 = 0;

  sensor_value1 = analogRead(A14);

  voltage1 = (DIV_VOLTAGE * sensor_value1) - 2.5;

  i_res1 = voltage1 / 0.1;

  return i_res1;

}

float current_res2() { // Função para calcular a corrente no ramo 2 de resistências

  float voltage2 = 0.0;
  float i_res2 = 0.0;
  uint16_t sensor_value2 = 0;

  sensor_value2 = analogRead(A15);

  voltage2 = (DIV_VOLTAGE * sensor_value2) - 2.5;

  i_res2 = voltage2 / 0.1;

  return i_res2;

}
