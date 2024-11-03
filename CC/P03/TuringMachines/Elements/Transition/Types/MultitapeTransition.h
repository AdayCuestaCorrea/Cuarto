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
 * @class MultiTapeTransition
 * @brief Represents a transition in a multi-tape Turing machine.
 *
 * This class encapsulates the details of a transition in a multi-tape Turing machine,
 * including the destination state, the symbols to read and write on each tape, and the
 * directions to move the tape heads.
 *
 * @param destination_ The state to transition to.
 * @param read_symbols_ The symbols to read from each tape.
 * @param write_symbols_ The symbols to write to each tape.
 * @param move_directions_ The directions to move the tape heads ('L' for left, 'R' for right, 'N' for no movement).
 *
 * @note This class inherits from the Transition class.
 */
class MultiTapeTransition : public Transition {
 public:
  MultiTapeTransition(std::shared_ptr<State> destination, const std::vector<Symbol>& read_symbols,
                      const std::vector<Symbol>& write_symbols, const std::vector<char>& move_directions)
      : destination_(destination), read_symbols_(read_symbols), write_symbols_(write_symbols), move_directions_(move_directions) {}

  ~MultiTapeTransition() override = default;

  std::shared_ptr<State> getDestination() const override { return destination_; }
  std::vector<Symbol> getReadSymbols() const override { return read_symbols_; }
  std::vector<Symbol> getWriteSymbols() const override { return write_symbols_; }
  std::vector<char> getMoveDirections() const override { return move_directions_; }

 private:
  std::shared_ptr<State> destination_;
  std::vector<Symbol> read_symbols_;
  std::vector<Symbol> write_symbols_;
  std::vector<char> move_directions_;
};