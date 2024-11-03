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


/**
 * @brief Detects the type of Turing machine described in a JSON file.
 *
 * This function reads a JSON file from the specified file path and determines
 * whether the Turing machine described in the file is a single-tape or a 
 * multi-tape Turing machine. It checks the "transitions" section of the JSON 
 * file to see if any transition contains multiple "read_symbols" or 
 * "write_symbols", which would indicate a multi-tape Turing machine.
 *
 * @param file_path The path to the JSON file describing the Turing machine.
 * @return A string indicating the type of Turing machine: "SingleTape" or "Multitape".
 * @throws std::runtime_error If the file cannot be opened.
 */
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

/**
 * @brief Loads the states of a Turing machine from a JSON object.
 *
 * This function parses a JSON object to create a vector of shared pointers to State objects.
 * It initializes each state with its name and sets the initial and final states based on the JSON data.
 *
 * @param j The JSON object containing the states information. The JSON object should have the following structure:
 * {
 *   "states": ["state1", "state2", ...],
 *   "initial_state": "state1",
 *   "final_states": ["state2", ...]
 * }
 * 
 * @return A vector of shared pointers to State objects representing the states of the Turing machine.
 */
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

/**
 * @brief Loads an Alphabet from a JSON object.
 *
 * This function extracts an Alphabet from the given JSON object using the specified key.
 * It iterates over the JSON array associated with the key and converts each element to a 
 * character, which is then added to the Alphabet.
 *
 * @param j The JSON object containing the alphabet data.
 * @param key The key in the JSON object that maps to the alphabet array.
 * @return An Alphabet object containing the characters from the JSON array.
 */
Alphabet TuringMachineLoader::loadAlphabet(const json& j, const std::string& key) {
  Alphabet alphabet;
  for (const auto& symbol : j[key]) {
    alphabet.push_back(symbol.get<std::string>()[0]);
  }
  return alphabet;
}

/**
 * @brief Checks if the 'states' field in the given JSON object is a non-empty array.
 *
 * This function verifies that the 'states' field in the provided JSON object is
 * present, is an array, and is not empty. If any of these conditions are not met,
 * an error message is printed to the standard error stream and the function returns false.
 *
 * @param j The JSON object to check.
 * @return true if the 'states' field is a non-empty array, false otherwise.
 */
bool TuringMachineLoader::checkStates(const json& j) {
  if (!j["states"].is_array() || j["states"].empty()) {
    std::cerr << "Error: 'states' must be a non-empty array" << std::endl;
    return false;
  }
  return true;
}

/**
 * @brief Checks the validity of the input and tape alphabets in the given JSON object.
 *
 * This function verifies that the 'input_alphabet' and 'tape_alphabet' fields in the JSON object
 * are non-empty arrays of single-character strings. Additionally, it ensures that all symbols
 * in the 'input_alphabet' are contained within the 'tape_alphabet'.
 *
 * @param j The JSON object containing the alphabets to be checked.
 * @return true if the alphabets are valid, false otherwise.
 */
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

/**
 * @brief Checks if the initial state in the given JSON object is valid.
 *
 * This function verifies that the "initial_state" field in the JSON object is a non-empty string
 * and that it is contained within the "states" set defined in the same JSON object.
 *
 * @param j The JSON object containing the Turing machine configuration.
 * @return true if the initial state is valid, false otherwise.
 */
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

/**
 * @brief Checks if the 'blank_symbol' in the given JSON object is valid.
 *
 * This function verifies that the 'blank_symbol' in the provided JSON object
 * meets the following criteria:
 * - It is a string.
 * - It is not empty.
 * - It is equal to the dot character ".".
 *
 * If any of these conditions are not met, an error message is printed to the
 * standard error stream and the function returns false.
 *
 * @param j The JSON object containing the 'blank_symbol' to be checked.
 * @return true if the 'blank_symbol' is valid, false otherwise.
 */
bool TuringMachineLoader::checkBlankSymbol(const json& j) {
  if (!j["blank_symbol"].is_string() || j["blank_symbol"].empty() || j["blank_symbol"] != ".") {
    std::cerr << "Error: 'blank_symbol' must be a non-empty string with a dot -> \".\"" << std::endl;
    return false;
  }
  return true;
}

/**
 * @brief Checks the validity of the final states in a Turing machine configuration.
 *
 * This function verifies that the "final_states" field in the provided JSON object is a non-empty array
 * and that each final state is contained within the "states" field of the JSON object.
 *
 * @param j A JSON object containing the Turing machine configuration. It must have the fields "final_states" and "states".
 * @return true if the "final_states" field is a non-empty array and all its elements are contained in the "states" field; false otherwise.
 */
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

/**
 * @brief Checks if the transition states are valid.
 *
 * This function verifies that both the 'current_state' and 'next_state' in the given transition
 * are present in the provided set of states.
 *
 * @param transition A JSON object representing the transition. It should contain the keys 
 *                   "current_state" and "next_state" with their respective state names as values.
 * @param states_set An unordered set of strings containing all valid states.
 * @return true if both 'current_state' and 'next_state' are found in the states_set, false otherwise.
 */
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