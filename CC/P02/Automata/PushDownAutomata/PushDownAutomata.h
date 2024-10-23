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

#pragma once

#include "../Automata.h"
#include <stack>

/**
 * @class PushDownAutomata
 * @brief A class representing a Push Down Automata (PDA), which is a type of automaton that employs a stack.
 * 
 * This class extends the Automata class and adds functionality specific to PDAs, including stack operations.
 * 
 * @param states A collection of states in the automaton.
 * @param initial_state The initial state of the automaton.
 * @param alphabet The input alphabet of the automaton.
 * @param stack_alphabet The alphabet of the stack used by the automaton.
 * @param stack The stack used by the automaton.
 */
class PushDownAutomata : public Automata {
 public:
  PushDownAutomata(States states, std::shared_ptr<State> initial_state, const Alphabet& alphabet,
                   const Alphabet& stack_alphabet, std::stack<Symbol> stack) 
                   : Automata(states, initial_state, alphabet), 
                     stack_alphabet_(stack_alphabet), stack_(stack) {}
  bool execute(std::string word) override;
  void print(std::ostream& os) const override;
 private:
  std::stack<Symbol> stack_;
  Alphabet stack_alphabet_;
  bool executeRecursive(std::shared_ptr<State> current_state, const std::string& word, int index, std::stack<Symbol>& stack);
};