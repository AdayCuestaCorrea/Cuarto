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

#include "../Types/MovableTape.h"
#include "../Types/StayableTape.h"

class AdvancedTMTape : public MovableTape, public StayableTape {
 public:
  AdvancedTMTape(std::string content) {
    for (char symbol : content) {
      tape_.push_back(symbol);
    }
    head_position_ = 0;
  }

  char read() const override;

  void write(char symbol) override;

  std::string getContent() const override;

  void moveLeft() override;

  void moveRight() override;

  void stay() override {
    // Do nothing
  }
};