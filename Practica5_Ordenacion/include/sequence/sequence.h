/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 5: Ordenación

 * @file   sequence.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   20/03/2024
 * @brief  Declaración de la clase abstracta Sequence
 */

#pragma once

#include <iostream>
#include <string>

// Definimos el tipo de dato Position como un entero sin signo
typedef unsigned Position;

/**
 * @brief Clase abstracta Sequence: tipo de dato para representar una secuencia de datos
 */
template <class Key>
class Sequence {
 public:
  //--------------GETTER--------------
  /// Getter del tamaño de la secuencia de elementos
  virtual unsigned getSize() const = 0;

  //-----------------MÉTODOS-----------------
  /// Sobrecarga polimórfica del operador de indexación
  virtual bool search (const Key&) const = 0;

  /// Método polimórfico para insertar un elemento en la secuencia
  virtual bool insert (const Key&) = 0;

  /// Método polimórfico para saber si la secuencia está llena
  virtual bool isFull() const = 0;

  /// Método polimórfico para imprimir la secuencia
  virtual std::string print() const = 0;

  /// Sobrecarga polimórfica del operador de indexación ([])
  virtual Key& operator[](Position) = 0;

  /// Sobrecarga polimórfico del operador de inserción del flujo de entrada (<<)
  virtual std::ostream& operator<<(std::ostream&) const = 0;
};

// Incluimos la clase heredera
#include "static_sequence.h"