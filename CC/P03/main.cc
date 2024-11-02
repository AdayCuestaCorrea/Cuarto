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

#include "Utility/Utility.h"
#include "TuringMachineLoader/LRSTuringMachineLoader/LRSTuringMachineLoader.h"
#include "TuringMachineLoader/MultitapeTMLoader/MultitapeTMLoader.h"
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
  try {
    Utility::help(argc, argv);
    std::shared_ptr<TuringMachineLoader> loader;
    bool is_multitape = TuringMachineLoader::detectMachineType(argv[1]) == "Multitape";

    if (is_multitape) loader = std::make_shared<MultitapeTMLoader>();
    else loader = std::make_shared<LRSTuringMachineLoader>();

    std::shared_ptr<TuringMachine> turing_machine = loader->load(argv[1]);
    std::cout << *turing_machine << std::endl;

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
      std::cout << result << std::endl << std::endl;
    }
  } catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}