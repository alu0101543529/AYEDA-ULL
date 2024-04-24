/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 5: Ordenación

 * @file   selection_sort.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   20/03/2024
 * @brief  Declaración de la clase SelectionSort
 */

#pragma once

#include "sort_method.h"
#include "sorting_algorithms.h"
/**
 * @brief Clase abstracta SelectionSort: tipo de dato para representar la ordenación por el mecanismo SelectionSort
 */
template <class Key>
class SelectionSort : public SortMethod<Key> {
 public:
  //----------------CONSTRUCTOR----------------
  SelectionSort(staticSequence<Key>, unsigned, bool);
  
  //-------------MÉTODO-------------
  /// Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación SelectionSort.
  virtual void Sort() override;
};

/**
 * @brief Constructor de la clase SelectionSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: valor booleano para activar o desactivar el modo traza.
 */
template <class Key>  
SelectionSort<Key>::SelectionSort(staticSequence<Key> sequence, unsigned size, bool trace) : SortMethod<Key>(sequence, size, trace) {}

/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación SelectionSort.
 */
template <class Key>
void SelectionSort<Key>::Sort() { selectionSort<Key>(this->sequence_, this->size_, this->trace_); }