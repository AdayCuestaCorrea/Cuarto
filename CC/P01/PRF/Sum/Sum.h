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

#include "../PRF.h"
#include "../../BRF/SuccessorFunction/SuccessorFunction.h"
#include "../../BRF/ProyectionFunction/ProyectionFunction.h"

/**
 * @class Sum
 * @brief A class representing the sum function as a primitive recursive function.
 *
 * This class inherits from PrimitiveRecursiveFunctions and implements the sum function
 * using primitive recursion. It calculates the sum of two numbers and stores the result.
 */
class Sum : public PrimitiveRecursiveFunctions {
 public:
  /**
   * @brief Constructor that initializes the sum function.
   * @param numberX The first number.
   * @param numberY The second number.
   *
   * The constructor calculates the sum of numberX and numberY using the calculateSum method
   * and stores the result in the inherited result member.
   */
  Sum(int numberX, int numberY) {
    result = calculateSum(numberX, numberY);
  }

 private:
  /**
   * @brief Calculates the sum of two numbers using primitive recursion.
   * @param numberX The first number.
   * @param numberY The second number.
   * @return The sum of numberX and numberY.
   *
   * This method implements the sum function using primitive recursion.
   */
  int calculateSum(int numberX, int numberY);
};