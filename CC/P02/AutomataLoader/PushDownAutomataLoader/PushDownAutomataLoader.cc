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


std::shared_ptr<Automata> PushDownAutomataLoader::load(std::string file_path) {
  if (!validFile(file_path)) {
    return nullptr;
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

void PushDownAutomataLoader::loadStates(States& states, std::shared_ptr<State>& initial_state) {
  for (int i = 0; i < lines[0].size(); i++) {
    std::shared_ptr<State> state = std::make_shared<State>(lines[0][i], lines[3][0] == lines[0][i]);
    if (lines[3][0] == lines[0][i]) initial_state = state;
    states.push_back(state);
  }
}

void PushDownAutomataLoader::loadAlphabet(Alphabet& alphabet) {
  for (int i = 0; i < lines[1].size(); i++) {
    alphabet.push_back(lines[1][i][0]);
  }
  alphabet.push_back('.');
}

void PushDownAutomataLoader::loadStackAlphabet(Alphabet& stack_alphabet) {
  for (int i = 0; i < lines[2].size(); i++) {
    stack_alphabet.push_back(lines[2][i][0]);
  }
  stack_alphabet.push_back('.');
}

void PushDownAutomataLoader::loadInitialStack(std::stack<Symbol>& stack) {
  for (int i = 0; i < lines[4].size(); i++) {
    stack.push(lines[4][i][0]);
  }
}

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

bool PushDownAutomataLoader::validFile(std::string file_path) {
  lines = readFile(file_path);
  std::vector<std::string> states = lines[0];
  std::vector<std::string> alphabet = lines[1];
  std::vector<std::string> stack_alphabet = lines[2];

  if (checkForDuplicates() || !checkFileLength() || 
      !validateAlphabet(alphabet, false) || !validateAlphabet(stack_alphabet, true) || 
      !validateInitial(states, lines[3]) || !validateInitial(stack_alphabet, lines[4]) || 
      !validateTransitions(states, alphabet, stack_alphabet)) {
    return false;
  }
  return true;
}

bool PushDownAutomataLoader::checkForDuplicates() {
  if (Utility::hasDuplicates(lines) && lines[0].size() > 1) {
    std::cerr << "Error: Duplicate lines found on the file." << std::endl;
    return true;
  }
  return false;
}

bool PushDownAutomataLoader::checkFileLength() {
  if (lines.size() < 6) {
    std::cerr << "Error: File must contain at least 6 lines." << std::endl;
    return false;
  }
  return true;
}

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

bool PushDownAutomataLoader::validateInitial(const std::vector<std::string>& states, const std::vector<std::string>& initialState) {
  if (!Utility::contains(states, initialState[0]) || initialState.size() > 1) {
    std::cerr << "Error: Initial state must be unique and exist." << std::endl;
    return false;
  }
  return true;
}

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