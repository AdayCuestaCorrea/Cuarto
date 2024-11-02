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

#pragma once

#include "../JSON_Library/json.hpp"
#include "../TuringMachines/TuringMachine.h"
#include <string>
#include <fstream>
#include <unordered_set>

using json = nlohmann::json;

class TuringMachineLoader {
 public:
  virtual std::shared_ptr<TuringMachine> load(const std::string& file_path) = 0;
  static std::string detectMachineType(const std::string& file_path);
 protected:
  virtual bool validFile(const std::string& file_path) = 0;
};