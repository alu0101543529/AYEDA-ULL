/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 3: Autómata Celular General

 * @file   cellLife23_3.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   26/02/2024
 * @brief  Declaración de la clase CellLife23_3
 */

#pragma once

#include "cellLife.h"

class Lattice;

/**
 * @brief Clase CellLife51_346: tipo de dato para representar las células del Juego de la Vida (que transicionan bajo la regla 51/346), que hereda públicamente de la clase CellLife.
 */
class CellLife51_346 : public CellLife {
 public:
  //-------------------MÉTODO-------------------
  /// Método para obtener el estado siguiente que la célula tendrá, siguiendo la regla 51/346
  virtual int NextState(const Lattice&) override;
};