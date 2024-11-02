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

#include "MultitapeTuringMachine.h"

std::string MultitapeTuringMachine::execute(InputType input) {
  if (!std::holds_alternative<std::vector<std::string>>(input)) {
    throw std::runtime_error("Invalid input type");
  }

  std::vector<std::string> words = std::get<std::vector<std::string>>(input);

  for (size_t i = words.size(); i < tape_.size(); ++i) {
    words.push_back(".");
  }

  if (words.size() != tape_.size()) {
    throw std::runtime_error("Number of input words does not match number of tapes");
  }

  for (size_t i = 0; i < words.size(); ++i) {
    tape_[i].setContent(words[i]);
  }

  std::shared_ptr<State> current_state = initial_state_;
  while (true) {
    std::vector<char> read_symbols;
    for (auto& tape : tape_) {
      read_symbols.push_back(tape.read());
    }

    bool transition_found = false;
    for (const auto& transition : current_state->getTransitions()) {
      const auto& multi_tape_transition = static_cast<MultiTapeTransition&>(*transition);
      if (multi_tape_transition.getReadSymbols() == read_symbols) {
        const auto& write_symbols = multi_tape_transition.getWriteSymbols();
        const auto& move_directions = multi_tape_transition.getMoveDirections();
        for (size_t i = 0; i < tape_.size(); ++i) {
          tape_[i].write(write_symbols[i]);
          switch (move_directions[i]) {
            case 'L':
              tape_[i].moveLeft();
              break;
            case 'R':
              tape_[i].moveRight();
              break;
            case 'S':
              tape_[i].stay();
              break;
            default:
              throw std::runtime_error("Invalid movement direction");
          }
        }

        current_state = multi_tape_transition.getDestination();
        transition_found = true;
        break;
      }
    }

    if (!transition_found) {
      break;
    }
  }
  std::string result;
  if (current_state->isFinal()) result = "Turing Machine stopped on an accepted state.\nTape content:\n" + getTapeContents();
  else result = "Turing Machine didn't stop on an accepted state.\nTape content:\n" + getTapeContents();

  return result;
}

std::string MultitapeTuringMachine::getTapeContents() const {
  std::string result;
  for (size_t i = 0; i < tape_.size(); ++i) {
    result += "Tape " + std::to_string(i + 1) + ": " + tape_[i].getContent() + "\n";
  }
  return result;
}

void MultitapeTuringMachine::print(std::ostream& os) const {
  os << "Multitape Turing Machine" << std::endl;
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
  for (const auto& tape : tape_) {
    for (const auto& symbol : tape.getAlphabet()) {
      os << symbol << " ";
    }
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
      const auto& multi_tape_transition = static_cast<MultiTapeTransition&>(*transition);
      if (!first_transition) os << std::endl;
      os << "  " << state->getName() << " ";
      for (const auto& read_symbol : multi_tape_transition.getReadSymbols()) {
        os << read_symbol << " ";
      }
      os << "-> " << multi_tape_transition.getDestination()->getName() << " ";
      for (const auto& write_symbol : multi_tape_transition.getWriteSymbols()) {
        os << write_symbol << " ";
      }
      for (const auto& move_direction : multi_tape_transition.getMoveDirections()) {
        os << move_direction << " ";
      }
      first_transition = false;
    }
  }
}