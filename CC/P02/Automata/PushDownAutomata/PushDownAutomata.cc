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
  std::shared_ptr<State> current_state = initial_state_;
  for (int i = 0; i < word.size(); i++) {
    Symbol read = word[i];
    bool found = false;
    for (Transition transition : current_state->get_transitions()) {
      if (transition.get_read() == read && transition.get_remove_from_stack() == stack.top()) {
        stack.pop();
        for (char symbol : transition.get_insert_into_stack()) {
          stack.push(symbol);
        }
        current_state = transition.get_destination();
        found = true;
        break;
      }
    }
    if (!found) return false;
  }
  return true;
}