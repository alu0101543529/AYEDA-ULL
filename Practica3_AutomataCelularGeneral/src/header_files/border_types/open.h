/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   open.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Declaración de la clase heredada Open
 */

#pragma once

#include "border.h"

/**
 * @brief Clase Open que hereda públicamente de Border
 */
class Open : public Border {
 public:
  //-------CONSTRUCTOR (POR DEFECTO)-------
  Open(int temperature) { 
    border_type_ = "open"; 
    temperature_ = temperature;
  }

  //---------------------------MÉTODO---------------------------
  /// Método polimórfico que devuelve la célula, teniendo en cuenta que el borde es abierto.
  virtual Cell getCell(const Lattice&, const Position&) override;

 private:
  //---ATRIBUTO---
  /// Atributo que indica la temperatura del borde.
  int temperature_;
};