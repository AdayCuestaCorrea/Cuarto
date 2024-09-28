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

#include "ProyectionFunction.h"
#include "../../PRF/PRF.h"

/**
 * @brief Executes the projection function.
 * @return The element at the specified index in the vector.
 *
 * This method increments the function call counter and returns the element at the index
 * specified during construction. If the index is out of bounds (less than 0 or greater than
 * or equal to the size of the vector), it returns the first or last element of the vector, respectively.
 */
int ProyectionFunction::execute() {
  PrimitiveRecursiveFunctions::functionCallCount++;
  if(index_ < 0) return vector_[0];
  if(index_ >= vector_.size()) return vector_.back();
  return vector_[index_];
}