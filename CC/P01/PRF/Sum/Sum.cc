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

#include "Sum.h"

/**
 * @brief Calculates the sum of two numbers using primitive recursion.
 * @param numberX The first number.
 * @param numberY The second number.
 * @return The sum of numberX and numberY.
 *
 * This method implements the sum function using primitive recursion. It increments
 * the function call counter each time it is called. If numberY is 0, it uses a 
 * projection function to return numberX. Otherwise, it recursively calls itself 
 * with numberY decremented by 1 and adds 1 to the result.
 */
int Sum::calculateSum(int numberX, int numberY) {
  PrimitiveRecursiveFunctions::functionCallCount++;
  if (numberY == 0) {
    BasicRecursiveFunctions* proyectionFunction = new ProyectionFunction({numberX, numberY}, 0);
    return proyectionFunction->execute();
  }
  return calculateSum(numberX, numberY - 1) + 1;
}