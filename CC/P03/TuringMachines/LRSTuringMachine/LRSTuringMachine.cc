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

/**
 * @brief Executes the Turing machine with the given input.
 *
 * This function sets the tape content to the provided input and starts the
 * Turing machine from the initial state. It processes transitions until no
 * more transitions are possible.
 *
 * @param input The input to be processed by the Turing machine. It must be of type std::string.
 * @return A std::string representing the result after the Turing machine has finished processing.
 * @throws std::runtime_error If the input type is not std::string.
 */
std::string LRSTuringMachine::execute(InputType input) {
  if (!std::holds_alternative<std::string>(input)) {
    throw std::runtime_error("Invalid input type");
  }

  tape_.setContent(std::get<std::string>(input));
  std::shared_ptr<State> current_state = initial_state_;
  while (true) {
    char read_symbol = tape_.read();
    if (!processTransitions(current_state, read_symbol)) break;
  }

  return generateResult(current_state);
}

/**
 * @brief Processes the transitions for the current state based on the read symbol.
 *
 * This function iterates through the transitions of the current state and checks if any transition
 * matches the given read symbol. If a matching transition is found, it writes the corresponding 
 * symbol to the tape, moves the tape in the specified direction, updates the current state to the 
 * destination state of the transition, and returns true. If no matching transition is found, it 
 * returns false.
 *
 * @param current_state A shared pointer to the current state of the Turing machine.
 * @param read_symbol The symbol read from the tape.
 * @return true if a matching transition is found and processed, false otherwise.
 */
bool LRSTuringMachine::processTransitions(std::shared_ptr<State>& current_state, char read_symbol) {
  for (const auto& transition : current_state->getTransitions()) {
    if (transition->getReadSymbols()[0] == read_symbol) {
      tape_.write(transition->getWriteSymbols()[0]);
      moveTape(transition->getMoveDirections()[0]);
      current_state = transition->getDestination();
      return true;
    }
  }
  return false;
}

/**
 * @brief Moves the tape in the specified direction.
 *
 * This function moves the tape based on the given direction character.
 * The direction can be 'L' for left, 'R' for right, or 'S' for stay.
 * If an invalid direction is provided, a runtime error is thrown.
 *
 * @param direction The direction to move the tape ('L', 'R', or 'S').
 * @throws std::runtime_error If an invalid direction is provided.
 */
void LRSTuringMachine::moveTape(char direction) {
  switch (direction) {
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
std::string LRSTuringMachine::generateResult(const std::shared_ptr<State>& current_state) {
  std::string result;
  if (current_state->isFinal()) {
    result = "Turing Machine stopped on an accepted state.";
  } else {
    result = "Turing Machine didn't stop on an accepted state.";
  }
  return result;
}

void LRSTuringMachine::printTape() const {
  const std::string reset_color = "\033[0m";
  const std::string head_color = "\033[31m";

  std::string result = "Cinta: |";
  for (size_t i = 0; i < tape_.getContent().size(); ++i) {
    if (i == tape_.getHeadPosition()) {
      result += head_color + tape_.getContent()[i] + reset_color + "|";
    } else {
      result += tape_.getContent()[i] + std::string("|");
    }
  }
  std::cout << result << std::endl;
}

/**
 * @brief Prints the details of the Left Right Stay Turing Machine to the given output stream.
 *
 * This function outputs the following details of the Turing Machine:
 * - The type of the Turing Machine.
 * - The list of states.
 * - The input alphabet.
 * - The tape alphabet.
 * - The initial state.
 * - The blank symbol.
 * - The list of final states.
 * - The transitions between states.
 *
 * @param os The output stream to which the details will be printed.
 */
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