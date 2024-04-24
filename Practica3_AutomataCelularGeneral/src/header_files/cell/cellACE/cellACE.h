/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 3: Autómata Celular General

 * @file   cellACE.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   26/02/2024
 * @brief  Declaración de la clase CellACE
 */

#pragma once

#include "../cell.h"

class Lattice;

/**
 * @brief Clase CellACE: tipo de dato para representar las células de un autómata celular elemental, que hereda públicamente de la clase Cell.
 */
class CellACE : public Cell {
 public:
  //------------------CONSTRUCTOR------------------
  CellACE(const Position&, const State& = State(0));

  //-------------------------MÉTODOS-------------------------
  /// Método polimórfico que devuelve una célula dada su posición.
  Cell* GetNeighbour (Position&, const Lattice&) override;

  /// Método polimórfico para obtener el estado siguiente que la célula tendrá.
  virtual int NextState(const Lattice&) = 0;

 protected:
  //-------ATRIBUTO-------
  /// position_: representa la posición de la célula dentro del retículo unidimensional (Lattice1D).
  PositionDim<1> position_;
  
};