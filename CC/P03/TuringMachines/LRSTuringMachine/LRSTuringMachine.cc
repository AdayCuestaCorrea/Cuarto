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

#include "LRSTuringMachine.h"

bool LRSTuringMachine::execute(std::string word) {

  return true; 
}

void LRSTuringMachine::print(std::ostream& os) const {
  os << "Left Right Stay Turing Machine" << std::endl;
  os << "States: ";
  for (const auto& state : states_) {
    os << state->getName() << " ";
  }
  os << std::endl;
  os << "Input Alphabet: ";
  for (const auto& symbol : alphabet_) {
    os << symbol << " ";
  }
  os << std::endl;
  os << "Tape Alphabet: ";
  for (const auto& symbol : tape_->getAlphabet()) {
    os << symbol << " ";
  }
  os << std::endl;
  os << "Initial state: " << initial_state_->getName() << std::endl;
  os << "Blank symbol: ." << std::endl;
  os << "Final states: ";
  for (const auto& state : states_) {
    if (state->isFinal()) os << state->getName() << " ";
  }
  os << std::endl;
  os << "Transitions:" << std::endl;
  bool first_transition = true;
  for (const auto& state : states_) {
    for (const auto& transition : state->getTransitions()) {
      if (!first_transition) os << std::endl;
      os << "  " << state->getName() << " " 
      << transition.getRead() << " -> " 
      << transition.getDestination()->getName() << " " 
      << transition.getWrite() << " " << 
      transition.getMovement();
      first_transition = false;
    }
  }
}