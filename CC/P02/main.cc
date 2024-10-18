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
  std::cout << *automata << std::endl;
  return 0;
}