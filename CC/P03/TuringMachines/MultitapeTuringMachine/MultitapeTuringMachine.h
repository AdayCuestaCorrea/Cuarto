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

#pragma once

#include "../TuringMachine.h"
#include "../Elements/Tape/LRSTuringMachineTape/LRSTuringMachineTape.h"
#include "../Elements/Transition/Types/MultitapeTransition.h"

/**
 * @class MultitapeTuringMachine
 * @brief A class representing a multi-tape Turing machine.
 * 
 * This class extends the TuringMachine class and provides functionality for
 * a Turing machine with multiple tapes.
 */
class MultitapeTuringMachine : public TuringMachine {
 public:
  MultitapeTuringMachine(const States& states, std::shared_ptr<State> initial_state, const Alphabet& alphabet, std::vector<LRSTuringMachineTape> tape)
                       : TuringMachine(states, initial_state, alphabet), tape_(tape) {}

  std::string execute(InputType input) override;
  bool processTransition(std::shared_ptr<State> &current_state, Alphabet &read_symbols);
  void print(std::ostream& os) const override;
  void printTape() const override;
 private:
  std::vector<LRSTuringMachineTape> tape_;
  std::string getTapeContents() const;
  void initializeTapes(const std::vector<std::string>& words);
  std::vector<char> readFromTapes();
  void applyTransition(const std::shared_ptr<Transition> transition);
  std::string generateResult(const std::shared_ptr<State>& current_state);
};