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

/**
 * @brief Loads a Turing Machine from a specified file path.
 *
 * This function reads a JSON file containing the definition of a Turing Machine,
 * validates the file, and constructs the Turing Machine object.
 *
 * @param file_path The path to the JSON file containing the Turing Machine definition.
 * @return A shared pointer to the loaded Turing Machine.
 * @throws std::runtime_error If the file is invalid or cannot be read.
 */
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

/**
 * @brief Loads a Turing machine tape from a JSON object.
 *
 * This function extracts the tape alphabet from the provided JSON object
 * and uses it to construct and return an LRSTuringMachineTape object.
 *
 * @param j The JSON object containing the tape alphabet.
 * @return An LRSTuringMachineTape object initialized with the tape alphabet.
 */
LRSTuringMachineTape LRSTuringMachineLoader::loadTape(const json& j) {
  Alphabet tape_alphabet = loadAlphabet(j, "tape_alphabet");
  return LRSTuringMachineTape(tape_alphabet);
}

/**
 * @brief Loads transitions from a JSON object into the provided states.
 *
 * This function parses a JSON object to extract transition information and 
 * associates these transitions with the corresponding states in the provided 
 * vector of states.
 *
 * @param j The JSON object containing the transitions. The JSON object should 
 *          have a "transitions" key, which is an array of transition objects. 
 *          Each transition object should have the following keys:
 *          - "current_state": The name of the current state (string).
 *          - "next_state": The name of the next state (string).
 *          - "read_symbol": The symbol to read (string, single character).
 *          - "write_symbol": The symbol to write (string, single character).
 *          - "move_direction": The direction to move (string, single character).
 * @param states A vector of shared pointers to State objects. These states 
 *               represent the states of the Turing machine and should have 
 *               unique names.
 */
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

/**
 * @brief Validates the Turing machine configuration file.
 *
 * This function attempts to open the specified file and parse its contents as JSON.
 * It then checks for the presence and validity of required fields, states, alphabets,
 * initial state, blank symbol, final states, and transitions.
 *
 * @param file_path The path to the Turing machine configuration file.
 * @return true if the file is valid and contains all required fields; false otherwise.
 */
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

/**
 * @brief Checks if the provided JSON object contains all required fields for a Turing machine.
 *
 * This function verifies that the JSON object `j` contains the necessary fields to define a Turing machine.
 * The required fields are:
 * - "states"
 * - "input_alphabet"
 * - "tape_alphabet"
 * - "initial_state"
 * - "blank_symbol"
 * - "final_states"
 * - "transitions"
 *
 * If any of these fields are missing, an error message is printed to the standard error stream, and the function returns false.
 *
 * @param j The JSON object to check.
 * @return true if all required fields are present, false otherwise.
 */
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

/**
 * @brief Validates the transitions of a Turing machine described in a JSON object.
 *
 * This function checks if the "transitions" field in the provided JSON object is a non-empty array.
 * It also validates each transition to ensure it adheres to the constraints of a deterministic Turing machine.
 * Specifically, it checks that:
 * - Each transition has the required fields.
 * - The symbols in the transitions are part of the input and tape alphabets.
 * - The states in the transitions are part of the defined states.
 * - There are no multiple transitions from the same state reading the same symbol.
 *
 * @param j A JSON object containing the Turing machine description, including "transitions", "input_alphabet", "tape_alphabet", and "states".
 * @return true if all transitions are valid and the Turing machine is deterministic, false otherwise.
 */
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

/**
 * @brief Checks the validity of the fields in a Turing machine transition.
 *
 * This function verifies that the given JSON object representing a transition
 * contains all the required fields: 'current_state', 'read_symbol', 'next_state',
 * 'write_symbol', and 'move_direction'. Additionally, it ensures that the 
 * 'move_direction' field has a valid value ('L', 'R', or 'S').
 *
 * @param transition A JSON object representing a Turing machine transition.
 * @return true if the transition contains all required fields with valid values, false otherwise.
 */
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

/**
 * @brief Checks if the transition symbols are valid according to the tape alphabet.
 *
 * This function verifies that the 'read_symbol' and 'write_symbol' in the given transition
 * are present in the provided tape alphabet set. If either symbol is not found in the tape
 * alphabet set, an error message is printed to the standard error stream and the function
 * returns false.
 *
 * @param transition A JSON object representing the transition, which must contain the keys
 *                   "read_symbol" and "write_symbol".
 * @param input_alphabet_set An unordered set of strings representing the input alphabet.
 *                           (Note: This parameter is not used in the current implementation.)
 * @param tape_alphabet_set An unordered set of strings representing the tape alphabet.
 *
 * @return true if both 'read_symbol' and 'write_symbol' are found in the tape alphabet set,
 *         false otherwise.
 */
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