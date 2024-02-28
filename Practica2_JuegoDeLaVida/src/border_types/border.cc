/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   border.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Implementación de la clase abstracta Border
 */

#include "../header_files/border_types/border.h"

/**
 * @brief Método que comprueba si alguna célula se encuentra fuera del retículo.
 * @param[in] lattice: referencia (constante) al retículo donde están almacenadas todas las células.
 * @param[in] position: referencia (constante) a la posición de la célula dentro del retículo.
 */
bool Border::isOut(const Lattice& lattice, const Position& position) {
  if (position.getPosition().first  < 0 || position.getPosition().first  >= lattice.getRows() ||
      position.getPosition().second < 0 || position.getPosition().second >= lattice.getCols()) {
    return true;
  }
  return false;
}