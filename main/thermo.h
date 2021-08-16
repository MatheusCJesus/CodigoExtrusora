/* 
--------------------------------------------------------------------------------
  Algoritmo para controlar os drivers de thermopar
  Placa: v1.0
--------------------------------------------------------------------------------
  Autor: Matheus Cerqueira de Jesus
  Data: 13 de Agosto de 2021
  Bolsista FAPESP
--------------------------------------------------------------------------------
*/

#include "definition.h"
#include "max6675.h"

  // Instânciação dos objetos da classe MAX6675

  MAX6675 thermoN(SCK_1, CS_1, SO_1); // Termopar 1: Nozzle
  MAX6675 thermo2(SCK_2, CS_2, SO_2); // Termopar 2
  MAX6675 thermo3(SCK_3, CS_3, SO_3); // Termopar 3
  MAX6675 thermo4(SCK_4, CS_4, SO_4); // Termopar 4
  MAX6675 thermo5(SCK_5, CS_5, SO_5); // Termopar 5
  MAX6675 thermo6(SCK_6, CS_6, SO_6); // Termopar 6

