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

float tempo_passado = 0.0;
float tempo_atual = 0.0;

uint8_t passos = 0;

void define_DCpwm() {

  DDRB |= (1 << DDB7);  // pinMode(13, OUTPUT);
  DDRC |= (1 << DDC5);  // pinMode(32, OUTPUT);
  DDRC |= (1 << DDC3);  // pinMode(34, OUTPUT);

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
    OCR0A = pwm_8bits;

  } else {

    if (dir == 'a' | dir == 'A') { // Rotaciona o motor no sentido anti-horário

      PORTC |= (1 << PORTC3);
      PORTC &= ~(1 << PORTC5);
      OCR0A = pwm_8bits;

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

  if (tempo_atual - tempo_passado > 1000) {

    rpm = (60 * 1000 / passos_por_volta) / (tempo_atual - tempo_passado) * passos;

    tempo_passado = tempo_atual;

    passos = 0;

  }

  return rpm;

}

void Set_EXTERNAL_INTERRUPT_RPM() {
/* Configura interrupção externa nos registadores como borda de
   subida para o pino de encoder (D20) */

  EICRA |= (1 << ISC10);
  EICRA |= (1 << ISC11);

  EIMSK |= (1 << INT1);

}

ISR(INT1_vect){ // Função de interrupção.
   passos += 1;
}
