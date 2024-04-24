/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   cell.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Implementación de la clase Cell
 */

#include "header_files/cell/cell.h"

Cell::Cell(const Position&, const State&) {
  //Rellenar código Constructor
}

/**
 * @brief Método que obtiene el atributo que representa el estado de la célula (state_).
 * @return Devuelve el atributo privado que representa el estado de la célula (state_).
 */
State Cell::getState() const { return state_; }

/**
 * @brief Método que establece un nuevo estado a la célula pasado por parámetros.
 * @param[in] new_state: referencia constante al nuevo estado de la célula.
 * @return Devuelve el estado en el que se encontraba la célula previa a ser cambiado.
 */
State Cell::setState(const State& new_state) { 
  State old_state;
  old_state = state_;   // Guardamos el estado en una nueva variable para posteriormente devolverla.
  state_ = new_state;   // Actualizamos el estado al nuevo requerido.
  return old_state;
}

/**
 * @brief Método que actualiza el estado de las células, previamente hallado con el método NextState().
 */
void Cell::updateState() { state_ = next_gen_; }

/**
 * @brief sobrecarga del operador de flujo de salida (<<) para la clase Cell.
 * @param[in] os: referencia al objeto ostream (flujo de datos de salida).
 * @param[in] cell: referencia (constante) de la célula a imprimir.
 * @return Devuelve la impresión por pantalla de la célula.
 */
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  // En caso de que la célula se encuentre en estado muerta, la representaremos como ' '.
  if (cell.getState().getState() == 0) { os << ' '; }
  // En caso de que esté viva su representación es 'X'.
  else { os << 'X'; }

  return os;
}