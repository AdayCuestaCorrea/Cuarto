/** Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Complejidad Computacional
  * Curso: 4º
  * Práctica 2: Autómata De Pila
  * Autor: Aday Cuesta Correa
  * Correo: alu0101483887@ull.edu.es
  * Fecha: 16/10/2024
  */

#include "PushDownAutomata.h"

/**
 * @brief Prints the details of the PushDownAutomata to the given output stream.
 *
 * This function outputs the following details of the PushDownAutomata:
 * - States: Names of all the states in the automaton.
 * - Alphabet: Symbols in the input alphabet.
 * - Stack Alphabet: Symbols in the stack alphabet.
 * - Initial State: Name of the initial state.
 * - Initial Stack Symbol: The symbol at the top of the stack if the stack is not empty.
 * - Transitions: All transitions in the automaton, formatted as:
 *   [current_state] [input_symbol] [stack_symbol_to_pop] [next_state] [stack_symbols_to_push]
 *
 * @param os The output stream to which the details are printed.
 */
void PushDownAutomata::print(std::ostream& os) const {
  // Print states
  for (const auto& state : states_) {
    os << state->get_name() << " ";
  }
  os << std::endl;

  // Print alphabet
  for (const auto& symbol : alphabet_) {
    os << symbol << " ";
  }
  os << std::endl;

  // Print stack alphabet
  for (const auto& symbol : stack_alphabet_) {
    os << symbol << " ";
  }
  os << std::endl;

  // Print initial state
  os << initial_state_->get_name() << std::endl;

  // Print initial stack symbol
  if (!stack_.empty()) {
    os << stack_.top() << std::endl;
  }

  // Print transitions
  bool first_transition = true;
  for (const auto& state : states_) {
    for (const auto& transition : state->get_transitions()) {
      if (!first_transition) os << std::endl;
      os << state->get_name() << " " << transition.get_read() << " "
         << transition.get_remove_from_stack() << " "
         << transition.get_destination()->get_name() << " "
         << transition.get_insert_into_stack();
      first_transition = false;
    }
  }
}

/**
 * @brief Executes the pushdown automaton on a given input word.
 *
 * This function initializes the stack with the current stack state and 
 * starts the recursive execution of the automaton from the initial state.
 *
 * @param word The input string to be processed by the automaton.
 * @return true if the automaton accepts the input word, false otherwise.
 */
bool PushDownAutomata::execute(std::string word) {
  std::stack<Symbol> stack = stack_;
  return executeRecursive(initial_state_, word, 0, stack);
}

/**
 * @brief Executes the pushdown automaton recursively to determine if the given word is accepted.
 *
 * This function attempts to process the given word starting from the current state and using the provided stack.
 * It follows the transitions defined in the automaton and checks if the word can be fully read while emptying the stack.
 *
 * @param current_state The current state of the automaton.
 * @param word The input word to be processed.
 * @param index The current index in the word being processed.
 * @param stack The current stack used by the automaton.
 * @return true if the word is accepted by the automaton, false otherwise.
 */
bool PushDownAutomata::executeRecursive(std::shared_ptr<State> current_state, const std::string& word, int index, std::stack<Symbol>& stack) {
  // Base case: if the entire word has been read and the stack is empty
  if (index == word.size() && stack.empty()) {
    return true;
  }

  // If the stack is empty but the word is not fully read, return false
  if (stack.empty()) {
    return false;
  }

  Symbol read = (index < word.size()) ? word[index] : '.';
  Symbol top_stack = stack.top();

#ifdef TRAZA
  std::cout << "Current state: " << current_state->get_name() << ", Index: " << index 
            << ", Read: " << read << ", Stack top: " << top_stack << std::endl;
#endif

  for (const Transition& transition : current_state->get_transitions()) {
    if ((transition.get_read() == read || transition.get_read() == '.') && transition.get_remove_from_stack() == top_stack) {
      // Apply the transition
      stack.pop();
      std::stack<Symbol> temp_stack = stack;
      
      // Push symbols in reverse order
      const std::string& to_push = transition.get_insert_into_stack();
      for (auto it = to_push.rbegin(); it != to_push.rend(); ++it) {
        if (*it != '.') {
          temp_stack.push(*it);
        }
      }

#ifdef TRAZA
      std::cout << "Transition: " << current_state->get_name() << " --(" << transition.get_read() 
                << ", " << transition.get_remove_from_stack() << " / " << transition.get_insert_into_stack() 
                << ")--> " << transition.get_destination()->get_name() << std::endl;
#endif

      // Recur with the next state and updated stack
      if (executeRecursive(transition.get_destination(), word, index + (transition.get_read() != '.'), temp_stack)) {
        return true;
      }

      // Restore the stack for the next iteration
      stack.push(top_stack);
    }
  }

  return false;
}