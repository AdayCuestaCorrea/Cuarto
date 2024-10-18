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
};