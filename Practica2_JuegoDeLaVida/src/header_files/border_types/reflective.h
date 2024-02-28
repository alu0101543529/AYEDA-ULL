/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   reflective.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Declaración de la clase heredada Reflective
 */

#pragma once

#include "border.h"

/**
 * @brief Clase Reflective que hereda públicamente de Border
 */
class Reflective : public Border {
 public:
  //--------CONSTRUCTOR (POR DEFECTO)---------
  Reflective() { border_type_ = "reflective"; }
  
  //---------------------------MÉTODO---------------------------
  /// Método polimórfico que devuelve la célula, teniendo en cuenta que el borde es reflectante.
  virtual Cell getCell(const Lattice&, const Position&) override;
};