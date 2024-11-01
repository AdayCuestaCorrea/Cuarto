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

using json = nlohmann::json;

class TuringMachineLoader {
 public:
  virtual std::shared_ptr<TuringMachine> execute(const std::string& input) = 0;
 protected:
  virtual bool validFile(std::string file_path) = 0;
};