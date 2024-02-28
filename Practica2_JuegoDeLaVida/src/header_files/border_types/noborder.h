/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   noborder.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Declaración de la clase heredada NoBorder
 */

#pragma once

#include "border.h"

/**
 * @brief Clase NoBorder que hereda públicamente de Border
 */
class NoBorder : public Border {
 public:
  //-------CONSTRUCTOR (POR DEFECTO)-------
  NoBorder() { border_type_ = "no border"; }

  //-----------MÉTODOS-----------
  /// Método que comprueba si las celdas de los bordes están vivas o muertas.
  void CheckCells(const Lattice&);
  /// Método que añade bordes al retículo, si CheckCells() lo indica.
  void addBorder(Lattice&);
  /// Método que reindexa las células del retículo.
  void ReIndex(Lattice&);
  
  /// Método polimórfico que devuelve la célula, teniendo en cuenta que el borde es no existente.
  virtual Cell getCell(const Lattice&, const Position&) override;


 private:
  //-------ATRIBUTOS-------
  /// Atributos que indican si se deben añadir filas o columnas al retículo.
  bool add_up_row = false;
  bool add_down_row = false;
  bool add_left_col = false;
  bool add_right_col = false;
};