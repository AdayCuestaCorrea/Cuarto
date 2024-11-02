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

  std::ifstream file(file_path);
  json j;
  file >> j;

  States states = loadStates(j);
  Alphabet input_alphabet = loadAlphabet(j, "input_alphabet");
  Alphabet tape_alphabet = loadAlphabet(j, "tape_alphabet");
  std::vector<LRSTuringMachineTape> tapes = loadTapes(j);
  loadTransitions(j, states);

  std::shared_ptr<State> initial_state = *std::find_if(states.begin(), states.end(), [&](const std::shared_ptr<State>& state) {
    return state->isInitial();
  });

  return std::make_shared<MultitapeTuringMachine>(states, initial_state, input_alphabet, tapes);
}

bool MultitapeTMLoader::validFile(const std::string& file_path) {
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

std::vector<std::shared_ptr<State>> MultitapeTMLoader::loadStates(const json& j) {
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

Alphabet MultitapeTMLoader::loadAlphabet(const json& j, const std::string& key) {
  Alphabet alphabet;
  for (const auto& symbol : j[key]) {
    alphabet.push_back(symbol.get<std::string>()[0]);
  }
  return alphabet;
}

std::vector<LRSTuringMachineTape> MultitapeTMLoader::loadTapes(const json& j) {
  Alphabet tape_alphabet = loadAlphabet(j, "tape_alphabet");
  std::vector<LRSTuringMachineTape> tapes;

  // Determinar el número de cintas basado en el tamaño del vector read_symbols en la primera transición
  if (j.contains("transitions") && j["transitions"].is_array() && !j["transitions"].empty()) {
    size_t num_tapes = j["transitions"][0]["read_symbols"].size();
    for (size_t i = 0; i < num_tapes; ++i) {
      tapes.emplace_back(tape_alphabet);
    }
  }

  return tapes;
}

void MultitapeTMLoader::loadTransitions(const json& j, const std::vector<std::shared_ptr<State>>& states) {
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

    std::vector<Symbol> read_symbols;
    for (const auto& symbol : transition["read_symbols"]) {
      read_symbols.push_back(symbol.get<std::string>()[0]);
    }

    std::vector<Symbol> write_symbols;
    for (const auto& symbol : transition["write_symbols"]) {
      write_symbols.push_back(symbol.get<std::string>()[0]);
    }

    std::vector<char> move_directions;
    for (const auto& direction : transition["move_directions"]) {
      move_directions.push_back(direction.get<std::string>()[0]);
    }

    auto new_transition = std::make_shared<MultiTapeTransition>(
      next_state,
      read_symbols,
      write_symbols,
      move_directions
    );

    current_state->addTransition(new_transition);
  }
}

bool MultitapeTMLoader::checkRequiredFields(const json& j) {
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

bool MultitapeTMLoader::checkStates(const json& j) {
  if (!j["states"].is_array() || j["states"].empty()) {
    std::cerr << "Error: 'states' must be a non-empty array" << std::endl;
    return false;
  }
  return true;
}

bool MultitapeTMLoader::checkAlphabets(const json& j) {
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

bool MultitapeTMLoader::checkInitialState(const json& j) {
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

bool MultitapeTMLoader::checkBlankSymbol(const json& j) {
  if (!j["blank_symbol"].is_string() || j["blank_symbol"].empty() || j["blank_symbol"] != ".") {
    std::cerr << "Error: 'blank_symbol' must be a non-empty string with a dot -> \".\"" << std::endl;
    return false;
  }
  return true;
}

bool MultitapeTMLoader::checkFinalStates(const json& j) {
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

bool MultitapeTMLoader::checkTransitions(const json& j) {
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

    std::string read_symbols_key;
    for (const auto& symbol : transition["read_symbols"]) {
      read_symbols_key += symbol.get<std::string>();
    }

    std::string key = transition["current_state"].get<std::string>() + "_" + read_symbols_key;
    if (transition_set.find(key) != transition_set.end()) {
      std::cerr << "Error: Deterministic Turing Machine cannot have multiple transitions from the same state reading the same symbols" << std::endl;
      return false;
    }
    transition_set.insert(key);
  }
  return true;
}

bool MultitapeTMLoader::checkTransitionFields(const json& transition) {
  if (!transition.is_object() ||
      transition.find("current_state") == transition.end() ||
      transition.find("read_symbols") == transition.end() ||
      transition.find("next_state") == transition.end() ||
      transition.find("write_symbols") == transition.end() ||
      transition.find("move_directions") == transition.end()) {
    std::cerr << "Error: Each transition must be an object with fields 'current_state', 'read_symbols', 'next_state', 'write_symbols', and 'move_directions'" << std::endl;
    return false;
  }

  if (!transition["move_directions"].is_array()) {
    std::cerr << "Error: 'move_directions' in transition must be an array" << std::endl;
    return false;
  }

  for (const auto& direction : transition["move_directions"]) {
    if (!direction.is_string() || (direction.get<std::string>() != "L" && direction.get<std::string>() != "R" && direction.get<std::string>() != "S")) {
      std::cerr << "Error: Each 'move_direction' in transition must be 'L', 'R', or 'S'" << std::endl;
      return false;
    }
  }
  return true;
}

bool MultitapeTMLoader::checkTransitionSymbols(const json& transition, const std::unordered_set<std::string>& input_alphabet_set, const std::unordered_set<std::string>& tape_alphabet_set) {
  if (!transition["read_symbols"].is_array() || !transition["write_symbols"].is_array()) {
    std::cerr << "Error: 'read_symbols' and 'write_symbols' in transition must be arrays" << std::endl;
    return false;
  }

  for (const auto& symbol : transition["read_symbols"]) {
    if (!symbol.is_string() || tape_alphabet_set.find(symbol.get<std::string>()) == tape_alphabet_set.end()) {
      std::cerr << "Error: Each 'read_symbol' in transition must be in 'tape_alphabet'" << std::endl;
      return false;
    }
  }

  for (const auto& symbol : transition["write_symbols"]) {
    if (!symbol.is_string() || tape_alphabet_set.find(symbol.get<std::string>()) == tape_alphabet_set.end()) {
      std::cerr << "Error: Each 'write_symbol' in transition must be in 'tape_alphabet'" << std::endl;
      return false;
    }
  }
  return true;
}

bool MultitapeTMLoader::checkTransitionStates(const json& transition, const std::unordered_set<std::string>& states_set) {
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