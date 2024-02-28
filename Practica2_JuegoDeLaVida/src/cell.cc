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

#include "header_files/cell.h"

/**
 * @brief Constructor de Cell.
 * @param[in] position: referencia (constante) a la posición de la célula dentro del retículo.
 * @param[in] state: referencia (constante) al estado inicial de la célula.
 */
Cell::Cell(const Position& position, const State& state) {
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
  old_state = state_;   // Guardamos el estado en una nueva variable para posteriormente devolverla.
  state_ = new_state;   // Actualizamos el estado al nuevo requerido.
  return old_state;
}

void Cell::setPosition(const Position& new_position) { position_ = new_position; }

/**
 * @brief Método que según el estado de sus células "vecinas" calcula el estado que adquiere la célula en la siguiente generación, pero no lo actualiza.
 * @param[in] lattice: referencia constante al retículo donde están almacenadas todas las células.
 * @return Devuelve el estado que adquiere la célula en su siguiente generación.
 */
int Cell::NextState(const Lattice& lattice) {
  // Definimos en distintas variables las posiciones de todas las células adyacentes tanto en el eje "x", como en el eje "y" respectivamente.
  //                  NO   O  SO  S  SE  E  NE   N
  int movement_x[] = {-1, -1, -1, 0,  1, 1,  1,  0};
  int movement_y[] = {-1,  0,  1, 1,  1, 0, -1, -1};

  // Definimos una variable que almacenará el número de células vecinas en estado 'viva' para posteriormente saber el estado que tendrá la célula que estamos tratando.
  int alive_neighbors = 0;

  // Recorremos todas las células vecinas, almacenando el número de células vivas en la variable definida para esa función.
  for (int i = 0; i < 8; i++) { 
    alive_neighbors += lattice.getBorder()->getCell(lattice, 
                                                    Position((position_.getPosition().first + movement_x[i]), 
                                                             (position_.getPosition().second + movement_y[i]))).getState().getState();
  }
  
  // Aplicamos la regla de transición 23/3, que consiste en lo siguiente:
  // En caso de que la célula en la generación actual este viva:
  if (state_.getState() == 1) {
    // Continuará viva si tiene 2 ó 3 células vivas adyacentes.
    if (alive_neighbors == 2 || alive_neighbors == 3) { next_gen_ = State(1); }
    // En cualquier otro caso morirá.
    else { next_gen_ = State(0); }
  }
  // Y en caso que la céula en la generación actual esté muerta:
  else {
    // Deberá tener exactamente 3 células vivas adyacentes para revivir.
    if (alive_neighbors == 3) { next_gen_ = State(1); }
    // En cualquier otro caso continuará muerta.
    else { next_gen_ = State(0); }
  }

  return next_gen_.getState();
}

/**
 * @brief Método que actualiza el estado de las células, previamente hallado con el método NextState().
 */
void Cell::updateState() { state_ = next_gen_; }

/**
 * @brief Método que dada unas posiciones dentro del retículo devuelven la célula en dicha posición.
 * @param[in] x: referencia (constante) a la posición en el eje "x" de la célula.
 * @param[in] y: referencia (constante) a la posición en el eje "y" de la célula.
 * @param[in] lattice: referencia (constante) al retículo donde están almacenadas todas las células.
 * @return Devuelve la célula en la posición especificada por parámetros.
 */
Cell Cell::GetNeighbour(const int& x, const int& y, const Lattice& lattice) { return lattice.getCell(Position(x,y)); }

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