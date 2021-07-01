
/* 
--------------------------------------------------------------------------------
  Algoritimo para controlar todo o sistema da máquina extrusora
  Placa: v1.0
--------------------------------------------------------------------------------
  Autor: Matheus Cerqueira de Jesus
  Data: 22 de Junho de 2021
  Bolsista FAPESP
--------------------------------------------------------------------------------
*/

#include "stepMotor.h"

/* ------------- Definições ------------- */

// Pinos digitais dos módulos de termopar
// INÍCIO
#define SCK_1 22  //-----------
#define SO_1  24  // Termopar 1
#define CS_1  26  //-----------

#define SCK_2 23  //-----------
#define SO_2  27  // Termopar 2
#define CS_2  25  //-----------

#define SCK_3 29  //-----------
#define SO_3  33  // Termopar 3
#define CS_3  31  //-----------

#define SCK_4 35  //-----------
#define SO_4  39  // Termopar 4
#define CS_4  37  //-----------

#define SCK_5 41  //-----------
#define SO_5  45  // Termopar 5
#define CS_5  43  //-----------

#define SCK_6 47  //-----------
#define SO_6  51  // Termopar 6
#define CS_6  49  //-----------
//FIM

// Pinos digitais do paquímetro
// INÍCIO
#define DATAPIN_PAQ 3  // Pino de informação do paquímetro
#define CLKPIN_PAQ  4  // Pinos de clock do paquímetro
//FIM

// Pinos digitais drivers motor de passo
// INÍCIO
#define STEP_P 11 // Pino de controle de passos do motor PUXADOR
#define DIR_P  12 // Pino de controle de direção do motor PUXADOR

#define STEP_B 46 // Pino de controle de passos do motor BOBINADOR
#define DIR_B  48 // Pino de contrle de direção do motor BOBINADOR
//FIM

// Pinos digital sensor de temperatura e pressão (DHT22)
//INÍCIO
#define DATAPIN_DHT22 30 // Pino de informação do sensor DHT22
//FIM

// Pinos digitais do driver de motor DC (Shield VNH2SP30)
//INÍCIO
#define PWM_DCMOTOR 44 // Pino de saída do PWM do motor DC
#define IN_A 34        // Pino que habilita a PONTE H do lado A
#define IN_B 32        // Pino que habilita a PONTE H do lado B
#define CS   36        // Pino analógico para o sensor de sobrecorrente
//FIM

// Pino digital para PWM das resistências de aquecimento
//INÍCIO
#define PWM_RES 7 // Pino de saída do PWM das resistências
//FIM

/* ------------- Fim das definições ------------- */
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Seta a valocidade da comunicação serial em 9600 baud/s

  define_pwm(); // Chama a função que define os pinos x e x como saída de PWM



}

void loop() {
  // put your main code here, to run repeatedly:

}
