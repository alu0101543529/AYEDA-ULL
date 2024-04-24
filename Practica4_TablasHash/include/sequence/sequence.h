/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 4: Tabla Hash

 * @file   sequence.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   07/03/2024
 * @brief  Declaración de la clase Sequence
 */

#pragma once

/**
 * @brief Clase abstracta Sequence: tipo de dato para representar una secuencia
 */
template <class Key>
class Sequence {
 public:
  //-----------------MÉTODOS-----------------
  /// Método polimórfico para buscar un elemento en la secuencia
  virtual bool search (const Key&) const = 0;

  /// Método polimórfico para insertar un elemento en la secuencia
  virtual bool insert (const Key&) = 0;

  /// Método polimórfico para saber si la secuencia está llena
  virtual bool isFull() const = 0;

  /// Método polimórfico para imprimir la secuencia
  virtual std::string print() const = 0;
};

// Incluimos las clases que heredan de Sequence
#include "static_sequence.h"
#include "dynamic_sequence.h"