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

#include "../Transition.h"

/**
 * @class SingleTapeTransition
 * @brief Represents a transition in a single-tape Turing machine.
 *
 * This class inherits from the Transition class and encapsulates the details
 * of a transition for a single-tape Turing machine, including the destination
 * state, the symbol to read, the symbol to write, and the movement direction.
 *
 * @param destination A shared pointer to the destination state of the transition.
 * @param read The symbol to be read from the tape.
 * @param write The symbol to be written to the tape.
 * @param movement The direction of the tape movement ('L' for left, 'R' for right, etc.).
 */
class SingleTapeTransition : public Transition {
 public:
  SingleTapeTransition(std::shared_ptr<State> destination, Symbol read, Symbol write, char movement)
      : destination_(destination), read_(read), write_(write), movement_(movement) {}

  ~SingleTapeTransition() override = default;

  std::shared_ptr<State> getDestination() const override { return destination_; }
  std::vector<Symbol> getReadSymbols() const override { return {read_}; }
  std::vector<Symbol> getWriteSymbols() const override { return {write_}; }
  std::vector<char> getMoveDirections() const override { return {movement_}; }

 private:
  std::shared_ptr<State> destination_;
  Symbol read_;
  Symbol write_;
  char movement_;
};