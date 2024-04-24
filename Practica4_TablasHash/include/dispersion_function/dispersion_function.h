/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 4: Tabla Hash

 * @file   dispersion_function.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   07/03/2024
 * @brief  Definición de la clase dispersionFunction
 */

#pragma once

/**
 * @brief Clase abstracta DispersionFunction: tipo de dato para representar una función de dispersión
 */
template <class Key>
class DispersionFunction {
 public:
  //---------------------MÉTODO---------------------
  /// Sobrecarga polimórfica del operador () para calcular la función de dispersión
  virtual unsigned operator() (const Key&) const = 0;
};

#include "module.h"
#include "sum_based.h"
#include "random.h"
