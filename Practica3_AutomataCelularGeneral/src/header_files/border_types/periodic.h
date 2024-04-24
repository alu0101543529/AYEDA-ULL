/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   periodic.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Declaración de la clase heredada Periodic
 */

#pragma once

#include "border.h"

/**
 * @brief Clase Periodic que hereda públicamente de Border
 */
class Periodic : public Border {
 public:
  //-----CONSTRUCTOR (POR DEFECTO)-----
  Periodic() { border_type_ = "open"; }

  //---------------------------MÉTODO---------------------------
  /// Método polimórfico que devuelve la celda en la posición dada, teniendo que el borde es periódico.
  virtual Cell getCell(const Lattice&, const Position&) override;
};