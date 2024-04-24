/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 3: Autómata Celular General

 * @file   cell.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   26/02/2024
 * @brief  Declaración de la clase Cell
 */

#pragma once

#include "../position/position.h"
#include "state.h"
#include "lattice.h"

class Lattice;

/**
 * @brief Clase abstracta Cell: tipo de dato para representar las células de un autómata celular general.
 */
class Cell {
 public:
  //-----------------CONSTRUCTOR-----------------
  Cell(const Position&, const State& = State(0));

  //--------GETTER-------
  /// Getter para obtener el atributo "state_".
  State getState() const;

  //----------SETTER----------
  /// Setter para establecer el atributo "state_" que se recibe por parámetros.
  State setState(const State&);

  //-------------------------MÉTODOS-------------------------
  /// Método polimórfico que devuelve una célula dada su posición.
  virtual Cell* GetNeighbour (Position&, const Lattice&) = 0;

  /// Método para obtener el estado siguiente que la célula tendrá.
  virtual int NextState(const Lattice&) = 0;

  /// Método para actualizar el estado de la célula que obtuvo el método NextState().
  void updateState();

  //------------------------MÉTODO I/O------------------------
  /// Sobrecarga del operador de flujo de salida (<<) para la clase Cell.
  friend std::ostream& operator<< (std::ostream&, const Cell&);

 protected:
  //---ATRIBUTOS---
  /// state_: representa el estado de la célula en la generación que se encuentra.
  State state_;
  /// next_gen_: representa el estado de la célula para su siguiente generación.
  State next_gen_;
};