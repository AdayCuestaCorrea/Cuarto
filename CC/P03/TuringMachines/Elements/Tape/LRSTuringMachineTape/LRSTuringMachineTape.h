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
#include "../Tape.h"

/**
 * @class LRSTuringMachineTape
 * @brief A class representing a tape for a single-tape Turing machine.
 */
class LRSTuringMachineTape : public Tape, public StayableTape, public MovableTape {
 public:
  LRSTuringMachineTape(const Alphabet& tape_alphabet) : Tape(tape_alphabet) {}
  LRSTuringMachineTape(const Alphabet& tape_alphabet, const std::string& content) : Tape(tape_alphabet) {
    setContent(content);
  }

  char read() const override;
  void write(char symbol) override;
  void moveLeft() override;
  void moveRight() override;
  void stay() override {
    // Do nothing
  }
  
  std::string getContent() const override { 
    std::string content;
    for (char symbol : tape_) {
      content += symbol;
    }
    return content;
   }
  Alphabet getAlphabet() const override { return tape_alphabet_; }
  void setContent(const std::string& content) override {
    content_ = content;
    tape_.clear();
    for (char symbol : content) {
      tape_.push_back(symbol);
    }
    head_position_ = 0;
  }
};