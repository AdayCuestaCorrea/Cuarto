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
  Transition(std::shared_ptr<State> destination, Symbol read, Symbol write, char movement) : 
             destination_(destination), read_(read), write_(write),
             movement_(movement) {};
  std::shared_ptr<State> getDestination() const { return destination_; }
  Symbol getRead() const { return read_; }
  Symbol getWrite() const { return write_; }
  char getMovement() const { return movement_; }

 private:
  std::shared_ptr<State> destination_;
  Symbol read_;
  Symbol write_;
  char movement_;
};