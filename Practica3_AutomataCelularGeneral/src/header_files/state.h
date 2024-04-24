/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   state.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Declaración de la clase State
 */

#pragma once

/**
 * @brief Clase State: tipo de dato para representar el estado de las células.
 */
class State {
 public:
  State() { state_ = 0; }
  //-------CONSTRUCTOR (PARAMETRIZADO)-------
  State(const int& state) { state_ = state; }

  //---------------GETTER---------------
  /// Getter para obtener el atributo "state_".
  int getState() const { return state_; }

 private:
  //-------ATRIBUTO-------
  /// state_: representa el estado de la célula en la generación que se encuentra.
  int state_;
};
