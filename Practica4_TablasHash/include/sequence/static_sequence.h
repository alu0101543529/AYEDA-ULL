/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 4: Tabla Hash

 * @file   static_sequence.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   07/03/2024
 * @brief  Declaración de la clase staticSequence
 */

#pragma once

#include <vector>

#include "sequence.h"

/**
 * @brief Clase staticSequence: tipo de dato para representar una secuencia estática, es decir que los bloques no cambian de tamaño en tiempo de ejecución.
 */
template <class Key>
class staticSequence : public Sequence<Key> {
 public:
  //------CONSTRUCTOR------
  staticSequence(unsigned);

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
  //------ATRIBUTOS------
  /// table_: representa el vector de elementos que forman la secuencia
  std::vector<Key> table_;
  /// blockSize_: representa el tamaño del bloque
  unsigned blockSize_;
  /// blockElementsUsed_: representa el número de elementos usados en el bloque (para saber si está llena)
  unsigned blockElementsUsed_;
};

/**
 * @brief Constructor de la secuencia estática
 * @param[in] blockSize: tamaño del bloque
 */
template <class Key>
staticSequence<Key>::staticSequence(unsigned blockSize) {
  blockSize_ = blockSize;
  blockElementsUsed_ = 0;
  table_.resize(blockSize_, -1);  // Inicializamos el vector con valores -1 para saber si está vacío o no.
}

/**
 * @brief Método para buscar un elemento en la secuencia
 * @param[in] key: referencia (constante) de la clave a buscar
 * @return Devuelve true si el elemento se encuentra en la secuencia, false en caso contrario
 */
template <class Key>
bool staticSequence<Key>::search (const Key& key) const {
  for (const Key &element : table_) {
    if (element == key) { return true; }
  }
  return false;
}


/**
 * @brief Método para insertar un elemento en la secuencia
 * @param[in] key: referencia (constante) de la clave a insertar
 * @return Devuelve true si el elemento se ha insertado correctamente, false en caso contrario
 */
template <class Key> 
bool staticSequence<Key>::insert (const Key& key) {
  // TENER CUIDADO PORQUE SI ESTAMOS INICIALIZANDO EL VECTOR CON VALORES KEY, NO SABEMOS CUALES SON "VACIOS"
  // Si la secuencia está llena o ya ese valor ha sido insertado, no podemos insertar ese elemento.
  if (isFull() || search(key)) { return false; } 
  for (int i = 0; i < blockSize_; i++) {
    if (table_[i] == Key(-1)) {
      table_[i] = key;      // Si encontramos un hueco vacío, insertamos el elemento.
      blockElementsUsed_++; // Si hemos conseguido insertarlo porque existe un hueco vacío, incrementamos en uno el valor de los elementos usados.
      return true; 
    }
  }
  return false;
}

/**
 * @brief Método para saber si la secuencia está llena
 * @return Devuelve true si la secuencia está llena, false en caso contrario
 */
template <class Key>
bool staticSequence<Key>::isFull () const {
  // Si el número de elementos usados es igual al tamaño del bloque, la secuencia está llena.
  if (blockElementsUsed_ == blockSize_) { return true; }
  return false;
}

/**
 * @brief Método para imprimir la secuencia
 * @return Devuelve la impresión de la secuencia
 */
template <class Key>
std::string staticSequence<Key>::print() const {
  std::string result = "";
  
  result += "[";
  for (int i = 0; i < table_.size(); i++) {
    if (i < (table_.size() - 1)) {
      if (table_[i] == Key(-1)) { result += "ø | "; }
      else { result += std::to_string(table_[i]) + " | "; }
    }
    else {
      if (table_[i] == Key(-1)) { result += "ø"; }
      else { result += std::to_string(table_[i]); }
    }
  }
  result += "]";
  
  return result;
}