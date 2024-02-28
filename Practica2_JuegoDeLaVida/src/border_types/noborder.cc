/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   noborder.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Implementación de la clase heredada NoBorder
 */

#include "../header_files/border_types/noborder.h"

/**
 * @brief Método que comprueba si hay alguna célula en las filas/columnas limítrofes del retículo.
 * @param[in] lattice: referencia (constante) al retículo donde están almacenadas todas las células. */
void NoBorder::CheckCells(const Lattice& lattice) {
  //Recorremos la primera y la última fila del retículo comprobando si hay alguna célula en estas.
  for (int i = 0; i < lattice.getRows(); i++) {
    if (lattice.getCell(Position(i, 0)).getState().getState() == 1) {
      add_left_col = true;
    }
    if (lattice.getCell(Position(i, lattice.getCols() - 1)).getState().getState() == 1) {
      add_right_col = true;
    }
  }
  
  //Recorremos la primera y la última columna del retículo comprobando si hay alguna célula en estas.
  for (int i = 0; i < lattice.getCols(); i++) {
    if (lattice.getCell(Position(0, i)).getState().getState() == 1) {
      add_up_row = true;
    }
    if (lattice.getCell(Position((lattice.getRows() - 1), i)).getState().getState() == 1) {
      add_down_row = true;
    }
  }
}

/**
 * @brief Método que añade una fila/columna al retículo si el método CheckCells() así lo contempla.
 * @param[in] lattice: referencia al retículo donde están almacenadas todas las células.
 */
void NoBorder::addBorder(Lattice& lattice) {
  // Añadir fila superior
  if (add_left_col == true) {
    for (int i = 0; i < lattice.getRows(); i++) { lattice.getCells()[i].insert(lattice.getCells()[i].begin(), Cell(Position(i, 0))); }
    lattice.setCols(lattice.getCols() + 1);
  }
  // Añadir fila inferior
  if (add_right_col == true) {
    for (int i = 0; i < lattice.getRows(); i++) { lattice.getCells()[i].push_back(Cell(Position(i, lattice.getCols()))); }
    lattice.setCols(lattice.getCols() + 1);
  }
  // Añadir columna izquierda
  if (add_up_row == true) {
    lattice.getCells().insert(lattice.getCells().begin(), std::vector<Cell>(lattice.getCols()));
    lattice.setRows(lattice.getRows() + 1);
  }
  // Añadir columna derecha
  if (add_down_row) {
    lattice.getCells().push_back(std::vector<Cell>(lattice.getCols()));
    lattice.setRows(lattice.getRows() + 1);
  }
}

/**
 * @brief Método que reindexa las células del retículo.
 * @param[in] lattice: referencia al retículo donde están almacenadas todas las células.
 */
void NoBorder::ReIndex(Lattice& lattice) {
  for (int i = 0; i < lattice.getRows(); i++) {
    for (int j = 0; j < lattice.getCols(); j++) {
      lattice.getCells()[i][j].setPosition(Position(i, j));
    }
  }
}

/**
 * @brief Método polimórfico que devuelve la célula, teniendo en cuenta que el borde es no existente.
 * @param[in] lattice: referencia constante al retículo donde están almacenadas todas las células.
 * @param[in] position: referencia (constante) a la posición de la célula dentro del retículo.
 * @return Devuelve la célula en la posición especificada por parámetros, con la condición de que la frontera no existe.
 */
Cell NoBorder::getCell(const Lattice& lattice, const Position& position) {
  // Comprobamos si hay que añadir una fila/columna al retículo.
  CheckCells(lattice);
  // Añadimos la fila/columna al retículo si el método CheckCells() así lo contempla.
  addBorder(const_cast<Lattice&>(lattice));
  // Reindexamos las células del retículo.
  ReIndex(const_cast<Lattice&>(lattice));

  return lattice[position];
}
