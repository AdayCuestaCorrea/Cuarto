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

#include "../TuringMachineLoader.h"

class MultitapeTMLoader : public TuringMachineLoader {
 public:
  std::shared_ptr<TuringMachine> load(const std::string& file_path) override;
 protected:
  bool validFile(const std::string& file_path) override;
};