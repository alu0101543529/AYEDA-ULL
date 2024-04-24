/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   reflective.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Implementación de la clase heredada Reflective
 */

#include <cmath>

#include "../header_files/border_types/reflective.h"

/**
 * @brief Método polimórfico que devuelve la célula, teniendo en cuenta que el borde es reflectante.
 * @param[in] lattice: referencia constante al retículo donde están almacenadas todas las células.
 * @param[in] position: referencia (constante) a la posición de la célula dentro del retículo.
 * @return Devuelve la célula en la posición especificada por parámetros, con la condición de que la frontera es reflectante.
 */
Cell Reflective::getCell(const Lattice& lattice, const Position& position) {
  int row = position.getPosition().first;
  int col = position.getPosition().second;

  // Si la posición está fuera del retículo, se calcula la posición correspondiente en el retículo reflectante.
  if (isOut(lattice, position)) {
    if (row < 0) { row++; }
    else if (row >= lattice.getRows()) { row--; }

    if (col < 0) { col++; }
    else if (col >= lattice.getCols()) { col--; }
  }

  return lattice[Position(row, col)];
}