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

#include "LRSTuringMachineTape.h"
#include <iostream>

/**
 * @brief Reads the symbol at the current head position on the tape.
 * 
 * This function returns the symbol located at the current head position
 * on the Turing machine's tape. The head position is maintained internally
 * by the LRSTuringMachineTape class.
 * 
 * @return char The symbol at the current head position on the tape.
 */
char LRSTuringMachineTape::read() const {
  return tape_[head_position_];
}

/**
 * @brief Writes a symbol at the current head position on the tape.
 * 
 * This function updates the tape by writing the specified symbol at the 
 * current head position. The head position is an index that indicates 
 * where on the tape the write operation should occur.
 * 
 * @param symbol The character to be written on the tape.
 */
void LRSTuringMachineTape::write(char symbol) {
  tape_[head_position_] = symbol;
}

/**
 * @brief Moves the tape head one position to the left.
 * 
 * If the head is not at the beginning of the tape, it simply decrements the head position.
 * If the head is at the beginning of the tape, it inserts a blank symbol ('.') at the start of the tape
 * and keeps the head position at the beginning.
 */
void LRSTuringMachineTape::moveLeft() {
  if (head_position_ > 0) {
    head_position_--;
  } else {
    tape_.insert(tape_.begin(), '.');
  }
}

/**
 * @brief Moves the tape head one position to the right.
 * 
 * Increments the head position by one. If the head position exceeds the current
 * size of the tape, a blank symbol ('.') is appended to the tape to extend it.
 */
void LRSTuringMachineTape::moveRight() {
  head_position_++;
  if (head_position_ >= tape_.size()) {
    tape_.push_back('.');
  }
}