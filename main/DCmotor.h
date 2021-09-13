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

//uint8_t pwm = 0; // Inicializa uma variável para receber valores inteiros entre 0 e 100;

void define_DCpwm() {

  DDRB |= (1 << DDB7);  // pinMode(13, OUTPUT);
  DDRC |= (1 << DDC5);  // pinMode(32, OUTPUT);
  DDRC |= (1 << DDC3);  // pinMode(34, OUTPUT);

  TCCR0A |= (1 << WGM01);
  TCCR0A |= (1 << WGM00);
  TCCR0A |= (1 << COM0A1);

}

void pwm_motor(char dir, float pwm) {

  float pwm_8bits = (255 * pwm) / 100;

  if (dir == 'c' | dir == 'C') {

    PORTC |= (1 << PORTC5);
    PORTC &= ~(1 << PORTC3);
    OCR0A = pwm_8bits;

  } else {

    if (dir == 'a' | dir == 'A') {

      PORTC |= (1 << PORTC3);
      PORTC &= ~(1 << PORTC5);
      OCR0A = pwm_8bits;

    } else {

      if(dir == 's' | dir == 'S') {

         PORTC |= (1 << PORTC5);
         PORTC |= (1 << PORTC3);
         OCR0A = 0;
        
      }
      
    }
  } 
}
