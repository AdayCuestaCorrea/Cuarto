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
#include "../../BRF/NullFunction/NullFunction.h"
#include "../Sum/Sum.h"

/**
 * @class Multiplication
 * @brief A class representing the multiplication function as a primitive recursive function.
 *
 * This class inherits from PrimitiveRecursiveFunctions and implements the multiplication function
 * using primitive recursion. It calculates the product of two numbers and stores the result.
 */
class Multiplication : public PrimitiveRecursiveFunctions {
 public:
  /**
   * @brief Constructor that initializes the multiplication function.
   * @param numberX The first number.
   * @param numberY The second number.
   *
   * The constructor calculates the product of numberX and numberY using the calculateMultiplication method
   * and stores the result in the inherited result member.
   */
  Multiplication(int numberX, int numberY) {
    result = calculateMultiplication(numberX, numberY);
  }

 private:
  /**
   * @brief Calculates the product of two numbers using primitive recursion.
   * @param numberX The first number.
   * @param numberY The second number.
   * @return The product of numberX and numberY.
   *
   * This method implements the multiplication function using primitive recursion.
   */
  int calculateMultiplication(int numberX, int numberY);
};