/* 
// --------------------------------------------------------------------------------
//   Biblioteca para controlar o motor DC
//   Placa: v1.0
// --------------------------------------------------------------------------------
//   Autor: Matheus Cerqueira de Jesus
//   Data: 14 de Agosto de 2021
//   Bolsista FAPESP
// --------------------------------------------------------------------------------
*/

// // ------------------------- Declarações de variáveis --------------------------

uint32_t tempo_passado = 0;
uint32_t tempo_atual = 0;

uint32_t t_passado_Interrupt = 0;
uint32_t t_atual_Interrupt = 0;

uint16_t passos = 0;

void define_DCpwm() {

  DDRB |= (1 << DDB7);  // pinMode(13, OUTPUT);
  DDRC |= (1 << DDC5);  // pinMode(32, OUTPUT);
  DDRC |= (1 << DDC3);  // pinMode(34, OUTPUT);
  DDRD &= ~(1 << DDD1);  // pinMode(20, OUTPUT);

  TCCR0A |= (1 << WGM01);
  TCCR0A |= (1 << WGM00);
  TCCR0A |= (1 << COM0A1);

}

float calcula_CS() { // Função para calcular a corrente no motor

  float voltage = 0.0;
  float i_out = 0.0;
  uint16_t sensor_value = 0;

  sensor_value = analogRead(A7);

  voltage = DIV_VOLTAGE * sensor_value;

  i_out = 11370 * voltage/1500;

  return i_out;

}

void pwm_motor(char dir, float pwm) {

  float pwm_8bits = (255 * pwm) / 100;

  if (dir == 'c' | dir == 'C') { // Rotaciona o motor no sentido horário

    PORTC |= (1 << PORTC5);
    PORTC &= ~(1 << PORTC3);

    if (pwm < 100) {
      OCR0A = pwm_8bits;
    } else {
      OCR0A = 255;
    }

  } else {

    if (dir == 'a' | dir == 'A') { // Rotaciona o motor no sentido anti-horário

      PORTC |= (1 << PORTC3);
      PORTC &= ~(1 << PORTC5);

      if (pwm < 100) {
      OCR0A = pwm_8bits;
    } else {
      OCR0A = 255;
    }

    } else {

      if(dir == 's' | dir == 'S') { // Trava o motor

         PORTC |= (1 << PORTC5);
         PORTC |= (1 << PORTC3);
         OCR0A = 0;
        
      }
      
    }
  }
}


float get_rpm() {

  float rpm = 0.0;

  tempo_atual = millis();

  if (tempo_atual - tempo_passado >= 999) {

    EIMSK &= ~(1 << INT1);

    float tempo = tempo_atual - tempo_passado;

    rpm = (60000/(tempo * (float)passos_por_volta)) * passos;

    //Serial.print("Passos: ");
    //Serial.println(passos);
    //Serial.print("Tempo: ");
    //Serial.println(tempo);
    //Serial.print("RPM: ");

    tempo_passado = tempo_atual;

    passos = 0;

    EIMSK |= (1 << INT1);

  }

  return rpm;

}

void Set_EXTERNAL_INTERRUPT_RPM() {
/* Configura interrupção externa nos registadores como borda de
   subida para o pino de encoder (D20) */

  EICRA &= ~(1 << ISC10);
  EICRA |= (1 << ISC11);

  EIMSK |= (1 << INT1);
  
}

ISR(INT1_vect){ // Função de interrupção.

 // t_atual_Interrupt = millis();

 // if  (digitalRead(20) == LOW) {
   // t_passado_Interrupt = t_atual_Interrupt;
     //Serial.println("IF 1");
 // }
  //if (t_atual_Interrupt - t_passado_Interrupt >= 60)  {
     passos = passos + 1;
      //Serial.println("IF 2"); 
//  }
        
        
  }
