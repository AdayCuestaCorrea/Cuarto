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

  template <typename T> bool contains(const std::vector<T>& vector, const T& element) {
    for (const auto& current_element : vector) {
      if (current_element == element) {
        return true;
      }
    }
    return false;
  }
}