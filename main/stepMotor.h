
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
void define_pwm(){

  // Configura o PWM nos modos "Phase and frequency correct" - tabela 17-2 do datasheet

  TCCR1A = 0b01100001; // D11
  TCCR1B = 0b00010001; // 0001 0001

  TCCR5A = 0b01100001;
  TCCR5B = 0b00010001;

}
//FIM

void rpm_motor() {
}
