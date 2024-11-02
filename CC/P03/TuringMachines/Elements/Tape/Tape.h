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

typedef char Symbol;
typedef std::vector<Symbol> Alphabet;

class Tape {
 public:
  Tape(const Alphabet& tape_alphabet) : tape_alphabet_(tape_alphabet) {}
  Tape(const Alphabet& tape_alphabet, std::string content) : tape_alphabet_(tape_alphabet) {
    for (char symbol : content) {
      tape_.push_back(symbol);
    }
  }
  
  virtual char read() const = 0;

  virtual void write(char symbol) = 0;

  std::string getContent() const { return content_; }

  Alphabet getAlphabet() const { return tape_alphabet_; }

  void setContent(std::string content) {
    content_ = content;
    tape_.clear();
    for (char symbol : content) {
      tape_.push_back(symbol);
    }
  }

  virtual ~Tape() = default;

 protected:
  std::vector<char> tape_;
  int head_position_ = 0;
  Alphabet tape_alphabet_;
  std::string content_;
};