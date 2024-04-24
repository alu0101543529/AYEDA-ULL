/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 4: Tabla Hash

 * @file   dynamic_sequence.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   07/03/2024
 * @brief  Declaración de la clase dynamicSequence
 */

#pragma once

#include <list>

#include "sequence.h"

/**
 * @brief Clase dynamicSequence: tipo de dato para representar una secuencia dinámica, es decir que los bloques cambian de tamaño en tiempo de ejecución.
 */
template <class Key>
class dynamicSequence : public Sequence<Key> {
 public:
  //--CONSTRUCTOR--
  dynamicSequence(unsigned);

  //---------------MÉTODOS---------------
  /// Método para buscar un elemento en la secuencia
  virtual bool search (const Key&) const override;

  /// Método para insertar un elemento en la secuencia
  virtual bool insert (const Key&) override;
  
  /// Método para saber si la secuencia está llena
  virtual bool isFull() const override;
  
  /// Método para imprimir la secuencia
  virtual std::string print() const override;

 private:
  //------ATRIBUTO------
  /// table_: representa una lista de elementos que forman la secuencia
  std::list<Key> table_;

};

/**
 * @brief Constructor de la secuencia dinámica
 */
template <class Key>
dynamicSequence<Key>::dynamicSequence(unsigned blockSize) {}

/**
 * @brief Método para buscar un elemento en la secuencia
 * @param[in] key: referencia (constante) al elemento a buscar
 * @return Devuelve true si el elemento está en la secuencia, false en caso contrario
 */
template <class Key>
bool dynamicSequence<Key>::search (const Key& key) const {
  for (const Key &element : table_) {
    if (element == key) { return true; }
  }
  return false;
}

/**
 * @brief Método para insertar un elemento en la secuencia
 * @param[in] key: referencia (constante) al elemento a insertar
 * @return Devuelve true si el elemento se ha insertado correctamente, false en caso contrario
 */
template <class Key>
bool dynamicSequence<Key>::insert (const Key& key) {
  if (search(key)) { return false; } // Si el elemento ya está en la secuencia, no se inserta
  table_.push_back(key);
  return true;
}

/**
 * @brief Método para saber si la secuencia está llena
 * @return Devuelve false siempre, ya que la secuencia dinámica no tiene límite de elementos
 */
template <class Key>
bool dynamicSequence<Key>::isFull () const {
  return false;
}

/**
 * @brief Método para imprimir la secuencia
 * @return Devuelve la impresión de la secuencia
 */
template <class Key>
std::string dynamicSequence<Key>::print() const {
  std::string result = "";
  
  result += "[";
  auto it = table_.begin();
  while (it != table_.end()) {
    result += std::to_string(*it);
    ++it;
    if (it != table_.end()) { result += " | ";}
  }
  result += "]";

  return result;
}