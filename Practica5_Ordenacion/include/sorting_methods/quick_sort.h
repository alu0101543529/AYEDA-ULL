/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 5: Ordenación

 * @file   quick_sort.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   20/03/2024
 * @brief  Declaración de la clase QuickSort
 */

#pragma once

#include "sort_method.h"
#include "sorting_algorithms.h"

/**
 * @brief Clase abstracta QuickSort: tipo de dato para representar la ordenación por el mecanismo QuickSort
 */
template <class Key>
class QuickSort : public SortMethod<Key> {
 public:
  //--------------CONSTRUCTOR--------------
  QuickSort(staticSequence<Key>, unsigned, bool);

  //----------MÉTODO----------
  /// Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación QuickSort.
  virtual void Sort() override;
};

/**
 * @brief Constructor de la clase QuickSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: valor booleano para activar o desactivar el modo traza.
 */
template <class Key>
QuickSort<Key>::QuickSort(staticSequence<Key> sequence, unsigned size, bool trace) : SortMethod<Key>(sequence, size, trace) {}

/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación QuickSort.
 */
template <class Key>
void QuickSort<Key>::Sort() { quickSort(this->sequence_, 0, (this->size_ - 1), this->trace_); }