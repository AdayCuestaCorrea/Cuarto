/** Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Complejidad Computacional
  * Curso: 4º
  * Práctica 3: Máquina de Turing
  * Autor: Aday Cuesta Correa
  * Correo: alu0101483887@ull.edu.es
  * Fecha: 01/11/2024
  */

#include "MultitapeTMLoader.h"

std::shared_ptr<TuringMachine> MultitapeTMLoader::load(const std::string& file_path) {
  if (!validFile(file_path)) throw std::runtime_error("Invalid file: " + file_path);
  return nullptr;
}

bool MultitapeTMLoader::validFile(const std::string& file_path) {
  return false;
}