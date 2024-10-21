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

void PushDownAutomata::print(std::ostream& os) const {
  // Print states
  for (const auto& state : states_) {
    os << state->get_name() << " ";
  }
  os << std::endl;

  // Print alphabet
  for (const auto& symbol : alphabet_) {
    if (symbol == '.') continue;
    os << symbol << " ";
  }
  os << std::endl;

  // Print stack alphabet
  for (const auto& symbol : stack_alphabet_) {
    if (symbol == '.') continue;
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

bool PushDownAutomata::execute(std::string word) {
  std::stack<Symbol> stack = stack_;
  return executeRecursive(initial_state_, word, 0, stack);
}

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