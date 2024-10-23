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

#include "PushDownAutomataLoader.h"

/**
 * @brief Loads a PushDownAutomata from a specified file path.
 *
 * This function reads the automata configuration from the given file path,
 * validates the file, and initializes the states, alphabets, stack, and transitions
 * of the PushDownAutomata.
 *
 * @param file_path The path to the file containing the automata configuration.
 * @return A shared pointer to the loaded PushDownAutomata.
 * @throws std::runtime_error If the file is invalid or cannot be read.
 */
std::shared_ptr<Automata> PushDownAutomataLoader::load(std::string file_path) {
  if (!validFile(file_path)) {
    throw std::runtime_error("Invalid file: " + file_path);
  }

  States states;
  std::shared_ptr<State> initial_state;
  Alphabet alphabet;
  Alphabet stack_alphabet;
  std::stack<Symbol> stack;

  loadStates(states, initial_state);
  loadAlphabet(alphabet);
  loadStackAlphabet(stack_alphabet);
  loadInitialStack(stack);
  loadTransitions(states);

  return std::make_shared<PushDownAutomata>(states, initial_state, alphabet, stack_alphabet, stack);
}

/**
 * @brief Loads the states of the pushdown automaton from the provided lines.
 *
 * This function iterates through the first line of the input, creating a 
 * shared pointer to a State object for each element. It also checks if the 
 * current state is the initial state and updates the initial_state pointer 
 * accordingly. Each created state is then added to the states container.
 *
 * @param states A reference to a container that will hold the states of the automaton.
 * @param initial_state A shared pointer to the initial state of the automaton.
 */
void PushDownAutomataLoader::loadStates(States& states, std::shared_ptr<State>& initial_state) {
  for (int i = 0; i < lines[0].size(); i++) {
    std::shared_ptr<State> state = std::make_shared<State>(lines[0][i], lines[3][0] == lines[0][i]);
    if (lines[3][0] == lines[0][i]) initial_state = state;
    states.push_back(state);
  }
}

/**
 * @brief Loads the alphabet from the second line of the input data.
 *
 * This function iterates through the characters in the second line of the 
 * input data (stored in `lines[1]`) and adds each character to the provided 
 * `alphabet` object.
 *
 * @param alphabet A reference to an Alphabet object where the characters 
 *                 from the input data will be stored.
 */
void PushDownAutomataLoader::loadAlphabet(Alphabet& alphabet) {
  for (int i = 0; i < lines[1].size(); i++) {
    alphabet.push_back(lines[1][i][0]);
  }
}

/**
 * @brief Loads the stack alphabet from the third line of the input.
 *
 * This function iterates over the characters in the third line of the input
 * and adds each character to the provided stack alphabet.
 *
 * @param stack_alphabet A reference to an Alphabet object where the stack
 *                       alphabet will be stored.
 */
void PushDownAutomataLoader::loadStackAlphabet(Alphabet& stack_alphabet) {
  for (int i = 0; i < lines[2].size(); i++) {
    stack_alphabet.push_back(lines[2][i][0]);
  }
}

/**
 * @brief Loads the initial stack with symbols from the specified line.
 *
 * This function takes a reference to a stack of symbols and loads it with 
 * symbols from the fifth line (index 4) of the `lines` member variable. 
 * Each character in the specified line is pushed onto the stack.
 *
 * @param stack A reference to the stack of symbols to be initialized.
 */
void PushDownAutomataLoader::loadInitialStack(std::stack<Symbol>& stack) {
  for (int i = 0; i < lines[4].size(); i++) {
    stack.push(lines[4][i][0]);
  }
}

/**
 * @brief Loads transitions for the pushdown automaton from the provided lines.
 *
 * This function iterates over the lines starting from the 6th line (index 5) and
 * extracts the origin and destination states, as well as the transition details.
 * It then creates a Transition object and adds it to the origin state.
 *
 * @param states A reference to a collection of states in the pushdown automaton.
 */
void PushDownAutomataLoader::loadTransitions(States& states) {
  for (int i = 5; i < lines.size(); i++) {
    std::shared_ptr<State> origin_state;
    std::shared_ptr<State> destination_state;
    for (const auto& state : states) {
      if (state->get_name() == lines[i][0]) origin_state = state;
      if (state->get_name() == lines[i][3]) destination_state = state;
    }
    Transition transition(destination_state, lines[i][1][0], lines[i][2][0], lines[i][4]);
    origin_state->add_transition(transition);
  }
}

