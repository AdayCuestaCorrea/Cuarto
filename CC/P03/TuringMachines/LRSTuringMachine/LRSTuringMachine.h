/** Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Complejidad Computacional
  * Curso: 4º
  * Práctica 3: Máquina de Turing
  * Autor: Aday Cuesta Correa
  * Correo: alu0101483887@ull.edu.es
  * Fecha: 01/11/2024
  */

#pragma once

#include "../TuringMachine.h"
#include "../Elements/Tape/LRSTuringMachineTape/LRSTuringMachineTape.h"
#include "../Elements/Transition/Types/SingleTapeTransition.h"

class LRSTuringMachine : public TuringMachine {
 public:
  LRSTuringMachine(const States& states, std::shared_ptr<State> initial_state, const Alphabet& alphabet, LRSTuringMachineTape tape)
                       : TuringMachine(states, initial_state, alphabet), tape_(tape) {}

  std::string execute(InputType input) override;
  void print(std::ostream& os) const override;
 private:
  LRSTuringMachineTape tape_;
};