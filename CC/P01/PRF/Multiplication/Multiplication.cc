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

#include "Multiplication.h"

/**
 * @brief Calculates the product of two numbers using primitive recursion.
 * @param numberX The first number.
 * @param numberY The second number.
 * @return The product of numberX and numberY.
 *
 * This method implements the multiplication function using primitive recursion. It increments
 * the function call counter each time it is called. If numberY is 0, it uses a 
 * null function to return 0 (the base case for multiplication). Otherwise, it 
 * recursively calls itself with numberY decremented by 1 and adds numberX to the result
 * of the recursive call.
 */
int Multiplication::calculateMultiplication(int numberX, int numberY) {
  PrimitiveRecursiveFunctions::functionCallCount++;
  if (numberY == 0) {
    BasicRecursiveFunctions* nullFunction = new NullFunction();
    return nullFunction->execute();
  }
  PrimitiveRecursiveFunctions* sum = new Sum(numberX, calculateMultiplication(numberX, numberY - 1));
  return sum->getResult();
}