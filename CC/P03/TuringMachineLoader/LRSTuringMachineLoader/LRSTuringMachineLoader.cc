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

#include "LRSTuringMachineLoader.h"

std::shared_ptr<TuringMachine> LRSTuringMachineLoader::load(const std::string& file_path) {
  if (!validFile(file_path)) throw std::runtime_error("Invalid file: " + file_path);

  std::ifstream file(file_path);
  json j;
  file >> j;

  States states = loadStates(j);
  Alphabet input_alphabet = loadAlphabet(j, "input_alphabet");
  Alphabet tape_alphabet = loadAlphabet(j, "tape_alphabet");
  LRSTuringMachineTape tape = loadTape(j);

  loadTransitions(j, states);

  std::shared_ptr<State> initial_state = *std::find_if(states.begin(), states.end(), [&](const std::shared_ptr<State>& state) {
    return state->isInitial();
  });

  return std::make_shared<LRSTuringMachine>(states, initial_state, input_alphabet, tape);
}

LRSTuringMachineTape LRSTuringMachineLoader::loadTape(const json& j) {
  Alphabet tape_alphabet = loadAlphabet(j, "tape_alphabet");
  return LRSTuringMachineTape(tape_alphabet);
}

void LRSTuringMachineLoader::loadTransitions(const json& j, const std::vector<std::shared_ptr<State>>& states) {
  for (const auto& transition : j["transitions"]) {
    std::shared_ptr<State> current_state;
    for (const auto& state : states) {
      if (state->getName() == transition["current_state"].get<std::string>()) {
        current_state = state;
        break;
      }
    }

    std::shared_ptr<State> next_state;
    for (const auto& state : states) {
      if (state->getName() == transition["next_state"].get<std::string>()) {
        next_state = state;
        break;
      }
    }

    std::shared_ptr<Transition> new_transition = std::make_shared<SingleTapeTransition>(
      next_state,
      transition["read_symbol"].get<std::string>()[0],
      transition["write_symbol"].get<std::string>()[0],
      transition["move_direction"].get<std::string>()[0]
    );

    current_state->addTransition(new_transition);
  }
}

bool LRSTuringMachineLoader::validFile(const std::string& file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << file_path << std::endl;
    return false;
  }

  json j;
  file >> j;

  return checkRequiredFields(j) &&
         checkStates(j) &&
         checkAlphabets(j) &&
         checkInitialState(j) &&
         checkBlankSymbol(j) &&
         checkFinalStates(j) &&
         checkTransitions(j);
}

bool LRSTuringMachineLoader::checkRequiredFields(const json& j) {
  std::vector<std::string> required_fields = {
    "states", "input_alphabet", "tape_alphabet", "initial_state", "blank_symbol", "final_states", "transitions"
  };
  for (const auto& field : required_fields) {
    if (j.find(field) == j.end()) {
      std::cerr << "Error: Missing required field " << field << std::endl;
      return false;
    }
  }
  return true;
}

bool LRSTuringMachineLoader::checkTransitions(const json& j) {
  if (!j["transitions"].is_array() || j["transitions"].empty()) {
    std::cerr << "Error: 'transitions' must be a non-empty array" << std::endl;
    return false;
  }

  std::unordered_set<std::string> transition_set;
  std::unordered_set<std::string> input_alphabet_set(j["input_alphabet"].begin(), j["input_alphabet"].end());
  std::unordered_set<std::string> tape_alphabet_set(j["tape_alphabet"].begin(), j["tape_alphabet"].end());
  std::unordered_set<std::string> states_set(j["states"].begin(), j["states"].end());

  for (const auto& transition : j["transitions"]) {
    if (!checkTransitionFields(transition)) return false;
    if (!checkTransitionSymbols(transition, input_alphabet_set, tape_alphabet_set)) {
      return false;
    }
    if (!checkTransitionStates(transition, states_set)) return false;
    
    std::string key = transition["current_state"].get<std::string>() + "_" + transition["read_symbol"].get<std::string>();
    if (transition_set.find(key) != transition_set.end()) {
      std::cerr << "Error: Deterministic Turing Machine cannot have multiple transitions from the same state reading the same symbol" << std::endl;
      return false;
    }
    transition_set.insert(key);
  }

  return true;
}

bool LRSTuringMachineLoader::checkTransitionFields(const json& transition) {
  if (!transition.is_object() ||
      transition.find("current_state") == transition.end() ||
      transition.find("read_symbol") == transition.end() ||
      transition.find("next_state") == transition.end() ||
      transition.find("write_symbol") == transition.end() ||
      transition.find("move_direction") == transition.end()) {
    std::cerr << "Error: Each transition must be an object with fields 'current_state', 'read_symbol', 'next_state', 'write_symbol', and 'move_direction'" << std::endl;
    return false;
  }

  if (transition["move_direction"].get<std::string>() != "L" && transition["move_direction"].get<std::string>() != "R" && transition["move_direction"].get<std::string>() != "S") {
    std::cerr << "Error: 'move_direction' in transition must be 'L', 'R', or 'S'" << std::endl;
    return false;
  }

  return true;
}

bool LRSTuringMachineLoader::checkTransitionSymbols(const json& transition, const std::unordered_set<std::string>& input_alphabet_set, const std::unordered_set<std::string>& tape_alphabet_set) {
  if (tape_alphabet_set.find(transition["read_symbol"].get<std::string>()) == tape_alphabet_set.end()) {
    std::cerr << "Error: 'read_symbol' in transition must be in 'tape_alphabet'" << std::endl;
    return false;
  }

  if (tape_alphabet_set.find(transition["write_symbol"].get<std::string>()) == tape_alphabet_set.end()) {
    std::cerr << "Error: 'write_symbol' in transition must be in 'tape_alphabet'" << std::endl;
    return false;
  }

  return true;
}