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

#include "Utility/Utility.h"
#include "AutomataLoader/PushDownAutomataLoader/PushDownAutomataLoader.h"

int main(int argc, char* argv[]) {
  Utility::help(argc, argv);
  std::shared_ptr<AutomataLoader> loader = std::make_shared<PushDownAutomataLoader>();
  std::shared_ptr<Automata> automata = loader->load(argv[1]);
  int number_of_words = 0;
  std::cout << "Enter the number of words you want to check: ";
  std::cin >> number_of_words;
  while (number_of_words > 0) {
    std::string word;
    std::cout << "Enter a word to check if it is accepted by the automata: ";
    std::cin >> word;
    std::cout << "The word is " << (automata->execute(word) ? "accepted" : "rejected") << std::endl;
    number_of_words--;
  }
  //std::cout << *automata << std::endl;
  return 0;
}