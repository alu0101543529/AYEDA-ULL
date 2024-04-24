/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 5: Ordenación

 * @file   heap_sort.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   20/03/2024
 * @brief  Declaración de la clase HeapSort
 */

#pragma once

#include "sort_method.h"
#include "sorting_algorithms.h"

/**
 * @brief Clase abstracta HeapSort: tipo de dato para representar la ordenación por el mecanismo HeapSort
 */
template <class Key>
class HeapSort : public SortMethod<Key> {
 public:
  //-------------CONSTRUCTOR-------------
  HeapSort(staticSequence<Key>, unsigned, bool);

  //---------------------MÉTODOS---------------------
  /// Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación HeapSort.
  virtual void Sort() override;
};

/**
 * @brief Constructor de la clase HeapSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: valor booleano para activar o desactivar el modo traza.
 */
template <class Key>
HeapSort<Key>::HeapSort(staticSequence<Key> sequence, unsigned size, bool trace) : SortMethod<Key>(sequence, size, trace) {}

/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación HeapSort.
 */
template <class Key>
void HeapSort<Key>::Sort() { heapSort<Key>(this->sequence_, this->size_, this->trace_); }