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
#include <vector>

#include "../Transition/Transition.h"

class State {
 public:
  State() {};
  State(std::string name, bool is_initial, bool is_final) : name_(name), is_initial_(is_initial), is_final_(is_final) {};
  State(std::string name, bool is_initial) : name_(name), is_initial_(is_initial) {};
  std::string get_name() const { return name_; }
  bool is_initial() const { return is_initial_; }
  bool is_final() const { return is_final_; }
  std::vector<Transition> get_transitions() const { return transitions_; }
  void add_transition(Transition transition) { transitions_.push_back(transition); }

 private:
  std::string name_;
  bool is_initial_;
  bool is_final_ = false;
  std::vector<Transition> transitions_;
};