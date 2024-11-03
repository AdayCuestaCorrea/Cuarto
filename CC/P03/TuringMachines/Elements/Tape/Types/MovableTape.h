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

/*
 * @class MovableTape
 * @brief Interface for tapes that can move left and right.
 */
class MovableTape {
 public:
  virtual void moveLeft() = 0;
  virtual void moveRight() = 0;
};