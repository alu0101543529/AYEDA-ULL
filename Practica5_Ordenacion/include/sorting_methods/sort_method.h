/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 5: Ordenación

 * @file   sort_method.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   20/03/2024
 * @brief  Declaración de la clase abstracta SortMethod
 */

#pragma once

#include "../sequence/sequence.h"

/**
 * @brief Clase abstracta SortMethod: tipo de dato para representar la ordenación de una secuencia de elementos.
 */
template <class Key>
class SortMethod {
 public:
  //--------------CONSTRUCTOR--------------
  SortMethod(staticSequence<Key>, unsigned, bool);
  //-----------MÉTODO-----------
  /// Método polimórfico para ordenar una secuencia de elementos.
  virtual void Sort() = 0;

  std::string print() const { return sequence_.print(); }

 protected:
  //------ATRIBUTOS------
  /// sequence_: secuencia de elementos a ordenar.
  staticSequence<Key> sequence_;
  /// size_: tamaño de la secuencia de elementos.
  unsigned size_;
  /// trace_: indica si se debe mostrar el rastro de la ordenación.
  bool trace_;
};

/**
 * @brief Constructor de la clase SortMethod.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: indica si se debe mostrar el rastro de la ordenación.
 */
template <class Key>
SortMethod<Key>::SortMethod(staticSequence<Key> sequence, unsigned size, bool trace) {
  sequence_ = sequence;
  size_ = size;
  trace_ = trace;
}

// Incluimos las clases herederas
#include "selection_sort.h"
#include "quick_sort.h"
#include "heap_sort.h"
#include "shell_sort.h"
#include "radix_sort.h"