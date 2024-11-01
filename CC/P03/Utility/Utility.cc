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
      std::cout << "This program reads a file containing a pushdown automata, if the file is not correct the program will stop." << std::endl;
      std::cout << "If the file is correct, you will be able to input words to check if they are accepted by the automata." << std::endl;
      exit(0);
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
}