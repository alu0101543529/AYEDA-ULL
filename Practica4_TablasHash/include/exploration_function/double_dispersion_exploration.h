/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 4: Tabla Hash

 * @file   double_dispertion_exploration.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   07/03/2024
 * @brief  Definición de la clase DoubleDispertionExploration
 */

#pragma once

#include "exploration_function.h"

/**
 * @brief Clase DoubleDispertionExploration: tipo de dato para representar una función de exploración por doble dispersión
 */
template <class Key>
class DoubleDispersionExploration : public ExplorationFunction<Key> {
 public:
  //----------------------------CONSTRUCTOR----------------------------
  DoubleDispersionExploration(DispersionFunction<Key>* fd) : fd_(fd) {}

  //-----------------------------MÉTODO-----------------------------
  /// Sobrecarga del operador () para calcular la función de exploración por doble dispersión
  virtual unsigned operator() (const Key&, unsigned) const override;

 private:
  //---------ATRIBUTO---------
  /// fd_: representa la función de dispersión
  DispersionFunction<Key>* fd_;
};

/**
 * @brief Sobrecarga del operador () para calcular la función de exploración por doble dispersión
 * @param[in] key: referencia (constante) al elemento a buscar
 * @param[in] i: número de intentos
 * @return Devuelve el resultado de la función de exploración por doble dispersión
 */
template <class Key>
unsigned DoubleDispersionExploration<Key>::operator() (const Key& key, unsigned i) const { return (fd_->operator()(key) * i); } 