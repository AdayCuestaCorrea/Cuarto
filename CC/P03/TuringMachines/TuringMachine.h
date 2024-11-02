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

#pragma once

#include "Elements/State/State.h"
#include <iostream>

#include <memory>

typedef char Symbol;
typedef std::vector<std::shared_ptr<State>> States;
typedef std::vector<Symbol> Alphabet;

class TuringMachine {
 public:
  TuringMachine(const States& states, std::shared_ptr<State> initial_state, const Alphabet& alphabet)
           : states_(states), initial_state_(initial_state), alphabet_(alphabet) {}
  virtual bool execute(std::string word) = 0;
  virtual void print(std::ostream& os) const = 0; // Pure virtual function

  friend std::ostream& operator<<(std::ostream& os, const TuringMachine& machine) {
    machine.print(os);
    return os;
  }
 protected:
  States states_;
  std::shared_ptr<State> initial_state_;
  Alphabet alphabet_;
};