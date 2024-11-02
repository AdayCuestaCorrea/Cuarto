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

std::string LRSTuringMachine::execute(InputType input) {
  if (!std::holds_alternative<std::string>(input)) {
    throw std::runtime_error("Invalid input type");
  }
  tape_.setContent(std::get<std::string>(input));
  std::shared_ptr<State> current_state = initial_state_;
  while (true) {
    char read_symbol = tape_.read();
    bool transition_found = false;

    for (const auto& transition : current_state->getTransitions()) {
      auto single_tape_transition = std::dynamic_pointer_cast<SingleTapeTransition>(transition);
      if (single_tape_transition && single_tape_transition->getReadSymbols()[0] == read_symbol) {
        tape_.write(single_tape_transition->getWriteSymbols()[0]);
        switch (single_tape_transition->getMoveDirections()[0]) {
          case 'L':
            tape_.moveLeft();
            break;
          case 'R':
            tape_.moveRight();
            break;
          case 'S':
            tape_.stay();
            break;
          default:
            throw std::runtime_error("Invalid movement direction");
        }
        current_state = single_tape_transition->getDestination();
        transition_found = true;
        break;
      }
    }

    if (!transition_found) {
      break;
    }
  }
  std::string result;
  if (current_state->isFinal()) result = "Turing Machine stopped on an accepted state.\nTape content: " + tape_.getContent();
  else result = "Turing Machine didn't stop on an accepted state.\nTape content: " + tape_.getContent();
  
  return result;
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
  for (const auto& symbol : tape_.getAlphabet()) {
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
      auto single_tape_transition = std::dynamic_pointer_cast<SingleTapeTransition>(transition);
      if (single_tape_transition) {
        if (!first_transition) os << std::endl;
        os << "  " << state->getName() << " " 
           << single_tape_transition->getReadSymbols()[0] << " -> " 
           << single_tape_transition->getDestination()->getName() << " " 
           << single_tape_transition->getWriteSymbols()[0] << " " 
           << single_tape_transition->getMoveDirections()[0];
        first_transition = false;
      }
    }
  }
}