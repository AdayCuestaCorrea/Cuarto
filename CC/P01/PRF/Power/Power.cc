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

#include "Power.h"

/**
 * @brief Calculates the power of a base number raised to an exponent using primitive recursion.
 * @param numberX The base number.
 * @param numberY The exponent.
 * @return The result of numberX raised to the power of numberY.
 *
 * This method implements the power function using primitive recursion. It increments
 * the function call counter each time it is called. If numberY is 0, it uses a 
 * successor function to return 1 (the base case for exponentiation). Otherwise, it 
 * recursively calls itself with numberY decremented by 1 and multiplies the result 
 * by numberX.
 */
int Power::calculatePower(int numberX, int numberY) {
  PrimitiveRecursiveFunctions::functionCallCount++;
  if (numberY == 0) {
    BasicRecursiveFunctions* nullFunction = new NullFunction();
    BasicRecursiveFunctions* successorFunction = new SuccessorFunction(nullFunction->execute());
    return successorFunction->execute();
  }
  PrimitiveRecursiveFunctions* multiplication = new Multiplication(numberX, calculatePower(numberX, numberY - 1));
  return multiplication->getResult();
}