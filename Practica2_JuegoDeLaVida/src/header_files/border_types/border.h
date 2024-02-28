/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   border.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Declaración de la clase abstracta Border
 */

#pragma once

#include <string>

#include "../lattice.h"

class Lattice;
class Cell;

class Border {
 public:
  //------------------------MÉTODOS------------------------
  /// Método que comprueba si alguna célula se encuentra fuera del retículo.
  bool isOut(const Lattice&, const Position&);
  
  /// Método polimórfico que devuelve la célula correspondiente para cada tipo de borde.
  virtual Cell getCell(const Lattice&, const Position&) = 0;
 
 protected:
  std::string border_type_;
};