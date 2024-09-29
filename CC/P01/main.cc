/** Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Complejidad Computacional
  * Curso: 4º
  * Práctica 1: Potencia
  * Autor: Aday Cuesta Correa
  * Correo: alu0101483887@ull.edu.es
  * Fecha: 26/09/2024
  */

#include <iostream>
#include "PRF/Power/Power.h"
#include "PRF/Sum/Sum.h"
#include "PRF/Multiplication/Multiplication.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <numberX> <numberY>" << std::endl;
    return 1;
  } 
  int numberX = std::stoi(argv[1]);
  int numberY = std::stoi(argv[2]);
  if (numberX < 0) {
    std::cerr << "Error: numberX must be a non-negative integer." << std::endl;
    return 1;
  }
  if (numberY < 0) {
    std::cerr << "Error: numberY must be a non-negative integer." << std::endl;
    return 1;
  }
  PrimitiveRecursiveFunctions* pow = new Power(numberX, numberY);
  std::cout << "Result: " << pow->getResult() << std::endl;
  std::cout << "Function call count: " << pow->getFunctionCallCount() << std::endl;
  return 0;
}