/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 4: Tabla Hash

 * @file   cuadratic_exploration.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   07/03/2024
 * @brief  Definición de la clase CuadraticExploration
 */

#pragma once

#include "exploration_function.h"

/**
 * @brief Clase CuadraticExploration: tipo de dato para representar una función de exploración cuadrática
 */
template <class Key>
class CuadraticExploration : public ExplorationFunction<Key> {
 public:
  //-----------------------------MÉTODO-----------------------------
  /// Sobrecarga del operador () para calcular la función de exploración cuadrática
  virtual unsigned operator() (const Key&, unsigned) const override;
};

/**
 * @brief Sobrecarga del operador () para calcular la función de exploración cuadrática
 * @param[in] key: referencia (constante) al elemento a buscar
 * @param[in] i: número de intentos
 * @return Devuelve el resultado de la función de exploración cuadrática
 */
template <class Key>
unsigned CuadraticExploration<Key>::operator() (const Key& key, unsigned i) const { return (key * key) * i; }