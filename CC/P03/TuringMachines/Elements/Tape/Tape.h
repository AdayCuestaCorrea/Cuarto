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


/**
 * @class Tape
 * @brief Abstract base class representing a tape in a Turing machine.
 *
 * The Tape class provides an interface for reading from and writing to a tape,
 * as well as managing the tape's content and alphabet. It is an abstract class
 * and must be inherited by concrete implementations.
 *
 * @param tape_alphabet The alphabet used by the tape.
 * @param content The initial content of the tape.
 */
class Tape {
 public:
  Tape(const Alphabet& tape_alphabet) : tape_alphabet_(tape_alphabet) {}
  Tape(const Alphabet& tape_alphabet, const std::string& content) : tape_alphabet_(tape_alphabet), content_(content) {}

  virtual char read() const = 0;
  virtual void write(char symbol) = 0;

  virtual std::string getContent() const = 0;
  virtual void setContent(const std::string& content) = 0;
  virtual Alphabet getAlphabet() const = 0;

  virtual int getHeadPosition() const = 0;

  virtual ~Tape() = default;

 protected:
  std::vector<char> tape_;
  int head_position_ = 0;
  Alphabet tape_alphabet_;
  std::string content_;
};