/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 1: Autómata Celular Elemental

 * @file   cell.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2024
 * @brief  Declaración de la clase Cell
 */

#pragma once

#include "position.h"
#include "state.h"
#include "lattice.h"

class Lattice;

/**
 * @brief Clase Cell: tipo de dato para representar las células de un autómata celular elemental.
 */
class Cell {
 public:
  //----CONSTRUCTOR (PARAMETRIZADO)----
  Cell(const Position& = Position(0), const State& = State(0));

  //-------GETTER-------
  /// Getter para obtener el atributo "state_".
  State getState() const;

  //-------------SETTER-------------
  /// Setter para establecer el atributo "state_" que se recibe por parámetros.
  State setState(const State&);

  //---------MÉTODOS---------
  // Métodos para obtener las células de posiciones vecinas (izquierda y derecha) de una posición de célula dada.
  Cell LeftNeighbour (const Lattice&);
  Cell RightNeighbour (const Lattice&);

  /// Método para obtener el estado siguiente que la célula tendrá.
  int NextState(const Lattice&);

  /// Método para actualizar el estado de la célula que obtuvo el método NextState().
  void updateState();

 private:
  //-------ATRIBUTOS-------
  /// position_: representa la posición de la célula dentro del retículo (lattice).
  Position position_;
  /// state_: representa el estado de la célula en la generación que se encuentra.
  State state_;
  /// next_gen_: representa el estado de la célula para su siguiente generación.
  State next_gen_;
};

//------------------------MÉTODO I/O------------------------
/// Sobrecarga del operador de flujo de salida (<<) para la clase Cell.
std::ostream& operator<< (std::ostream&, const Cell&);