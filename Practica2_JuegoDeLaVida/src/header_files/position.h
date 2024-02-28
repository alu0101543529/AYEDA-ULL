/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   position.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Declaración de la clase Position
 */

#pragma once

#include <utility>

/**
 * @brief Clase Position: tipo de dato para representar la posición de las células dentro del retículo (lattice).
 */
class Position {
 public:
 //-CONSTRUCTOR (POR DEFECTO)-
  Position() { 
    position_.first = 0;
    position_.second = 0;
  }
  
  //-----CONSTRUCTOR (PARAMETRIZADO)-----
  Position(const int& x, const int& y) {
    position_.first = x; 
    position_.second = y;
  }

  //---------------GETTER---------------
  /// Getter para obtener el atributo "position_".
  std::pair<int,int> getPosition() const { return position_; }

 private:
  //-------ATRIBUTO-------
  /// position_: representa la posición de la célula dentro del retículo (lattice).
  std::pair<int,int> position_;
};
