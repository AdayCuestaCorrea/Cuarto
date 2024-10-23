/** Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Complejidad Computacional
  * Curso: 4º
  * Práctica 2: Autómata De Pila
  * Autor: Aday Cuesta Correa
  * Correo: alu0101483887@ull.edu.es
  * Fecha: 16/10/2024
  */

#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>

namespace Utility {
  void help(int argc, char* argv[]);
  bool hasComment(const std::string& line);
  std::string removeComments(const std::string& line);
  void leftTrim(std::string& string);
  void rightTrim(std::string& string);

  /**
   * @brief Checks if a vector contains duplicate elements.
   * 
   * This function iterates through the given vector and uses an unordered set
   * to track the elements that have been seen. If an element is found in the set,
   * it means the vector contains duplicates and the function returns true.
   * Otherwise, it returns false.
   * 
   * @tparam T The type of the elements in the vector.
   * @param vector The vector to be checked for duplicates.
   * @return true if the vector contains duplicate elements, false otherwise.
   */
  template <typename T> bool hasDuplicates(const std::vector<T>& vector) {
    std::unordered_set<T> seen;
    for (const auto& element : vector) {
      if (seen.find(element) != seen.end()) {
        return true; // Duplicate found
      }
      seen.insert(element);
    }
    return false; // No duplicates found
  }

  /**
   * @brief Checks if a 2D vector contains any duplicate rows.
   * 
   * This function iterates through each pair of rows in the given 2D vector
   * and compares them to determine if there are any duplicates.
   * 
   * @tparam T The type of elements contained in the 2D vector.
   * @param vector The 2D vector to be checked for duplicate rows.
   * @return true if there are duplicate rows in the 2D vector, false otherwise.
   */
  template <typename T> bool hasDuplicates(const std::vector<std::vector<T>>& vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
      for (size_t j = i + 1; j < vector.size(); ++j) {
        if (vector[i] == vector[j]) {
          return true; // Duplicate found
        }
      }
    }
    return false; // No duplicates found
  }

  /**
   * @brief Checks if a vector contains a specific element.
   * 
   * This function iterates through the given vector to determine if it contains
   * the specified element. It returns true if the element is found, otherwise false.
   * 
   * @tparam T The type of the elements in the vector.
   * @param vector The vector to search through.
   * @param element The element to search for in the vector.
   * @return true If the element is found in the vector.
   * @return false If the element is not found in the vector.
   */
  template <typename T> bool contains(const std::vector<T>& vector, const T& element) {
    for (const auto& current_element : vector) {
      if (current_element == element) {
        return true;
      }
    }
    return false;
  }
}