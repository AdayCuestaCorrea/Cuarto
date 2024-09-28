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

#include "SuccessorFunction.h"
#include "../../PRF/PRF.h"

/**
 * @brief Executes the successor function.
 * @return The successor of the given number.
 *
 * This method increments the function call counter and returns the successor
 * of the number provided during construction.
 */
int SuccessorFunction::execute() {
  PrimitiveRecursiveFunctions::functionCallCount++;
  return number_ + 1;
}