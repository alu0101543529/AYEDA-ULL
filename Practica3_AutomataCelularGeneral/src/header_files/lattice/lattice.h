/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   lattice.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Declaración de la clase Lattice
 */

#pragma once

#include <iostream>
#include <vector>

#include "cell.h"
#include "border_types/border.h"

class Cell;
class Border;

/**
 * @brief Clase Lattice: tipo de dato para representar el retículo donde se almacenan las células de un autómata celular elemental.
 */
class Lattice {
 public:
  //-----------CONSTRUCTOR (PARAMETRIZADO)-----------
  // Si se especifica un tamaño por línea de comandos
  Lattice(int, int, std::string = "periodic", int = 0);
  // Si se especifica un fichero por línea de comandos
  Lattice(const std::string& filename, std::string = "periodic", int = 0);

  //------------------------------------GETTERS------------------------------------
  /// Getters para obtener el número de filas/columnas de la matriz <=> retículo donde viven las células.
  int getRows() const { return cells_.size(); }
  int getCols() const { return cells_[0].size(); }

  /// Getter para obtener las célula de una posición (especificada por parámetros) dentro del retículo.
  const Cell getCell(const Position&) const;

  /// Getter para obtener la metriz que representa el retículo (lattice).
  std::vector<std::vector<Cell>> getCells() const { return cells_; }

  /// Getter para obtener el tipo de borde que tiene el retículo.
  Border* getBorder() const { return border_type_; }

  //-----------------------SETTERS-----------------------
  /// Setter para establecer el número de filas/columnas de la matriz <=> retículo donde viven las células.
  void setRows(const int& new_rows) { rows_ = new_rows; }
  void setCols(const int& new_cols) { cols_ = new_cols; }

  //------------MÉTODOS------------
  /// Método que aplica la función de transición al retículo actualizando todas las células.
  void nextGeneration();

  /// Método para inicializar el retículo con un valor inicial en las células.
  void InitialSetting();

  /// Método para calcular el número de células vivas en la generación actual en la que se encuentra el retículo.
  std::size_t Population() const;

  /// Método para cargar un retículo desde un fichero.
  void OpenFile(const std::string&);

  /// Método para guardar un retículo en un fichero.
  void SaveFile(const std::string&);

  //------SOBRECARGA DE OPERADORES------
  /// Sobrecarga del operador de indexación ([]) para acceder a una célula dada su posición (por parámetros) dentro del retículo.
  Cell operator[](const Position&) const;

 private:
  //----------------------ATRIBUTOS----------------------
  /// cells_: representa la matriz <=> retículo donde viven las células.
  std::vector<std::vector<Cell>> cells_;
  /// border_type_: representa el tipo de borde (tipo de dato polimórfico) que tiene el retículo.
  Border* border_type_;
  /// rows_: representa el número de filas de la matriz <=> retículo donde viven las células.
  int rows_;
  /// cols_: representa el número de columnas de la matriz <=> retículo donde viven las células.
  int cols_;
};

//--------------------------MÉTODO I/O--------------------------
/// Sobrecarga del operador de flujo de salida (<<) para la clase Lattice.
std::ostream& operator<< (std::ostream&, const Lattice&);