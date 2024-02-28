/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   open.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Implementación de la clase heredada Open
 */

#include "../header_files/border_types/open.h"

/**
 * @brief Método polimórfico que devuelve la célula, teniendo en cuenta que el borde es abierto.
 * @param[in] lattice: referencia constante al retículo donde están almacenadas todas las células.
 * @param[in] position: referencia (constante) a la posición de la célula dentro del retículo.
 * @return Devuelve la célula en la posición especificada por parámetros, con la condición de que la frontera es abierta.
 */
Cell Open::getCell(const Lattice& lattice, const Position& position) {
  if (isOut(lattice, position)) {
    return (Cell(Position((position.getPosition().first - 1), (position.getPosition().second - 1)), State(temperature_)));
  }
  return lattice.getCell(position);
}