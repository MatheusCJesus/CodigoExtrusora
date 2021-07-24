
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

  DDRB = 0b00100000;  // pinMode(11, OUTPUT);
  DDRL = 0b00001000;  // pinMode(46, OUTPUT);


  // Configura o PWM nos modos "Phase and frequency correct" - tabela 17-2 do datasheet

  TCCR1A = 0b01100001;  // D11
  TCCR1B = 0b00010001;

  TCCR5A = 0b01100001;  // D46
  TCCR5B = 0b00010001;
}
//FIM

void rpm_motor(char motor, int rpm) {

  // Micro passo = 1/32 avos
  // Angulo por passo = 0,05625 --> 0,05625*passos = 360
  // Passos para dar uma volta = 6400

  int freq = 0;

  if (motor == 'p' | motor == 'P') {

    freq = (rpm * 6400) / 60;
    ICR1 = 0;
    OCR1A = 16000000 / (4 * 1 * freq);

  } else {

    if (motor == 'b' | motor == 'B') {

      freq = (rpm * 6400) / 60;
      ICR5 = 0;
      OCR5A = 16000000 / (4 * 1 * freq);
    }
  }
}
