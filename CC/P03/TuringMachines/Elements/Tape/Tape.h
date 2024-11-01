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

class Tape {
 public:
  virtual char read() const = 0;
  virtual void write(char symbol) = 0;
  virtual std::string getContent() const = 0;
  virtual ~Tape() = default;

 protected:
  std::vector<char> tape_;
  int head_position_;
};