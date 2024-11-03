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

std::vector<std::shared_ptr<State>> TuringMachineLoader::loadStates(const json& j) {
  std::vector<std::shared_ptr<State>> states;
  for (const auto& state : j["states"]) {
    states.push_back(std::make_shared<State>(state.get<std::string>(), false));
  }

  for (const auto& state : states) {
    if (state->getName() == j["initial_state"].get<std::string>()) {
      state->setInitial(true);
    }
    for (const auto& final_state : j["final_states"]) {
      if (state->getName() == final_state.get<std::string>()) {
        state->setFinal(true);
      }
    }
  }

  return states;
}

Alphabet TuringMachineLoader::loadAlphabet(const json& j, const std::string& key) {
  Alphabet alphabet;
  for (const auto& symbol : j[key]) {
    alphabet.push_back(symbol.get<std::string>()[0]);
  }
  return alphabet;
}

bool TuringMachineLoader::checkStates(const json& j) {
  if (!j["states"].is_array() || j["states"].empty()) {
    std::cerr << "Error: 'states' must be a non-empty array" << std::endl;
    return false;
  }
  return true;
}

bool TuringMachineLoader::checkAlphabets(const json& j) {
  if (!j["input_alphabet"].is_array() || j["input_alphabet"].empty()) {
    std::cerr << "Error: 'input_alphabet' must be a non-empty array" << std::endl;
    return false;
  }
  for (const auto& symbol : j["input_alphabet"]) {
    if (!symbol.is_string() || symbol.get<std::string>().length() != 1) {
      std::cerr << "Error: 'input_alphabet' must contain single-character strings" << std::endl;
      return false;
    }
  }

  if (!j["tape_alphabet"].is_array() || j["tape_alphabet"].empty()) {
    std::cerr << "Error: 'tape_alphabet' must be a non-empty array" << std::endl;
    return false;
  }
  for (const auto& symbol : j["tape_alphabet"]) {
    if (!symbol.is_string() || symbol.get<std::string>().length() != 1) {
      std::cerr << "Error: 'tape_alphabet' must contain single-character strings" << std::endl;
      return false;
    }
  }

  std::unordered_set<std::string> tape_alphabet_set(j["tape_alphabet"].begin(), j["tape_alphabet"].end());
  for (const auto& symbol : j["input_alphabet"]) {
    if (tape_alphabet_set.find(symbol.get<std::string>()) == tape_alphabet_set.end()) {
      std::cerr << "Error: 'input_alphabet' must be contained in 'tape_alphabet'" << std::endl;
      return false;
    }
  }

  return true;
}

bool TuringMachineLoader::checkInitialState(const json& j) {
  if (!j["initial_state"].is_string() || j["initial_state"].empty()) {
    std::cerr << "Error: 'initial_state' must be a non-empty string" << std::endl;
    return false;
  }
  std::unordered_set<std::string> states_set(j["states"].begin(), j["states"].end());
  if (states_set.find(j["initial_state"].get<std::string>()) == states_set.end()) {
    std::cerr << "Error: 'initial_state' must be contained in 'states'" << std::endl;
    return false;
  }
  return true;
}

bool TuringMachineLoader::checkBlankSymbol(const json& j) {
  if (!j["blank_symbol"].is_string() || j["blank_symbol"].empty() || j["blank_symbol"] != ".") {
    std::cerr << "Error: 'blank_symbol' must be a non-empty string with a dot -> \".\"" << std::endl;
    return false;
  }
  return true;
}

bool TuringMachineLoader::checkFinalStates(const json& j) {
  if (!j["final_states"].is_array() || j["final_states"].empty()) {
    std::cerr << "Error: 'final_states' must be a non-empty array" << std::endl;
    return false;
  }

  std::unordered_set<std::string> states_set(j["states"].begin(), j["states"].end());
  for (const auto& state : j["final_states"]) {
    if (states_set.find(state.get<std::string>()) == states_set.end()) {
      std::cerr << "Error: 'final_states' must be contained in 'states'" << std::endl;
      return false;
    }
  }

  return true;
}

bool TuringMachineLoader::checkTransitionStates(const json& transition, const std::unordered_set<std::string>& states_set) {
  if (states_set.find(transition["current_state"].get<std::string>()) == states_set.end()) {
    std::cerr << "Error: 'current_state' in transition must be in 'states'" << std::endl;
    return false;
  }

  if (states_set.find(transition["next_state"].get<std::string>()) == states_set.end()) {
    std::cerr << "Error: 'next_state' in transition must be in 'states'" << std::endl;
    return false;
  }

  return true;
}