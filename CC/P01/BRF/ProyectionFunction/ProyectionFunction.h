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
#include <vector>

/**
 * @class ProyectionFunction
 * @brief A class representing the projection function as a basic recursive function.
 *
 * This class inherits from BasicRecursiveFunctions and implements the projection function,
 * which returns the element at a specified index from a given vector.
 */
class ProyectionFunction : public BasicRecursiveFunctions {
 public:
  /**
   * @brief Constructor that initializes the projection function with a given vector and index.
   * @param vector The vector from which to project an element.
   * @param index The index of the element to project.
   */
  ProyectionFunction(std::vector<int> vector, int index) : vector_(vector), index_(index) {};

  /**
   * @brief Executes the projection function.
   * @return The element at the specified index in the vector.
   *
   * This method returns the element at the index specified during construction.
   */
  int execute();

 private:
  std::vector<int> vector_;
  int index_;
};