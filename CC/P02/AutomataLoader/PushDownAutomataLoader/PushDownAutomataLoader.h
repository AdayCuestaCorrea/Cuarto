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

#include "../AutomataLoader.h"
#include "../../Automata/PushDownAutomata/PushDownAutomata.h"

class PushDownAutomataLoader : public AutomataLoader {
 public:
  std::shared_ptr<Automata> load(std::string file_path) override;
 private:
  std::vector<std::vector<std::string>> readFile(std::string file_path);
  bool validFile(std::string file_path) override;
  bool checkForDuplicates();
  bool checkFileLength();
  bool validateAlphabet(const std::vector<std::string>& alphabet, bool isStackAlphabet);
  bool validateInitialState(const std::vector<std::string>& states, const std::vector<std::string>& initialState);
  bool validateInitialStack(const std::vector<std::string>& states, const std::vector<std::string>& initialState);
  bool validateTransitions(const std::vector<std::string>& states, const std::vector<std::string>& alphabet, const std::vector<std::string>& stack_alphabet);
  void loadStates(States& states, std::shared_ptr<State>& initial_state);
  void loadAlphabet(Alphabet& alphabet);
  void loadStackAlphabet(Alphabet& stack_alphabet);
  void loadInitialStack(std::stack<Symbol>& stack);
  void loadTransitions(States& states);
};