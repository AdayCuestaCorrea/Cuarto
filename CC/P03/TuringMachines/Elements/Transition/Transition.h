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

#include <string>
#include <vector>
#include <memory>

class State;
typedef char Symbol;

/**
 * @class Transition
 * @brief A class representing a transition in an automaton.
 * 
 */
class Transition {
 public:
  virtual ~Transition() = default;
  virtual std::shared_ptr<State> getDestination() const = 0;
  virtual std::vector<Symbol> getReadSymbols() const = 0;
  virtual std::vector<Symbol> getWriteSymbols() const = 0;
  virtual std::vector<char> getMoveDirections() const = 0;
};