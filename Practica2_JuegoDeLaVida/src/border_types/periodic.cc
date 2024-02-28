/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   periodic.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Implementación de la clase heredada Periodic
 */

#include <cmath>

#include "../header_files/border_types/periodic.h"

/**
 * @brief Método polimórfico que devuelve la célula, teniendo en cuenta que el borde es periódico.
 * @param[in] lattice: referencia constante al retículo donde están almacenadas todas las células.
 * @param[in] position: referencia (constante) a la posición de la célula dentro del retículo.
 * @return Devuelve la célula en la posición especificada por parámetros, con la condición de que la frontera es periódica.
 */
Cell Periodic::getCell(const Lattice& lattice, const Position& position) {
  int row = position.getPosition().first;
  int col = position.getPosition().second;

  // Si la posición está fuera del retículo, se calcula la posición correspondiente en el retículo periódico.
  if (isOut(lattice, position)) {
    if (row < 0) { row = lattice.getRows() - (abs(row) % lattice.getRows()); } 
    row %= lattice.getRows();
    
    if (col < 0) { col = lattice.getCols() - (abs(col) % lattice.getCols()); }
    col %= lattice.getCols();
  }
  return lattice[Position(row, col)];
}