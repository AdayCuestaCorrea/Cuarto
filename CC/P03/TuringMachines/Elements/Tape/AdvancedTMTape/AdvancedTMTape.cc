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

#include "AdvancedTMTape.h"

char AdvancedTMTape::read() const {
  return tape_[head_position_];
}

void AdvancedTMTape::write(char symbol) {
  tape_[head_position_] = symbol;
}

std::string AdvancedTMTape::getContent() const {
  std::string content;
  for (char symbol : tape_) {
    content += symbol;
  }
  return content;
}

void AdvancedTMTape::moveLeft() {
  if (head_position_ > 0) {
    head_position_--;
  } else {
    tape_.insert(tape_.begin(), '.');
  }
}

void AdvancedTMTape::moveRight() {
  head_position_++;
  if (head_position_ >= tape_.size()) {
    tape_.push_back('.');
  }
}