/**
 * @brief Reads a file and processes its content into a vector of string vectors.
 *
 * This function opens a file specified by the given file path, reads its content line by line,
 * and processes each line by trimming whitespace, removing comments, and splitting the line
 * into individual elements based on spaces. The processed lines are stored in a vector of
 * string vectors, which is then returned.
 *
 * @param file_path The path to the file to be read.
 * @return A vector of string vectors, where each inner vector represents a processed line from the file.
 */
std::vector<std::vector<std::string>> PushDownAutomataLoader::readFile(std::string file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    return lines;
  }
  std::string line;
  while (std::getline(file, line)) {
    Utility::leftTrim(line);
    if (line.empty() || line[0] == '#') continue;
    if (Utility::hasComment(line)) line = Utility::removeComments(line);
    Utility::rightTrim(line);
    std::vector<std::string> currentLine;
    std::string element;
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == ' ' || i == line.size() - 1) {
        if (i == line.size() - 1 && line[i] != ' ') element += line[i];
        currentLine.push_back(element);
        element = "";
      } else element += line[i];
    }
    lines.push_back(currentLine);
  }
  return lines;
}

/**
 * @brief Validates the structure and content of a pushdown automata file.
 *
 * This function reads the file specified by the given file path and performs 
 * a series of checks to ensure the file is a valid representation of a pushdown automata.
 * The checks include verifying the absence of duplicates, correct file length, 
 * valid states, alphabets, initial state, initial stack, and transitions.
 *
 * @param file_path The path to the file to be validated.
 * @return true if the file is valid, false otherwise.
 */
bool PushDownAutomataLoader::validFile(std::string file_path) {
  lines = readFile(file_path);
  std::vector<std::string> states = lines[0];
  std::vector<std::string> alphabet = lines[1];
  std::vector<std::string> stack_alphabet = lines[2];

  if (checkForDuplicates() || !checkFileLength() || !checkStates(states) ||
      !validateAlphabet(alphabet, false) || !validateAlphabet(stack_alphabet, true) || 
      !validateInitialState(states, lines[3]) || !validateInitialStack(stack_alphabet, lines[4]) || 
      !validateTransitions(states, alphabet, stack_alphabet)) {
    return false;
  }
  return true;
}

/**
 * @brief Checks if the given states are valid for the PushDown Automata.
 *
 * This function verifies that the provided list of states does not contain
 * the empty symbol ("."). If the empty symbol is found, an error message
 * is printed to the standard error stream, and the function returns false.
 *
 * @param states A vector of strings representing the states to be checked.
 * @return true if the states are valid (do not contain the empty symbol), false otherwise.
 */
bool PushDownAutomataLoader::checkStates(const std::vector<std::string>& states) {
  if (Utility::contains(states, std::string("."))) {
    std::cerr << "Error: States must not contain the empty symbol." << std::endl;
    return false;
  }
  return true;
}

/**
 * @brief Checks for duplicate lines in the automata file.
 *
 * This function checks if there are any duplicate lines in the file being
 * processed by the PushDownAutomataLoader. If duplicates are found and the
 * first line has more than one character, an error message is printed to
 * standard error.
 *
 * @return true if duplicate lines are found and the first line has more than
 *         one character, false otherwise.
 */
bool PushDownAutomataLoader::checkForDuplicates() {
  if (Utility::hasDuplicates(lines) && lines[0].size() > 1) {
    std::cerr << "Error: Duplicate lines found on the file." << std::endl;
    return true;
  }
  return false;
}

/**
 * @brief Checks if the file contains the minimum required number of lines.
 *
 * This function verifies that the file loaded into the PushDownAutomataLoader
 * contains at least 6 lines. If the file has fewer than 6 lines, an error
 * message is printed to the standard error stream, and the function returns false.
 *
 * @return true if the file contains at least 6 lines, false otherwise.
 */
bool PushDownAutomataLoader::checkFileLength() {
  if (lines.size() < 6) {
    std::cerr << "Error: File must contain at least 6 lines." << std::endl;
    return false;
  }
  return true;
}

/**
 * @brief Validates the given alphabet for the pushdown automaton.
 *
 * This function checks if each symbol in the provided alphabet is valid.
 * A valid symbol must be a single character and must not be the empty symbol (".").
 *
 * @param alphabet A vector of strings representing the alphabet to be validated.
 * @param isStackAlphabet A boolean indicating if the alphabet is for the stack.
 * @return true if the alphabet is valid, false otherwise.
 */
