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

#include "TuringMachineLoader.h"

std::string TuringMachineLoader::detectMachineType(const std::string& file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file");
  }

  json turing_machine_file;
  file >> turing_machine_file;

  if (turing_machine_file.find("transitions") != turing_machine_file.end()) {
    for (const auto& transition : turing_machine_file["transitions"]) {
      if (transition.find("read_symbols") != transition.end() && transition["read_symbols"].is_array()) {
        if (transition["read_symbols"].size() > 1) {
          return "Multitape";
        }
      }
      if (transition.find("write_symbols") != transition.end() && transition["write_symbols"].is_array()) {
        if (transition["write_symbols"].size() > 1) {
          return "Multitape";
        }
      }
    }
  }

  return "SingleTape";
}