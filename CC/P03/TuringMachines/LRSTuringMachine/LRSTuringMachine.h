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

/**
 * @class LRSTuringMachine
 * @brief A class representing a Turing Machine with Left-Right-Stop (LRS) tape movement.
 * 
 * This class extends the TuringMachine class and provides additional functionality
 * specific to a Turing Machine that operates with a tape that can move left, right, or stop.
 * 
 * @param states A collection of states for the Turing Machine.
 * @param initial_state The initial state of the Turing Machine.
 * @param alphabet The alphabet used by the Turing Machine.
 * @param tape The tape used by the Turing Machine.
 */
class LRSTuringMachine : public TuringMachine {
 public:
  LRSTuringMachine(const States& states, std::shared_ptr<State> initial_state, const Alphabet& alphabet, LRSTuringMachineTape tape)
                       : TuringMachine(states, initial_state, alphabet), tape_(tape) {}

  std::string execute(InputType input) override;
  void print(std::ostream& os) const override;
 private:
  LRSTuringMachineTape tape_;
  bool processTransitions(std::shared_ptr<State>& current_state, char read_symbol);
  void moveTape(char direction);
  std::string generateResult(const std::shared_ptr<State>& current_state);
};