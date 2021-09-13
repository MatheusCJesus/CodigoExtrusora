/* 
--------------------------------------------------------------------------------
  Biblioteca para controlar as interrupções internas
  Placa: v1.0
--------------------------------------------------------------------------------
  Autor: Matheus Cerqueira de Jesus
  Data: 14 de Agosto de 2021
  Bolsista FAPESP
--------------------------------------------------------------------------------
*/

uint8_t tempo = 0; // Tempo em segundos para gerar a interrupção
uint16_t t3_comp = 0; // Valor para ser atribuído no registrador 
                      // para gerar a interrupção no tempo escolhido

const float prescaler = 1024;

bool display_flag = false;

void set_time(float tempo){

  t3_comp = tempo*16000000/prescaler;

  OCR3A = uint16_t(t3_comp);

}

void set_INTERNAL_INTERRUPT() {

  //Limpa o registrador
  TCCR3A = 0b00000000;

  // Configura o timer 3 para o modo CTC (Clear Timer on Compare Match)
  TCCR3B &= ~(1 << WGM33);
  TCCR3B |= (1 << WGM32);

  // Seleciona o prescaler de 1024 para o timer 3
  TCCR3B |= (1 << CS32);
  TCCR3B &= ~(1 << CS31);
  TCCR3B |= (1 << CS30);

  // Habilita a interrupção interna do timer 3
  TIMSK3 |= (1 << OCIE3A);

}

void set_Compare_Value(){

  OCR3A = t3_comp;

}

ISR(TIMER3_COMPA_vect) {

  display_flag = !display_flag;
  
}
