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

/**
 * @brief Loads a multitape Turing machine from a specified file.
 *
 * This function reads a JSON file containing the definition of a multitape Turing machine,
 * including its states, input alphabet, tape alphabet, tapes, and transitions. It then
 * constructs and returns a shared pointer to a MultitapeTuringMachine object.
 *
 * @param file_path The path to the JSON file containing the Turing machine definition.
 * @return std::shared_ptr<TuringMachine> A shared pointer to the loaded MultitapeTuringMachine.
 * @throws std::runtime_error If the file is invalid or cannot be read.
 */
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

/**
 * @brief Validates the structure and content of a Turing machine configuration file.
 *
 * This function attempts to open the specified file and read its contents as JSON.
 * It then performs a series of checks to ensure that the JSON contains all the
 * required fields and that these fields are valid according to the Turing machine
 * specification.
 *
 * @param file_path The path to the Turing machine configuration file.
 * @return true if the file is valid and contains all required fields; false otherwise.
 */
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
         checkNumberOfTapes(j) &&
         checkFinalStates(j) &&
         checkTransitions(j);
}

/**
 * @brief Loads the tapes for a multi-tape Turing machine from a JSON object.
 *
 * This function reads the tape alphabet and the number of tapes from the provided
 * JSON object and initializes a vector of LRSTuringMachineTape objects accordingly.
 *
 * @param j The JSON object containing the Turing machine configuration. It should
 *          contain a "tape_alphabet" key for the tape alphabet and a "transitions"
 *          key with an array of transitions, where each transition includes a 
 *          "read_symbols" array indicating the number of tapes.
 * @return A vector of LRSTuringMachineTape objects initialized with the tape alphabet.
 */
std::vector<LRSTuringMachineTape> MultitapeTMLoader::loadTapes(const json& j) {
  Alphabet tape_alphabet = loadAlphabet(j, "tape_alphabet");
  std::vector<LRSTuringMachineTape> tapes;

  if (j.contains("transitions") && j["transitions"].is_array() && !j["transitions"].empty()) {
    size_t num_tapes = j["transitions"][0]["read_symbols"].size();
    for (size_t i = 0; i < num_tapes; ++i) {
      tapes.emplace_back(tape_alphabet);
    }
  }

  return tapes;
}

/**
 * @brief Loads transitions from a JSON object into the states of a Turing machine.
 *
 * This function parses a JSON object to extract transition information and 
 * associates these transitions with the corresponding states in the Turing machine.
 *
 * @param j The JSON object containing the transitions. The JSON structure is expected to have 
 *          an array of transitions, where each transition includes:
 *          - "current_state": The name of the current state.
 *          - "next_state": The name of the next state.
 *          - "read_symbols": An array of symbols to be read.
 *          - "write_symbols": An array of symbols to be written.
 *          - "move_directions": An array of directions to move the tape heads.
 * @param states A vector of shared pointers to State objects representing the states of the Turing machine.
 */
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

    std::shared_ptr<Transition> new_transition = std::make_shared<MultiTapeTransition>(
      next_state,
      read_symbols,
      write_symbols,
      move_directions
    );

    current_state->addTransition(new_transition);
  }
}

/**
 * @brief Checks if the provided JSON object contains all the required fields for a multitape Turing machine.
 *
 * This function verifies that the JSON object `j` includes all the necessary fields to define a multitape Turing machine.
 * The required fields are:
 * - "states"
 * - "input_alphabet"
 * - "tape_alphabet"
 * - "initial_state"
 * - "blank_symbol"
 * - "final_states"
 * - "number_of_tapes"
 * - "transitions"
 *
 * If any of these fields are missing, an error message is printed to the standard error stream, and the function returns false.
 *
 * @param j The JSON object to be checked.
 * @return true if all required fields are present, false otherwise.
 */
bool MultitapeTMLoader::checkRequiredFields(const json& j) {
  std::vector<std::string> required_fields = {
    "states", "input_alphabet", "tape_alphabet", "initial_state", "blank_symbol", "final_states", "number_of_tapes", "transitions"
  };
  for (const auto& field : required_fields) {
    if (j.find(field) == j.end()) {
      std::cerr << "Error: Missing required field " << field << std::endl;
      return false;
    }
  }
  return true;
}

/**
 * @brief Checks the validity of the number of tapes in a Turing machine configuration.
 *
 * This function verifies that the "number_of_tapes" field in the provided JSON object is a positive integer.
 * It also ensures that each transition in the "transitions" array has the correct number of read and write symbols
 * corresponding to the specified number of tapes.
 *
 * @param j The JSON object containing the Turing machine configuration.
 * @return true if the number of tapes is valid and consistent across transitions, false otherwise.
 */
bool MultitapeTMLoader::checkNumberOfTapes(const json& j) {
  if (!j["number_of_tapes"].is_number_integer() || j["number_of_tapes"].get<int>() <= 0) {
    std::cerr << "Error: 'number_of_tapes' must be a positive integer" << std::endl;
    return false;
  }

  int number_of_tapes = j["number_of_tapes"].get<int>();
  for (const auto& transition : j["transitions"]) {
    if (transition["read_symbols"].size() != number_of_tapes || transition["write_symbols"].size() != number_of_tapes) {
      std::cerr << "Error: The number of tapes you indicated is incorrect on the number_of_tapes field or on the transitions" << std::endl;
      return false;
    }
  }

  return true;
}

/**
 * @brief Validates the transitions of a multitape Turing machine.
 *
 * This function checks if the transitions provided in the JSON object are valid
 * for a deterministic multitape Turing machine. It ensures that:
 * - The "transitions" field is a non-empty array.
 * - Each transition has the required fields and valid symbols.
 * - Each transition refers to valid states.
 * - There are no multiple transitions from the same state reading the same symbols.
 *
 * @param j A JSON object containing the Turing machine description, including
 *          "transitions", "input_alphabet", "tape_alphabet", and "states".
 * @return true if all transitions are valid, false otherwise.
 */
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

/**
 * @brief Checks the validity of the fields in a transition object.
 *
 * This function verifies that the given transition object contains the required fields:
 * 'current_state', 'read_symbols', 'next_state', 'write_symbols', and 'move_directions'.
 * It also ensures that 'move_directions' is an array and that each element in the array
 * is a string with one of the values 'L', 'R', or 'S'.
 *
 * @param transition The JSON object representing the transition to be checked.
 * @return true if the transition object contains all required fields with valid values, false otherwise.
 */
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

/**
 * @brief Checks if the transition symbols are valid according to the input and tape alphabets.
 *
 * This function verifies that the 'read_symbols' and 'write_symbols' in the given transition are arrays
 * and that each symbol in these arrays is a string and belongs to the tape alphabet set.
 *
 * @param transition A JSON object representing the transition to be checked.
 * @param input_alphabet_set An unordered set of strings representing the input alphabet.
 * @param tape_alphabet_set An unordered set of strings representing the tape alphabet.
 * @return true if the transition symbols are valid, false otherwise.
 */
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