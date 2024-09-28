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
 * @class SuccessorFunction
 * @brief A class representing the successor function as a basic recursive function.
 *
 * This class inherits from BasicRecursiveFunctions and implements the successor function,
 * which returns the successor of a given number.
 */
class SuccessorFunction : public BasicRecursiveFunctions {
 public:
  /**
   * @brief Constructor that initializes the successor function with a given number.
   * @param number The number to find the successor of.
   */
  SuccessorFunction(int number) : number_(number) {};

  /**
   * @brief Executes the successor function.
   * @return The successor of the given number.
   *
   * This method returns the successor of the number provided during construction.
   */
  int execute();

 private:
  int number_;
};