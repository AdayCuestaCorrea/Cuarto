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

#include <vector>

/**
 * @class PrimitiveRecursiveFunctions
 * @brief A class representing primitive recursive functions.
 *
 * This class provides a base for implementing primitive recursive functions.
 * It includes a static counter to track the number of function calls and methods
 * to retrieve the result of the function and the function call count.
 */
class PrimitiveRecursiveFunctions {
 public:
  /**
   * @brief Static counter to track the number of function calls.
   */
  static int functionCallCount;

  /**
   * @brief Get the result of the function.
   * @return The result of the function.
   */
  int getResult() { return result; }

  /**
   * @brief Get the number of function calls.
   * @return The number of function calls.
   */
  int getFunctionCallCount() { return functionCallCount; }

 protected:
  int result;
};