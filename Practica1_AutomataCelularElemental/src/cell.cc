/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 1: Autómata Celular Elemental

 * @file   cell.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2024
 * @brief  Implementación de la clase Cell
 */

#include "header_files/cell.h"

/**
 * @brief Constructor de Cell.
 * @param[in] position: referencia (constante) a la posición de la célula dentro del retículo.
 * @param[in] state: referencia (constante) al estado inicial de la célula.
 */
Cell::Cell (const Position& position, const State& state) {
  position_ = position;
  state_ = state;
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
  old_state = state_;   // Guardamos el estado en una nueva variable para posteriormente devolverlo.
  state_ = new_state;   // Actualizamos el estado al nuevo requerido.
  return old_state;
}

/**
 * @brief Método que mediante un autómata calcula el estado que adquiere la célula en la siguiente generación, pero no lo actualiza.
 * @param[in] lattice: referencia constante al retículo donde están almacenadas todas las células.
 * @return Devuelve el estado que adquiere la célula en su siguiente generación.
 */
int Cell::NextState(const Lattice& lattice) {
  Cell Right = RightNeighbour(lattice);
  Cell Left = LeftNeighbour(lattice);
  next_gen_ = State((state_ + Right.getState() + (state_ * Right.getState()) + (Left.getState() * state_ * Right.getState())) % 2);
  return next_gen_.getState();
}

/**
 * @brief Método que actualiza el estado de las células, previamente hallado con el método NextState().
 */
void Cell::updateState() { state_ = next_gen_; }

/**
 * @brief Método que obtiene la célula vecina izquierda dada una célula central.
 * @param[in] lattice: referencia constante al retículo donde están almacenadas todas las células.
 * @return Devuelve la célula vecina izquierda a la célula central invocada.
 */
Cell Cell::LeftNeighbour (const Lattice& lattice) { 
  Position left_neighbour_position = (position_.getPosition() - 1);
  // En caso de que el tipo de frontera se abierta, y la posición de la célula sea la primera de la retícula, crearemos una "célula imaginaria" con el estado que determine el usuario dependiendo de la temperatura.
  if (lattice.getTypeBorder() == "open" && position_.getPosition() == 0) {
    return Cell(left_neighbour_position, lattice.getOpenBorderTemperature());
  }
  // En caso de que el tipo de frontera sea periódica, al salirse del rango del retículo el operador de módulo se encarga de "replicar" el mismo retículo a ambos lados de este.
  return lattice.getCell(left_neighbour_position.getPosition() % lattice.getCells().size());
}

/**
 * @brief Método que obtiene la célula vecina derecha dada una célula central.
 * @param[in] lattice: referencia constante al retículo donde están almacenadas todas las células.
 * @return Devuelve la célula vecina derecha a la célula central invocada.
 */
Cell Cell::RightNeighbour (const Lattice& lattice) {
  Position right_neighbour_position = (position_.getPosition() + 1);
  // En caso de que el tipo de frontera se abierta, y la posición de la célula sea la última de la retícula, crearemos una "célula imaginaria" con el estado que determine el usuario dependiendo de la temperatura.
  if ((lattice.getTypeBorder() == "open") && (position_.getPosition() == (lattice.getSize() - 1))) {
    return Cell(right_neighbour_position, lattice.getOpenBorderTemperature());
  } 
  // En caso de que el tipo de frontera sea periódica, al salirse del rango del retículo el operador de módulo se encarga de "replicar" el mismo retículo a ambos lados de este.
  return lattice.getCell(right_neighbour_position.getPosition() % lattice.getCells().size());
}

/**
 * @brief sobrecarga del operador de flujo de salida (<<) para la clase Cell.
 * @param[in] os: referencia al objeto ostream (flujo de datos de salida).
 * @param[in] cell: referencia (constante) de la célula a imprimir.
 * @return Devuelve la impresión de la célula.
 */
std::ostream& operator<< (std::ostream& os, const Cell& cell) {
  if (cell.getState().getState() == 0) { os << ' '; }
  else { os << 'X'; }

  return os;
}