/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 4: Tabla Hash

 * @file   exploration_function.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   07/03/2024
 * @brief  Definición de la clase explorationFunction
 */

#pragma once

/**
 * @brief Clase abstracta ExplorationFunction: tipo de dato para representar una función de exploración
 */
template <class Key>
class ExplorationFunction {
 public:
  //--------------------------MÉTODO--------------------------
  /// Sobrecarga polimórfica del operador () para calcular la función de exploración
  virtual unsigned operator() (const Key&, unsigned) const = 0;
};

#include "cuadratic_exploration.h"
#include "lineal_exploration.h"
#include "redispersion_exploration.h"
#include "double_dispersion_exploration.h"