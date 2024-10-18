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

#pragma once
#include "../Automata/Automata.h"
#include "../Utility/Utility.h"
#include <string>
#include <vector>
#include <fstream>

class AutomataLoader {
 public:
  virtual std::shared_ptr<Automata> load(std::string file_path) = 0;
 protected:
  virtual bool validFile(std::string file_path) = 0;
  std::vector<std::vector<std::string>> lines;
};