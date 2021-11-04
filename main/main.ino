
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

/* ------------- Início das definições ------------- */

char inputString[10];      // a String to hold incoming data
bool stringComplete = false, erro = false;  // whether the string is complete
char *token;
uint8_t commands;
char valid_commands[4] = {'1','2','3','4'};
uint8_t i = 0;
uint8_t buf_len = 0;
char buf[10];

float soma_i_out = 0;
float media_i_out = 0;
uint8_t l = 0;
uint8_t k = 0;

/* ------------- Fim das definições ------------- */

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Seta a valocidade da comunicação serial em 9600 baud/s

  define_pwm(); // Define os pinos D11 e D46 como saída de PWM.
  define_DCpwm();
  define_pwm_res();
  set_INTERNAL_INTERRUPT();

  Set_INPUT_pins();

  Set_EXTERNAL_INTERRUPT_CALIPER();
  Set_EXTERNAL_INTERRUPT_RPM();
  set_time(2);
  
}

void loop() {

  //put your main code here, to run repeatedly:

  if (k == 100) {

    if (l < 5) {

      soma_i_out += calcula_CS();

      l++;      

    } else {

      media_i_out = soma_i_out / l;
      soma_i_out = 0.0;

      l = 0;
      
    }

    k = 0;

  }

  // Controle de temperatura das resistências

  if (display_flag) {

    Serial.println("============Temperaturas=============");
    Serial.print("Nuzzle: ");
    Serial.print(thermoN.readCelsius());
    Serial.print(" || Termopar 2: ");
    Serial.print(thermo2.readCelsius());
    Serial.print(" || Termopar 3: ");
    Serial.print(thermo3.readCelsius());
    Serial.print(" || Termopar 4: ");
    Serial.println(thermo4.readCelsius());
    
    Serial.println("==============Motor DC==============="); 
    Serial.print("I_motor: ");
    Serial.print(media_i_out);
    Serial.print(" || RPM motor DC: ");
    Serial.println(get_rpm());

    Serial.println("============Resistencias============="); 
    Serial.print("I_res1: ");
    Serial.print(current_res1());
    Serial.print(" || I_res2: ");
    Serial.println(current_res2());

    Serial.println("========Diametro do filamento========");
    Serial.print("Diametro[mm]: ");
    Serial.println(getFinalValue());

    // Chama a função de controle de temperatura
    temp_control();
    
    display_flag = false;

 }

  if(inputString[0] == 'G') {
    for(int i = 0; i < 4; i++) {
      if(inputString[1] == valid_commands[i]) {
        commands = i + 1;
      }
    }
  }
  if (stringComplete) {
      if(commands == 1){ 

        char rotacao[1];
        float e_pwm = 0;

        token = strtok(inputString, " ");
        token = strtok(NULL, " ");
        strcpy(rotacao, token);
        Serial.println(rotacao);

        token = strtok(NULL, " ");
        e_pwm = atof(token);

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
        char control;

        token = strtok(inputString, " ");
        token = strtok(NULL, " ");
        control = token[0];
        Serial.println(control);
        if (control == 'm' | control == 'M') {
          temp_flag = false;
          token = strtok(NULL, " ");
          Rpwm = atof(token);
          pwm_res(Rpwm);
          Serial.println(Rpwm);
        } else {
          if (control == 'a' | control == 'A') {
            temp_flag = true;
            token = strtok(NULL, " ");
            temp = atof(token);
            temp_control();
            Serial.println(temp);
          } else {
            temp_flag = false;
          }
        }

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

  k++;
  
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
