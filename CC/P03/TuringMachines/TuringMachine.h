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
#include <variant>
#include <memory>

typedef char Symbol;
typedef std::vector<std::shared_ptr<State>> States;
typedef std::vector<Symbol> Alphabet;
typedef std::variant<std::string, std::vector<std::string>> InputType;

/**
 * @class TuringMachine
 * @brief Abstract base class representing a Turing Machine.
 *
 * This class provides the basic structure and interface for a Turing Machine.
 * It includes the states, initial state, and alphabet of the machine.
 * Derived classes must implement the execute and print methods.
 *
 * @param states A collection of states that the Turing Machine can be in.
 * @param initial_state The initial state of the Turing Machine.
 * @param alphabet The alphabet used by the Turing Machine.
 */
class TuringMachine {
 public:
  TuringMachine(const States& states, std::shared_ptr<State> initial_state, const Alphabet& alphabet)
           : states_(states), initial_state_(initial_state), alphabet_(alphabet) {}
           
  virtual std::string execute(InputType input) = 0;
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