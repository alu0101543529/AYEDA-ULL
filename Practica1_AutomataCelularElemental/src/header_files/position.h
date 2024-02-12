/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 1: Autómata Celular Elemental

 * @file   position.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2024
 * @brief  Declaración de la clase Position
 */

#pragma once

/**
 * @brief Clase Position: tipo de dato para representar la posición de las células dentro del retículo (lattice).
 */
class Position {
 public:
 //-CONSTRUCTOR (POR DEFECTO)-
  Position() { position_ = 0; }
  //-------------CONSTRUCTOR (PARAMETRIZADO)-------------
  Position(const int& position) { position_ = position; }

  //---------------GETTER---------------
  /// Getter para obtener el atributo "position_".
  int getPosition() const { return position_; }

 private:
  //-------ATRIBUTO-------
  /// position_: representa la posición de la célula dentro del retículo (lattice).
  int position_;
};
