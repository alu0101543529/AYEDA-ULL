/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 1: Autómata Celular Elemental

 * @file   lattice.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2024
 * @brief  Declaración de la clase Lattice
 */

#pragma once

#include <iostream>
#include <vector>

#include "cell.h"

class Cell;

/**
 * @brief Clase Lattice: tipo de dato para representar el retículo donde se almacenan las células de un autómata celular elemental.
 */
class Lattice {
 public:
  //-----------CONSTRUCTOR (PARAMETRIZADO)-----------
  // Si se especifica un tamaño por línea de comandos
  Lattice(int = 1, std::string = "periodic", bool = false);
  // Si se especifica un fichero por línea de comandos
  Lattice(const std::string& filename, std::string = "periodic", bool = false);

  //------------------------------------GETTERS------------------------------------
  /// Getter para obtener las células de la respectiva posición dentro del retículo.
  const Cell& getCell(const Position&) const;

  /// Getter para obtener el tamaño del retículo (lattice).
  int getSize() const { return cells_.size(); }

  /// Getter para obtener el array que representa el retículo (lattice).
  std::vector<Cell> getCells() const { return cells_; }

  /// Getter para obtener el tipo de borde que contiene el retículo (lattice).
  std::string getTypeBorder() const { return type_border_; }

  /// Getter para obtener, en caso de tipo de frontera abierta, la temperatura de las células exteriores que tiene el retículo (lattice).
  bool getOpenBorderTemperature() const { return open_border_temperature_; }

  //------------------------------------GETTERS------------------------------------
  /// Setter para establecer el tipo de borde que contiene el retículo (lattice).
  void setTypeBorder(const std::string& new_type_border) { type_border_ = new_type_border; }

  /// Setter para establecer, en caso de tipo de frontera abierta, la temperatura de las células exteriores que tiene el retículo (lattice).
  void setOpenBorderTemperature(const bool& new_open_border_temperature) { open_border_temperature_ = new_open_border_temperature; }

  //------------------------------------MÉTODOS------------------------------------
  /// Método que aplica la función de transición al retículo actualizando todas las células.
  void nextGeneration();

  /// Método para inicializar el retículo con un valor inicial en las células.
  void InitialSetting();

  /// Método para calcular el número de células vivas en la generación actual en la que se encuentra el retículo.
  int AliveCells();

  // Método para calcular el número de células muertas en la generación actual en la que se encuentra el retículo.
  int DeadCells();

  // Método para cargar un retículo desde un fichero.
  void OpenFile(const std::string&);

 private:
  //----------------------ATRIBUTOS----------------------
  /// cells_: representa el espacio donde viven las células.
  std::vector<Cell> cells_;
  /// type_border_: representa el tipo de borde que tiene el retículo.
  std::string type_border_;
  /// open_border_temperature_: representa, en caso de ser frontera abierta, el estado/temperatura que tendrán las células exteriores del retículo.
  bool open_border_temperature_;
};

//--------------------------MÉTODO I/O--------------------------
/// Sobrecarga del operador de flujo de salida (<<) para la clase Lattice.
std::ostream& operator<< (std::ostream&, const Lattice&);