bool PushDownAutomataLoader::validateAlphabet(const std::vector<std::string>& alphabet, bool isStackAlphabet) {
  for (const std::string &symbol : alphabet) {
    if (symbol.size() > 1) {
      std::cerr << "Error: Alphabet symbols must be of length 1." << std::endl;
      return false;
    }
    if (symbol == ".") {
      std::cerr << "Error: alphabet must not contain the empty symbol." << std::endl;
      return false;
    }
  }
  return true;
}

/**
 * @brief Validates the initial state of the pushdown automaton.
 *
 * This function checks if the initial state is unique and exists within the provided states.
 * It ensures that the initial state is a single state and is present in the list of states.
 *
 * @param states A vector of strings representing the states of the automaton.
 * @param initialState A vector of strings representing the initial state of the automaton.
 *                      It should contain exactly one state.
 * @return true if the initial state is valid (exists in the states and is unique), false otherwise.
 */
bool PushDownAutomataLoader::validateInitialState(const std::vector<std::string>& states, const std::vector<std::string>& initialState) {
  if (!Utility::contains(states, initialState[0]) || initialState.size() > 1) {
    std::cerr << "Error: Initial state must be unique and exist." << std::endl;
    return false;
  }
  return true;
}

/**
 * @brief Validates the initial stack symbol for the PushDownAutomata.
 *
 * This function checks if the initial stack symbol is unique and exists within the provided states.
 * It ensures that the initial stack symbol is present in the list of states and that the initial state
 * vector contains only one element.
 *
 * @param states A vector of strings representing the states of the automaton.
 * @param initialState A vector of strings representing the initial state of the stack.
 * @return true if the initial stack symbol is valid, false otherwise.
 */
bool PushDownAutomataLoader::validateInitialStack(const std::vector<std::string>& states, const std::vector<std::string>& initialState) {
  if (!Utility::contains(states, initialState[0]) || initialState.size() > 1) {
    std::cerr << "Error: Initial stack symbol must be unique and exist." << std::endl;
    return false;
  }
  return true;
}

/**
 * @brief Validates the transitions of a pushdown automaton.
 *
 * This function checks if the transitions defined in the automaton are valid
 * based on the provided states, input alphabet, and stack alphabet. Each transition
 * must have exactly 5 elements and adhere to the following rules:
 * - The first element must be a valid state.
 * - The second element must be a valid symbol from the input alphabet or a dot ('.') representing an epsilon transition.
 * - The third element must be a valid symbol from the stack alphabet.
 * - The fourth element must be a valid state.
 * - The fifth element must be a sequence of valid symbols from the stack alphabet or a dot ('.') representing an empty stack operation.
 *
 * @param states A vector of strings representing the valid states of the automaton.
 * @param alphabet A vector of strings representing the valid input alphabet of the automaton.
 * @param stack_alphabet A vector of strings representing the valid stack alphabet of the automaton.
 * @return true if all transitions are valid, false otherwise.
 */
bool PushDownAutomataLoader::validateTransitions(const std::vector<std::string>& states, const std::vector<std::string>& alphabet, const std::vector<std::string>& stack_alphabet) {
  int transitions_index = 5;
  for (int i = transitions_index; i < lines.size(); i++) {
    if (lines[i].size() != 5) {
      std::cerr << "Error: Transition must have 5 elements." << std::endl;
      return false;
    }
    if (!Utility::contains(states, lines[i][0])) {
      std::cerr << "Error: State must exist." << std::endl;
      return false;
    }
    if (!Utility::contains(alphabet, lines[i][1]) && lines[i][1] != ".") {
      std::cerr << "Error: Transition read symbol must exist." << std::endl;
      return false;
    }
    if (!Utility::contains(stack_alphabet, lines[i][2])) {
      std::cerr << "Error: Transition remove from stack symbol must exist." << std::endl;
      return false;
    }
    if (!Utility::contains(states, lines[i][3])) {
      std::cerr << "Error: Transition state must exist." << std::endl;
      return false;
    }
    for (char symbol : lines[i][4]) {
      if (!Utility::contains(stack_alphabet, std::string(1, symbol)) && symbol != '.') {
        std::cerr << "Error: Transition insert into stack symbol must exist." << std::endl;
        return false;
      }
    }
  }
  return true;
}