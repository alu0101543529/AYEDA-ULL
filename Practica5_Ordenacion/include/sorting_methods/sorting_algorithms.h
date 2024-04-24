/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 5: Ordenación

 * @file   sorting_algorithms.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   20/03/2024
 * @brief  Definicón de los algoritmos de ordenación
 */

#pragma once

#include "sort_method.h"

/**
 * @brief Método auxiliar para intercambiar dos elementos.
 * @param[in] elemento_1: primer elemento a intercambiar.
 * @param[in] elemento_2: segundo elemento a intercambiar.
 */
template <class Key>
void Swap(Key& elemento_1, Key& elemento_2) {
  Key aux = elemento_1;
  elemento_1 = elemento_2;
  elemento_2 = aux;
}

///-----------------------------------HEAP SORT-----------------------------------
/**
 * @brief Método auxiliar para la ordenación HeapSort.
 * @param[in] father: índice del elemento a ordenar.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 */
template <class Key>
void Down(int father, staticSequence<Key>& sequence, unsigned size) {
  Position inxHeap = father;
  Position leftSon = ((2 * father) + 1);
  Position rightSon = ((2 * father) + 2);

  // Si el hijo izquierdo es mayor que el padre, actualizamos el valor máximo
  if ((leftSon < size) && (sequence[leftSon] > sequence[inxHeap])) { inxHeap = leftSon; }

  // Si el hijo derecho es mayor que el padre, actualizamos el valor máximo
  if ((rightSon < size) && (sequence[rightSon] > sequence[inxHeap])) { inxHeap = rightSon; }

  // Si el valor máximo no es el padre, intercambiamos los elementos y llamamos recursivamente al método
  if (inxHeap != father) {
    Swap(sequence[father], sequence[inxHeap]);
    Down(inxHeap, sequence, size);
  }
}

/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación HeapSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: booleano para activar el rastro de la secuencia.
 */
template <class Key>
void heapSort(staticSequence<Key>& sequence, unsigned size, bool trace) {
  // Construimos el montículo
  for (int i = ((size / 2) - 1); i >= 0; i--) { Down(i, sequence, size); }

  // Recorremos la secuencia de elementos
  for (int i = (size - 1); i > 0; i--) {
    // Intercambiamos los elementos y llamamos al método Down
    Swap(sequence[0], sequence[i]);
    Down(0, sequence, i);

    // Si se ha activado el rastro, mostramos la secuencia
    if (trace) { std::cout << sequence.print() << std::endl; }
  }
}

///-----------------------------------QUICK SORT-----------------------------------
/**
 * @brief Método auxiliar para la ordenación QuickSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] beginning: índice del primer elemento de la secuencia.
 * @param[in] end: índice del último elemento de la secuencia.
 */
template <class Key>
void quickSort(staticSequence<Key>& sequence, int beginning, int end, bool trace) {
  int i = beginning;
  int j = end;
  int pivotIndex = ((beginning + end) / 2);
  Key pivot = sequence[pivotIndex];

  // Mientras que el índice de la izquierda sea menor o igual que el de la derecha...
  while (i <= j) {
    while (sequence[i] < pivot) { i++; }
    while (sequence[j] > pivot) { j--; }

    // Si el índice de la izquierda es menor o igual que el de la derecha, intercambiamos los elementos y actualizamos los índices
    if (i <= j) {
      Swap(sequence[i], sequence[j]);
      i++;
      j--;
    }
  }

  // Si se ha activado el rastro, mostramos la secuencia
  if (trace) { std::cout << sequence.print() << std::endl; }

  // Llamamos recursivamente al método para ordenar la secuencia por la izquierda y por la derecha simultáneamente
  if (beginning < j) { quickSort(sequence, beginning, j); }
  if (i < end) { quickSort(sequence, i, end); }

}

/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación QuickSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: booleano para activar el rastro de la secuencia.
 */
template <class Key>
void quickSort(staticSequence<Key>& sequence, unsigned size, bool trace) { quickSort(sequence, 0, (size - 1), trace); }

