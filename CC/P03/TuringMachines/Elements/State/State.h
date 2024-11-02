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

#include "../Transition/Transition.h"

/**
 * @class State
 * @brief A class representing a state in an automaton.
 * 
 */
class State {
 public:
  State() = default;
  State(std::string name, bool is_initial, bool is_final) : name_(name), is_initial_(is_initial), is_final_(is_final) {}
  State(std::string name, bool is_initial) : name_(name), is_initial_(is_initial) {}

  std::string getName() const { return name_; }
  void setInitial(bool is_initial) { is_initial_ = is_initial; }
  void setFinal(bool is_final) { is_final_ = is_final; }
  bool isInitial() const { return is_initial_; }
  bool isFinal() const { return is_final_; }

  std::vector<std::shared_ptr<Transition>> getTransitions() const { return transitions_; }
  void addTransition(std::shared_ptr<Transition> transition) { transitions_.push_back(transition); }

 private:
  std::string name_;
  bool is_initial_ = false;
  bool is_final_ = false;
  std::vector<std::shared_ptr<Transition>> transitions_;
};