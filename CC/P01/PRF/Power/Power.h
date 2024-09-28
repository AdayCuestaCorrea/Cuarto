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
#include "../Multiplication/Multiplication.h"

/**
 * @class Power
 * @brief A class representing the power function as a primitive recursive function.
 *
 * This class inherits from PrimitiveRecursiveFunctions and implements the power function
 * using primitive recursion. It calculates the power of a base number raised to an exponent
 * and stores the result.
 */
class Power : public PrimitiveRecursiveFunctions {
 public:
  /**
   * @brief Constructor that initializes the power function.
   * @param numberX The base number.
   * @param numberY The exponent.
   *
   * The constructor calculates the power of numberX raised to numberY using the calculatePower method
   * and stores the result in the inherited result member.
   */
  Power(int numberX, int numberY) {
    result = calculatePower(numberX, numberY);
  }

 private:
  /**
   * @brief Calculates the power of a base number raised to an exponent using primitive recursion.
   * @param numberX The base number.
   * @param numberY The exponent.
   * @return The result of numberX raised to the power of numberY.
   *
   * This method implements the power function using primitive recursion.
   */
  int calculatePower(int numberX, int numberY);
};