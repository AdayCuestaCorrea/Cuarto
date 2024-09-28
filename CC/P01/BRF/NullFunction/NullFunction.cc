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

#include "NullFunction.h"
#include "../../PRF/PRF.h"

/**
 * @brief Executes the null function.
 * @return Always returns 0.
 *
 * This method increments the function call counter and returns 0, representing the null function.
 */
int NullFunction::execute() {
  PrimitiveRecursiveFunctions::functionCallCount++;
  return 0;
}