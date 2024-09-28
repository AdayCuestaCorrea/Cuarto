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

#include "../BRF.h"

/**
 * @class NullFunction
 * @brief A class representing the null function as a basic recursive function.
 *
 * This class inherits from BasicRecursiveFunctions and implements the null function,
 * which always returns 0.
 */
class NullFunction : public BasicRecursiveFunctions {
 public:
  /**
   * @brief Executes the null function.
   * @return Always returns 0.
   *
   * This method returns 0, representing the null function.
   */
  int execute();
};