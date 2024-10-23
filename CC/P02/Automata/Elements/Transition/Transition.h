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
  Transition(std::shared_ptr<State> destination, Symbol read, Symbol remove_from_stack, std::string insert_into_stack) : 
             destination_(destination), read_(read), remove_from_stack_(remove_from_stack),
             insert_into_stack_(insert_into_stack) {};
  std::shared_ptr<State> get_destination() const { return destination_; }
  Symbol get_read() const { return read_; }
  Symbol get_remove_from_stack() const { return remove_from_stack_; }
  std::string get_insert_into_stack() const { return insert_into_stack_; }

 private:
  std::shared_ptr<State> destination_;
  Symbol read_;
  Symbol remove_from_stack_;
  std::string insert_into_stack_;
};