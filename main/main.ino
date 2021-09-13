
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

#include <string.h>
#include "caliper.h"
#include "thermo.h"
#include "timerEvent.h"
#include "stepMotor.h"
#include "DCmotor.h"

char inputString[10];      // a String to hold incoming data
bool stringComplete = false, erro = false;  // whether the string is complete
char *token;
uint8_t commands;
char valid_commands[4] = {'1','2','3','4'};
uint8_t i = 0;
uint8_t buf_len = 0;
char buf[10];

/* ------------- Fim das definições ------------- */

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Seta a valocidade da comunicação serial em 9600 baud/s

  define_pwm(); // Define os pinos D11 e D46 como saída de PWM.
  define_DCpwm();
  define_pwm_res();
  set_INTERNAL_INTERRUPT();

  Set_INPUT_pins();

  Set_EXTERNAL_INTERRUPT();
  set_time(4);
  
}

void loop() {

  //put your main code here, to run repeatedly:

  if (display_flag) {
    
    Serial.println(thermoN.readCelsius());
    Serial.println(thermo2.readCelsius());
    Serial.println(thermo3.readCelsius());
    Serial.println(thermo4.readCelsius());
    Serial.println(thermo5.readCelsius());
    Serial.println(thermo6.readCelsius());
    display_flag = false;

 }

  if(inputString[0] == 'G') {
   // Serial.println("entrei no if G");
    for(int i = 0; i < 4; i++) {
      if(inputString[1] == valid_commands[i]) {
        commands = i + 1;
        Serial.println(commands);
      }
    }
  }
  if (stringComplete) {
  //Serial.println("Entrei");
    //switch (commands) {

      if(commands == 1){ 

        char rotacao[1];
        float e_pwm = 0;

        token = strtok(inputString, " ");
        token = strtok(NULL, " ");
        strcpy(rotacao, token);
        Serial.println(rotacao);

        token = strtok(NULL, " ");
        e_pwm = atof(token);
        Serial.println(e_pwm, DEC);

        pwm_motor(rotacao[0], e_pwm);

        memset(inputString, NULL, 10);

        stringComplete = false;

      }

      if(commands == 2){
        
        char motor[1];
        float rpm = 0;

        token = strtok(inputString, " ");
        token = strtok(NULL, " ");
        strcpy(motor, token);

        token = strtok(NULL, " ");
        rpm = atof(token);

        rpm_motor(motor[0], rpm);

        inputString[0] = 'a';

        memset(inputString, NULL, 10);

        stringComplete = false;

      }

      if(commands == 3){//case 3: 

        float Rpwm;

        token = strtok(inputString, " ");
        token = strtok(NULL, " ");
        Rpwm = atof(token);
        Serial.println(Rpwm);

        pwm_res(Rpwm);

        memset(inputString, NULL, 10);

        stringComplete = false;

      }

      if(commands == 4){//case 4:

        float tempo;

        token = strtok(inputString, " ");
        token = strtok(NULL, " ");
        tempo = atof(token);

        set_time(tempo);

        memset(inputString, NULL, 10);

        stringComplete = false;

      }
  }
  
}

void serialEvent() {
  char c;

  if(Serial.available() > 0) {
      c = Serial.read();
      // Salva o caractere recebido se não encher o buffer
      buf[i] = c;
      i++;
      if (buf[i-1] == '\n') {
        //buf[idx - 1] = '\0';
        memcpy(inputString, buf, i);
        memset(buf, 0, 10);
        stringComplete = true;
        Serial.print(inputString);
        Serial.println("");
        i = 0;
      }
    }
}
