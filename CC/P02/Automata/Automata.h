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

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Elements/State/State.h"

typedef char Symbol;
typedef std::vector<std::shared_ptr<State>> States;
typedef std::vector<Symbol> Alphabet;

/**
 * @class Automata
 * @brief Abstract base class representing a finite automaton.
 *
 * This class provides the basic structure and interface for a finite automaton.
 * It includes the states, initial state, and alphabet of the automaton.
 * Derived classes must implement the execute and print methods.
 *
 * @param states A collection of states that the automaton can be in.
 * @param initial_state A shared pointer to the initial state of the automaton.
 * @param alphabet The alphabet of the automaton.
 */
class Automata {
 public:
  Automata(const States& states, std::shared_ptr<State> initial_state, const Alphabet& alphabet)
           : states_(states), initial_state_(initial_state), alphabet_(alphabet) {}
  virtual bool execute(std::string word) = 0;
  virtual void print(std::ostream& os) const = 0; // Pure virtual function

  friend std::ostream& operator<<(std::ostream& os, const Automata& automaton) {
    automaton.print(os);
    return os;
  }
 protected:
  States states_;
  std::shared_ptr<State> initial_state_;
  Alphabet alphabet_;
};