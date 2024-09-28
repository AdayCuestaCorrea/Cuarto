/** Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Complejidad Computacional
  * Curso: 4º
  * Práctica 1: Potencia
  * Autor: Aday Cuesta Correa
  * Correo: alu0101483887@ull.edu.es
  * Fecha: 26/09/2024
  */

#pragma once

/**
 * @class BasicRecursiveFunctions
 * @brief An abstract base class for basic recursive functions.
 *
 * This class provides an interface for basic recursive functions. It declares a pure virtual
 * function `execute` that must be implemented by derived classes.
 */
class BasicRecursiveFunctions {
 public:
  /**
   * @brief Pure virtual function to execute the recursive function.
   * @return The result of the recursive function.
   *
   * This function must be implemented by any class that inherits from BasicRecursiveFunctions.
   */
  virtual int execute() = 0;
};