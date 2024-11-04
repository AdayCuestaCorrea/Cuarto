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

#include "Utility.h"

namespace Utility {
  
  /**
   * @brief Displays help information for the program.
   *
   * This function checks the number of command-line arguments and displays
   * an error message if the number of arguments is incorrect. If the argument
   * is "-h" or "--help", it displays usage information and a brief description
   * of the program's functionality.
   *
   * @param argc The number of command-line arguments.
   * @param argv The array of command-line arguments.
   */
  void help(int argc, char* argv[]) {
    if (argc != 2) {
      std::cerr << "Error: Wrong number of arguments." << std::endl;
      std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
      exit(1);
    }
    std::string fileName = argv[1];
    if (fileName == "-h" || fileName == "--help") {
      std::cout << "Usage: " << argv[0] << " <file_path>" << std::endl;
      std::cout << "This program reads a file containing a Turing Machine, if the file is not correct the program will stop." << std::endl;
      std::cout << "If the file is correct, you will be able to input words to check if they are accepted by the Turing Machine." << std::endl;
      std::cout << "The file must be a JSON file with the following fields:" << std::endl;
      std::cout << "  - states: an array of strings representing the states of the Turing Machine" << std::endl;
      std::cout << "  - input_alphabet: an array of single-character strings representing the input alphabet" << std::endl;
      std::cout << "  - tape_alphabet: an array of single-character strings representing the tape alphabet" << std::endl;
      std::cout << "  - initial_state: a string representing the initial state of the Turing Machine" << std::endl;
      std::cout << "  - blank_symbol: a single-character string representing the blank symbol of the Turing Machine" << std::endl;
      std::cout << "  - number_of_tapes: an optional field with an integer representing the number of tapes of the MULTITAPE TURING MACHINE" << std::endl;
      std::cout << "  - final_states: an array of strings representing the final states of the Turing Machine" << std::endl;
      std::cout << "  - transitions: an array of objects representing the transitions of the Turing Machine" << std::endl;
      std::cout << "The transitions must have the following fields:" << std::endl;
      std::cout << "  - current_state: a string representing the current state of the transition" << std::endl;
      std::cout << "  - read_symbol: a string or array (Multitapes only) representing the symbol read by the transition" << std::endl;
      std::cout << "  - next_state: a string representing the next state of the transition" << std::endl;
      std::cout << "  - write_symbol: a string or array (Multitapes only) representing the symbol written by the transition" << std::endl;
      std::cout << "  - move_direction: a character or array (Multitapes only) representing the direction in which the tape head moves" << std::endl;
      exit(0);
    }

    // Check if the file extension is .json
    if (fileName.size() < 5 || fileName.substr(fileName.size() - 5) != ".json") {
      std::cerr << "Error: The file must have a .json extension." << std::endl;
      std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
      exit(1);
    }
  }

  /**
   * @brief Checks if a given line contains a comment.
   *
   * This function iterates through each character in the provided line and 
   * checks if there is a '#' character, which indicates the presence of a comment.
   *
   * @param line The line of text to be checked for a comment.
   * @return true if the line contains a comment, false otherwise.
   */
  bool hasComment(const std::string& line) {
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == '#') {
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Removes comments from a given line of text.
   *
   * This function takes a string as input and returns a new string with all characters
   * after the first '#' character removed. If there is no '#' character in the input string,
   * the entire string is returned unchanged.
   *
   * @param line The input string from which comments are to be removed.
   * @return A new string with comments removed.
   */
  std::string removeComments(const std::string& line) {
    std::string result = "";
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == '#') {
        break;
      }
      result += line[i];
    }
    return result;
  }

  /**
   * @brief Removes leading whitespace characters from a string.
   *
   * This function modifies the input string by erasing all leading whitespace
   * characters, including spaces, tabs, newlines, vertical tabs, form feeds, 
   * and carriage returns.
   *
   * @param string The string to be trimmed of leading whitespace.
   */
  void leftTrim(std::string& string) {
    string.erase(0, string.find_first_not_of("\t\n\v\f\r "));
  }
  
  /**
   * @brief Trims whitespace characters from the end of a string.
   *
   * This function removes all trailing whitespace characters from the given string.
   * Whitespace characters include spaces, tabs, newlines, vertical tabs, form feeds, and carriage returns.
   *
   * @param string The string to be trimmed. The string is modified in place.
   */
  void rightTrim(std::string& string) {
    string.erase(string.find_last_not_of("\t\n\v\f\r ") + 1);
  }

  /**
   * @brief Creates a TuringMachineLoader based on the type of Turing machine specified in the file.
   *
   * This function detects the type of Turing machine described in the given file path.
   * If the machine type is "Multitape", it creates and returns a shared pointer to a MultitapeTMLoader.
   * Otherwise, it creates and returns a shared pointer to an LRSTuringMachineLoader.
   *
   * @param file_path The path to the file that contains the Turing machine description.
   * @return std::shared_ptr<TuringMachineLoader> A shared pointer to the appropriate TuringMachineLoader.
   */
  std::shared_ptr<TuringMachineLoader> createLoader(const std::string& file_path) {
    bool is_multitape = TuringMachineLoader::detectMachineType(file_path) == "Multitape";
    if (is_multitape) {
      return std::make_shared<MultitapeTMLoader>();
    } else {
      return std::make_shared<LRSTuringMachineLoader>();
    }
  }

  /**
   * @brief Loads a Turing machine from a specified file.
   *
   * This function uses the provided TuringMachineLoader to load a Turing machine
   * from the given file path and returns a shared pointer to the loaded Turing machine.
   *
   * @param loader A shared pointer to a TuringMachineLoader instance used to load the Turing machine.
   * @param file_path The path to the file containing the Turing machine definition.
   * @return A shared pointer to the loaded Turing machine.
   */
  std::shared_ptr<TuringMachine> loadTuringMachine(const std::shared_ptr<TuringMachineLoader>& loader, const std::string& file_path) {
    return loader->load(file_path);
  }

  /**
   * @brief Runs the Turing Machine with user input.
   *
   * This function continuously prompts the user to enter input words for the Turing Machine
   * until the user types 'exit'. It supports both single-tape and multi-tape Turing Machines.
   *
   * @param turing_machine A shared pointer to the Turing Machine object.
   * @param is_multitape A boolean flag indicating whether the Turing Machine is multi-tape.
   */
  void runTuringMachine(const std::shared_ptr<TuringMachine>& turing_machine, bool is_multitape) {
    while (true) {
      std::cout << "To exit, enter 'exit'" << std::endl;
      std::string result;
      std::string word;
      if (is_multitape) {
        std::vector<std::string> input_words;
        std::cout << "Enter input words for each tape, separated by spaces: ";
        std::getline(std::cin, word);
        if (word == "exit") break;
        std::istringstream iss(word);
        std::string word;
        while (iss >> word) {
          input_words.push_back(word);
        }
        result = turing_machine->execute(input_words);
      } else {
        std::cout << "Enter input word: ";
        std::getline(std::cin, word);
        if (word == "exit") break;
        if (word.size() == 0) word = ".";
        result = turing_machine->execute(word);
      }
      std::cout << result << std::endl;
      turing_machine->printTape();
      std::cout << std::endl;
    }
  }
}