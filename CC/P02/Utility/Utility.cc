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

#include "Utility.h"

namespace Utility {
  
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

  bool hasComment(const std::string& line) {
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == '#') {
        return true;
      }
    }
    return false;
  }

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

  void leftTrim(std::string& string) {
    string.erase(0, string.find_first_not_of("\t\n\v\f\r "));
  }
  
  void rightTrim(std::string& string) {
    string.erase(string.find_last_not_of("\t\n\v\f\r ") + 1);
  }
}