
/* 
--------------------------------------------------------------------------------
  Biblioteca de controle de motor de passo
  Placa: v1.0
--------------------------------------------------------------------------------
  Autor: Matheus Cerqueira de Jesus
  Data: 22 de Junho de 2021
  Bolsista FAPESP
--------------------------------------------------------------------------------
*/
/* ------------ Configurar os PWMs dos pinos STEP_P(D11) e STEP_B(D46) ------------ */
//INÍCIO
void define_pwm() {

  DDRB |= (1 << DDB5);  // pinMode(11, OUTPUT);
  DDRB |= (1 << DDB6);  // pinMode(12, OUTPUT);
  DDRL |= (1 << DDL3);  // pinMode(46, OUTPUT);
  DDRL |= (1 << DDL1);  // pinMode(48, OUTPUT);

  // Configura o PWM nos modos "Phase and frequency correct" - tabela 17-2 do datasheet

  TCCR5A = 0;
  TCCR5B = 0;
  TCCR1A = 0;
  TCCR1B = 0;

  // D11
  TCCR1A &= ~(1 << WGM11);
  TCCR1A |=  (1 << WGM10);

  TCCR1A &= ~(1 << COM1A1);
  TCCR1A |=  (1 << COM1A0);

  TCCR1B &= ~(1 << WGM12);
  TCCR1B |=  (1 << WGM13);

  TCCR1B &= ~(1 << CS11);
  TCCR1B |=  (1 << CS10);

  //D46
  TCCR5A &= ~(1 << WGM51);
  TCCR5A |=  (1 << WGM50);

  TCCR5A &= ~(1 << COM5A1);
  TCCR5A |=  (1 << COM5A0);

  TCCR5B &= ~(1 << WGM52);
  TCCR5B |=  (1 << WGM53);

  TCCR5B &= ~(1 << CS51);
  TCCR5B |=  (1 << CS50);

  ICR1 = 0;
  OCR1A = 0;
  ICR5 = 0;
  OCR5A = 0;
  
}
//FIM

void rpm_motor(char motor,char dir, float rpm) {

  // Micro passo = 1/32 avos
  // Angulo por passo = 0,05625 --> 0,05625*passos = 360
  // Passos para dar uma volta = 6400

  float freq = 0.0;
  
  if (motor == 'p' | motor == 'P') {

    freq = (rpm * 6400) / 60;
    ICR1 = 0;
    OCR1A = round(16000000 / (4 * 1 * freq));

    if (dir == 'A' | dir == 'a') {
      Serial.println("A");
      PORTB |=  (1 << PORTB6);
    } else {
        if (dir == 'C' | dir == 'c') {
          PORTB &= ~(1 << PORTB6);
          Serial.println("C");
        }
     }

  } else {

    if (motor == 'b' | motor == 'B') {

      freq = (rpm * 6400) / 60;
      ICR5 = 0;
      OCR5A = round(16000000 / (4 * 1 * freq));

      if (dir == 'A' | dir == 'a') {
        Serial.println("A");
        PORTL |=  (1 << PORTL1);
  } else {
      if (dir == 'C' | dir == 'c') {
        PORTL &= ~(1 << PORTL1);
        Serial.println("C");
    }
  }

    }
  }
}
