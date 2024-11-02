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

class LRSTuringMachineTape : public MovableTape, public StayableTape {
 public:
  LRSTuringMachineTape(const Alphabet& tape_alphabet) : Tape(tape_alphabet) {}
  LRSTuringMachineTape(const Alphabet& tape_alphabet, std::string content) : Tape(tape_alphabet, content) {}

  char read() const override;

  void write(char symbol) override;

  void moveLeft() override;

  void moveRight() override;

  void stay() override {
    // Do nothing
  }
};