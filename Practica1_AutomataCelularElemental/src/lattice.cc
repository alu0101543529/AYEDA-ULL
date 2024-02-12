/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 1: Autómata Celular Elemental

 * @file   lattice.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2024
 * @brief  Implementación de la clase Lattice
 */
#include "header_files/cell.h"
#include "header_files/lattice.h"
#include <cassert>

/**
 * @brief Constructor del retículo.
 * @param[in] size: entero que representa el tamaño que tendrá el retículo.
 * @param[in] type_border: cadena de caracteres que representa el tipo de frontera que tiene el retículo.
 * @param[in] open_border_temperatura: booleano que representa, en caso de ser frontera abierta, el estado que tendran las células exteriores al retículo.
 */
Lattice::Lattice(int size, std::string type_border, bool open_border_temperature) {
  assert (size > 0);
  cells_.resize(size);
  type_border_ = type_border;
  open_border_temperature_ = open_border_temperature;
  InitialSetting();
}

/**
 * @brief Método que establece la configuración inicial del retículo.
 */
void Lattice::InitialSetting() {
  for (int i = 0; i <= cells_.size(); i++) { cells_[i] = Cell(Position(i), 0); }
  cells_[(cells_.size() / 2)].setState(State(1));
}

/**
 * @brief Método que obtiene una célula del retículo dada su posición por parámetros.
 * @param[in] position: referencia constante a la posición de la célula que deseamos obtener.
 */
const Cell& Lattice::getCell(const Position& position) const {
  assert(position.getPosition() >= 0 && position.getPosition() < getSize());
  return (cells_[position.getPosition()]); 
}

/**
 * @brief Método que actualiza los estados de todas las células del retículo a su siguiente generación.
 */
void Lattice::nextGeneration() {
  // Primero hacemos un recorrido de todo el retículo calculando el siguiente estado que tendrán las células.
  for (int i = 0; i < cells_.size(); i++) { cells_[i].NextState(*this); }
  // Posteriormente, vamos actualizando las células a su siguiente estado previamente calculado
  for (int i = 0; i < cells_.size(); i++) { cells_[i].updateState(); }
}

/**
 * @brief Método que calcula el número de células vivas en el retículo en su generación actual.
 * @return Devuelve el número de células vivas.
 */
int Lattice::AliveCells() {
  int cells_alive_counter{0};
  for (int i = 0; i < cells_.size(); i++) {
    if (getCell(Position(i)).getState().getState() == State(1).getState()) { cells_alive_counter++; }
  }
  return cells_alive_counter;
}

/**
 * @brief Método que calcula el número de células muertas en el retículo en su generación actual.
 * @return Devuelve el número de células muertas.
 */
int Lattice::DeadCells() {
  int cells_dead_counter{0};
  for(int i = 0; i < cells_.size(); i++) {
    if (getCell(Position(i)).getState().getState() == State(0).getState()) { cells_dead_counter++; }
  }
  return cells_dead_counter;
}

/**
 * @brief sobrecarga del operador de flujo de salida (<<) para la clase Lattice.
 * @param[in] os: referencia al objeto ostream (flujo de datos de salida).
 * @param[in] lattice: referencia (constante) del retículo a imprimir.
 * @return Devuelve la impresión del retículo.
 */
std::ostream& operator<< (std::ostream& os, const Lattice& lattice) {
  for (int i = 0; i < lattice.getCells().size(); i++) { os << lattice.getCell(Position(i)); }
  os << std::endl;

  return os;
}