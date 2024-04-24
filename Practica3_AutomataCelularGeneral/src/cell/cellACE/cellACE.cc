/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 3: Autómata Celular General

 * @file   cellACE.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   26/02/2024
 * @brief  Implementación de la clase CellACE
 */

#include "header_files/cell/cellACE/cellACE.h"

/**
 * @brief Constructor de CellACE.
 * @param[in] position: referencia (constante) a la posición de la célula.
 * @param[in] state: referencia (constante) al estado de la célula.
 */
CellACE::CellACE(const Position& position, const State& state) {
  //Rellenar código Constructor
}

/**
 * @brief Método que dada una posición dentro del retículo devuelve la célula en dicha posición.
 * @param[in] position: referencia a la posición de la célula.
 * @param[in] lattice: referencia (constante) al retículo donde están almacenadas todas las células.
 * @return Devuelve la célula en la posición especificada por parámetros.
 */
Cell* CellACE::GetNeighbour(Position& position, const Lattice& lattice) { 
  //Rellenar código GetNeighbour
}
