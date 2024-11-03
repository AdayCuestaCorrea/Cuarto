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

/**
 * @brief Executes the multitape Turing machine with the given input.
 *
 * This function initializes the tapes with the provided input words, sets the initial state,
 * and processes transitions until no more transitions are possible. It then generates and
 * returns the result based on the final state.
 *
 * @param input The input to the Turing machine, expected to be a vector of strings.
 * @return The result of the Turing machine execution as a string.
 * @throws std::runtime_error If the input type is not a vector of strings.
 */
std::string MultitapeTuringMachine::execute(InputType input) {
  if (!std::holds_alternative<std::vector<std::string>>(input)) {
    throw std::runtime_error("Invalid input type");
  }

  std::vector<std::string> words = std::get<std::vector<std::string>>(input);
  initializeTapes(words);

  std::shared_ptr<State> current_state = initial_state_;
  while (true) {
    std::vector<char> read_symbols = readFromTapes();
    if (!processTransition(current_state, read_symbols)) break;
  }

  return generateResult(current_state);
}

/**
 * @brief Processes a transition for the current state based on the read symbols.
 *
 * This function iterates through the transitions of the current state and checks
 * if any transition matches the provided read symbols. If a matching transition
 * is found, it applies the transition, updates the current state to the destination
 * state of the transition, and returns true. If no matching transition is found,
 * it returns false.
 *
 * @param current_state A shared pointer to the current state of the Turing machine.
 * @param read_symbols The symbols read from the tapes that are used to determine the transition.
 * @return true if a matching transition is found and applied, false otherwise.
 */
bool MultitapeTuringMachine::processTransition(std::shared_ptr<State> &current_state, Alphabet &read_symbols) {
  for (const auto &transition : current_state->getTransitions()) {
    if (transition->getReadSymbols() == read_symbols) {
      applyTransition(transition);
      current_state = transition->getDestination();
      return true;
    }
  }
  return false;
}

/**
 * @brief Initializes the tapes of the multitape Turing machine with the given input words.
 *
 * This function takes a vector of input words and assigns each word to a corresponding tape.
 * If the number of input words is less than the number of tapes, the remaining tapes are 
 * initialized with a default symbol ("."). If the number of input words exceeds the number 
 * of tapes, an exception is thrown.
 *
 * @param words A vector of strings representing the input words to be placed on the tapes.
 */
void MultitapeTuringMachine::initializeTapes(const std::vector<std::string>& words) {
  std::vector<std::string> adjusted_words = words;
  for (size_t i = adjusted_words.size(); i < tape_.size(); ++i) {
    adjusted_words.push_back(".");
  }

  for (size_t i = 0; i < adjusted_words.size(); ++i) {
    tape_[i].setContent(adjusted_words[i]);
  }
}

/**
 * @brief Reads the current symbols from all tapes in the multitape Turing machine.
 *
 * This function iterates over all the tapes in the Turing machine and reads the current
 * symbol from each tape. The symbols are collected into a vector and returned.
 *
 * @return std::vector<char> A vector containing the symbols read from each tape.
 */
std::vector<char> MultitapeTuringMachine::readFromTapes() {
  std::vector<char> read_symbols;
  for (auto& tape : tape_) {
    read_symbols.push_back(tape.read());
  }
  return read_symbols;
}

/**
 * @brief Applies a transition to the multitape Turing machine.
 *
 * This function takes a transition and applies it to the current state of the
 * multitape Turing machine. It writes the specified symbols to each tape and
 * moves the tape heads according to the given directions.
 *
 * @param transition A shared pointer to the Transition object that contains
 *                   the write symbols and move directions for each tape.
 *
 * @throws std::runtime_error If an invalid movement direction is encountered.
 */
void MultitapeTuringMachine::applyTransition(const std::shared_ptr<Transition> transition) {
  const auto& write_symbols = transition->getWriteSymbols();
  const auto& move_directions = transition->getMoveDirections();

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
}

/**
 * @brief Generates a result message based on the current state of the Turing Machine.
 *
 * This function checks if the provided current state is a final state. If it is,
 * it generates a message indicating that the Turing Machine stopped on an accepted state
 * and includes the content of the tape. If the current state is not a final state,
 * it generates a message indicating that the Turing Machine did not stop on an accepted state
 * and includes the content of the tape.
 *
 * @param current_state A shared pointer to the current state of the Turing Machine.
 * @return A string containing the result message and the tape content.
 */
std::string MultitapeTuringMachine::generateResult(const std::shared_ptr<State>& current_state) {
  std::string result;
  if (current_state->isFinal()) {
    result = "Turing Machine stopped on an accepted state.\nTape content:\n" + getTapeContents();
  } else {
    result = "Turing Machine didn't stop on an accepted state.\nTape content:\n" + getTapeContents();
  }
  return result;
}

/**
 * @brief Retrieves the contents of all tapes in the multitape Turing machine.
 *
 * This function iterates over all the tapes in the Turing machine and constructs
 * a string that contains the contents of each tape. Each tape's content is 
 * prefixed with "Tape X: ", where X is the tape number starting from 1.
 *
 * @return A string representing the contents of all tapes, with each tape's 
 *         content on a new line.
 */
std::string MultitapeTuringMachine::getTapeContents() const {
  std::string result;
  for (size_t i = 0; i < tape_.size(); ++i) {
    result += "Tape " + std::to_string(i + 1) + ": " + tape_[i].getContent() + "\n";
  }
  return result;
}

/**
 * @brief Prints the details of the Multitape Turing Machine to the given output stream.
 *
 * This function outputs the following details of the Multitape Turing Machine:
 * - The name "Multitape Turing Machine".
 * - The list of states.
 * - The input alphabet.
 * - The tape alphabet.
 * - The initial state.
 * - The blank symbol.
 * - The list of final states.
 * - The transitions between states, including read symbols, destination states, write symbols, and move directions.
 *
 * @param os The output stream to which the details will be printed.
 */
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