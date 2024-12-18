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
#include "../../TuringMachines/MultitapeTuringMachine/MultitapeTuringMachine.h"

/*
 * @class MultitapeTMLoader
 * @brief Loads multitape Turing machines from JSON files.
 */
class MultitapeTMLoader : public TuringMachineLoader {
 public:
  std::shared_ptr<TuringMachine> load(const std::string& file_path) override;
 protected:
  bool validFile(const std::string& file_path) override;
 private:
  std::vector<LRSTuringMachineTape> loadTapes(const json& j);
  void loadTransitions(const json& j, const std::vector<std::shared_ptr<State>>& states);
  bool checkRequiredFields(const json& j);
  bool checkNumberOfTapes(const json& j);
  bool checkTransitions(const json& j);
  bool checkTransitionFields(const json& transition);
  bool checkTransitionSymbols(const json& transition, const std::unordered_set<std::string>& input_alphabet_set, const std::unordered_set<std::string>& tape_alphabet_set);
};