///-----------------------------------SHELL SORT-----------------------------------
/**
 * @brief Método auxiliar para ordenar una secuencia de elementos mediante el algoritmo de ordenación ShellSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] alpha: valor de la distancia entre los elementos a comparar.
 */
template <class Key>
void AlphaSort(staticSequence<Key>& sequence, unsigned size, double alpha) {
  // Recorremos la secuencia de elementos
  for (int i = alpha; i < size; i++) {
    Key x = sequence[i];
    int j = i;

    // Mientras que el índice sea mayor o igual que alpha y el elemento en la posición j - alpha sea mayor que x...
    while ((j >= alpha) && (x < sequence[j - alpha])) {
      // Intercambiamos los elementos y actualizamos el índice
      sequence[j] = sequence[j - alpha];
      j = (j - alpha);
    }
    
    // Intercambiamos los elementos
    sequence[j] = x;
  }
}

/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación ShellSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: booleano para activar el rastro de la secuencia.
 */
template <class Key>
void shellSort(staticSequence<Key>& sequence, unsigned size, bool trace) {
  // Definimos el valor de alpha como el tamaño de la secuencia
  double alpha = size;

  // Mientras que alpha sea mayor que 1, dividimos alpha entre 2 y ordenamos la secuencia
  while (alpha > 1) {
    alpha = (alpha / 2);
    AlphaSort(sequence, size, alpha);
    
    // Si se ha activado el rastro, mostramos la secuencia
    if (trace) { std::cout << sequence.print() << std::endl; }
  }
}

///-----------------------------------SELECTION SORT-----------------------------------
/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación SelectionSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: booleano para activar el rastro de la secuencia.
 */
template <class Key>
void selectionSort(staticSequence<Key>& sequence, unsigned size, bool trace) {
  for (int i = 0; i < (size - 1); i++) {
    // Definimos el elemento mínimo como el primer elemento de la secuencia
    Position min = i;

    // Buscamos dentro de la secuencia si hay un elemento más pequeño que el previamente definido
    for (int j = (i + 1); j < size; j++) {
      if (sequence[j] < sequence[min]) { min = j; }
    }

    // Intercambiamos los elementos
    Swap(sequence[i], sequence[min]);

    // Si se ha activado el rastro, mostramos la secuencia
    if (trace) { std::cout << sequence.print() << std::endl; }
  }
}

///-----------------------------------RADIX SORT-----------------------------------
/**
 * @brief Método auxiliar para la ordenación RadixSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] exp: valor del dígito a comparar.
 */
template <class Key>
void countingSort(staticSequence<Key>& sequence, unsigned size, int exp) {
  // Definimos la secuencia de salida y un vector de conteo
  staticSequence<Key> output(size);
  std::vector<Key> count(10, 0);

  // Contamos la frecuencia de cada dígito
  for (int i = 0; i < size; i++) { count[(sequence[i] / exp) % 10]++; }

  // Calculamos la posición de cada dígito
  for (int i = 1; i < 10; i++) { count[i] += count[i - 1]; }

  // Construimos la secuencia de salida
  for (int i = (size - 1); i >= 0; i--) {
    output[count[(sequence[i] / exp) % 10] - 1] = sequence[i];
    count[(sequence[i] / exp) % 10]--;
  }

  // Copiamos la secuencia de salida en la secuencia original
  for (int i = 0; i < size; i++) { sequence[i] = output[i]; }
}

/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación RadixSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: booleano para activar el rastro de la secuencia.
 */
template <class Key>
void radixSort(staticSequence<Key>& sequence, unsigned size, bool trace) {
  // Definimos el valor máximo de la secuencia al inicial
  Key max = sequence[0];

  // Buscamos el valor máximo de la secuencia
  for (int i = 1; i < size; i++) {
    if (sequence[i] > max) { max = sequence[i]; }
  }

  // Aplicamos el método CountingSort para cada dígito
  for (int exp = 1; (max / exp) > 0; exp *= 10) {
    // Llamamos al método auxiliar para ordenar la secuencia
    countingSort(sequence, size, exp);

    // Si se ha activado el rastro, mostramos la secuencia
    if (trace) { std::cout << sequence.print() << std::endl; }  
  }
}