/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 5: Ordenación

 * @file   shell_sort.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   20/03/2024
 * @brief  Declaración de la clase ShellSort
 */

#pragma once

#include "sort_method.h"
#include "sorting_algorithms.h"

/**
 * @brief Clase abstracta ShellSort: tipo de dato para representar la ordenación por el mecanismo ShellSort
 */
template <class Key>
class ShellSort : public SortMethod<Key> {
 public:
  //--------------CONSTRUCTOR--------------
  ShellSort(staticSequence<Key>, unsigned, bool);

  //--------------MÉTODO------------
  /// Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación ShellSort.
  virtual void Sort() override;
};

/**
 * @brief Constructor de la clase ShellSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] alpha: valor de la distancia entre los elementos a comparar.
 */
template <class Key>
ShellSort<Key>::ShellSort(staticSequence<Key> sequence, unsigned size, bool trace) : SortMethod<Key>(sequence, size, trace) {}

/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación ShellSort.
 */
template <class Key>
void ShellSort<Key>::Sort() { shellSort<Key>(this->sequence_, this->size_, this->trace_); }