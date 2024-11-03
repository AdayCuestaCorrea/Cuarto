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

int main(int argc, char* argv[]) {
  try {
    Utility::help(argc, argv);
    std::shared_ptr<TuringMachineLoader> loader = Utility::createLoader(argv[1]);
    std::shared_ptr<TuringMachine> turing_machine = Utility::loadTuringMachine(loader, argv[1]);
    std::cout << *turing_machine << std::endl << std::endl;
    Utility::runTuringMachine(turing_machine, TuringMachineLoader::detectMachineType(argv[1]) == "Multitape");
  } catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}