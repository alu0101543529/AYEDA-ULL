/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 3: Autómata Celular General

 * @file   cellACE110.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   26/02/2024
 * @brief  Declaración de la clase CellACE110
 */

#pragma once

#include "cellACE.h"

class Lattice;

/**
 * @brief Clase CellACE30: tipo de dato para representar las células de un autómata celular elemental (que transicionan bajo la regla 110), que hereda públicamente de la clase CellACE.
 */
class CellACE110 : public CellACE {
 public:
  //--------------MÉTODO---------------
  /// Método para obtener el estado siguiente que la célula tendrá siguiendo la regla 110.
  virtual int NextState(const Lattice&) override;
};