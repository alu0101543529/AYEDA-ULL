/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 4: Tabla Hash

 * @file   hash_table.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   07/03/2024
 * @brief  Declaración de la clase HashTable
 */

#pragma once

#include <iostream>
#include <vector>

#include "sequence/sequence.h"
#include "dispersion_function/dispersion_function.h"
#include "exploration_function/exploration_function.h"

//----------------------------------TABLA ESTÁTICA----------------------------------
/**
 * @brief Clase HashTable: tipo de dato para representar una Tabla Hash
 */
template <class Key, class Container = staticSequence<Key>>
class HashTable {
 public:
  //----------------------------------CONSTRUCTOR----------------------------------
  HashTable(unsigned, DispersionFunction<Key>*, ExplorationFunction<Key>*, unsigned);

  //--------MÉTODOS--------
  /// Método para buscar un elemento en la tabla
  bool search(const Key&);

  /// Método para insertar un elemento en la tabla
  bool insert(const Key&);

  /// Método para imprimir la Tabla Hash
  std::ostream& print(std::ostream&) const;

 private:
  //---------ATRIBUTOS---------
  /// table_: representa el vector de secuencias que forman la Tabla Hash
  std::vector<Container*> table_;
  /// tableSize_: representa el tamaño de la Tabla Hash
  unsigned tableSize_;
  /// fd_: representa la función de dispersión
  DispersionFunction<Key>* fd_;
  /// fe_: representa la función de exploración
  ExplorationFunction<Key>* fe_;
};


/**
 * @brief Constructor de la Tabla Hash
 * @param[in] tableSize: tamaño de la tabla
 * @param[in] dispersionFunction: referencia a la función de dispersión
 * @param[in] explorationFunction: referencia a la función de exploración
 * @param[in] blockSize: tamaño del bloque (si no se especifica, se crean vacíos)
 */
template <class Key, class Container>
HashTable<Key,Container>::HashTable(unsigned tableSize, 
                                    DispersionFunction<Key>* dispersionFunction, 
                                    ExplorationFunction<Key>* explorationFunction, 
                                    unsigned blockSize) {
  tableSize_ = tableSize;
  fd_ = dispersionFunction;
  fe_ = explorationFunction;
  table_.resize(tableSize_);

  // Para cada posición de la tabla se crea una secuencia.
  for (int i = 0; i < tableSize_; i++) { table_[i] = new Container(blockSize); }
}

/**
 * @brief Método para buscar un elemento en la tabla
 * @param[in] key: referencia (constante) de la clave a buscar
 * @return Devuelve 'true' si se encuentra, en caso contrario 'false'
 */
template <class Key, class Container>
bool HashTable<Key,Container>::search(const Key& key) {
  unsigned index = fd_->operator()(key);
  bool wasFound = false;
  unsigned oldIndex = index;
  int iterator = 0;
  
  // Mientras no se encuentre el elemento y la secuencia no esté llena se sigue buscando.
  do {
    wasFound = (table_[index]->search(key));
    oldIndex = index;
    index = fe_->operator()(key, iterator++) % tableSize_;
  } while ((!(wasFound) && (table_[oldIndex]->isFull())));
  
  // Cuando se termine el bucle, la variable wasFound contendrá el resultado de la búsqueda.
  return wasFound;
}

/**
 * @brief Método para insertar un elemento en la tabla
 * @param[in] key: referencia (constante) de la clave a insertar
 * @return Devuelve 'true' si se ha insertado, en caso contrario 'false'
 */
template <class Key, class Container>
bool HashTable<Key,Container>::insert(const Key& key) {
  unsigned index = fd_->operator()(key);
  bool wasInserted = false;
  unsigned oldIndex = index;
  int iterator = 0;

  // Mientras no se inserte el elemento y la secuencia no esté llena se sigue intentando insertar.
  do {
    wasInserted = (table_[index]->insert(key));
    oldIndex = index;
    index = fe_->operator()(key, iterator++) % tableSize_;
  } while ((!wasInserted) && (table_[oldIndex]->isFull()));
  
  // Cuando se termine el bucle, la variable wasInserted contendrá el resultado de la inserción.
  return wasInserted;
}

/**
 * @brief Método para imprimir la Tabla Hash
 * @param[in] os referencia al objeto ostream (flujo de datos de salida)
 * @return Devuelve la impresión de la tabla hash
 */
template <class Key, class Container>
std::ostream& HashTable<Key,Container>::print(std::ostream& os) const {
  for (int i = 0; i < tableSize_; i++) {
    os << "Secuencia -> " << i << ": " << table_[i]->print() << std::endl;
  }
  return os;
}

/**
 * @brief Sobrecarga del operador de inserción (<<) para la impresión de la Tabla Hash
 * @param[in] os referencia al objeto ostream (flujo de datos de salida)
 * @param[in] hashTable referencia (constante) a la tabla hash
 * @return Devuelve la impresión de la tabla hash
 */
template <class Key, class Container>
std::ostream& operator<<(std::ostream& os, const HashTable<Key,Container>& hashTable) {
  return hashTable.print(os);
}


//----------------------------------TABLA DINÁMICA----------------------------------
/**
 * @brief Clase HashTable: tipo de dato para representar una Tabla Hash
 */
template <class Key>
class HashTable<Key, dynamicSequence<Key>>{
 public:
  //----------------CONSTRUCTOR----------------
  HashTable(unsigned, DispersionFunction<Key>*);

  //--------MÉTODOS--------
  /// Método para buscar un elemento en la tabla
  bool search(const Key&);

  /// Método para insertar un elemento en la tabla
  bool insert(const Key&);

  /// Método para imprimir la Tabla Hash
  std::ostream& print(std::ostream&) const;

 private:
  //---------ATRIBUTOS---------
  /// table_: representa el vector de secuencias que forman la Tabla Hash
  std::vector<dynamicSequence<Key>*> table_;
  /// tableSize_: representa el tamaño de la Tabla Hash
  unsigned tableSize_;
  /// fd_: representa la función de dispersión
  DispersionFunction<Key>* fd_;
};

/**
 * @brief Constructor de la Tabla Hash
 * @param[in] tableSize: tamaño de la tabla
 * @param[in] dispersionFunction: referencia a la función de dispersión
 */
template <class Key>
HashTable<Key, dynamicSequence<Key>>::HashTable(unsigned tableSize, DispersionFunction<Key>* dispersionFunction) {
  tableSize_ = tableSize;
  table_.resize(tableSize);
  fd_ = dispersionFunction;
  for (int i = 0; i < tableSize_; i++) {
    table_[i] = new dynamicSequence<Key>(0);
  }
  
}

/**
 * @brief Método para buscar un elemento en la tabla
 * @param[in] key: referencia (constante) de la clave a buscar
 * @return Devuelve 'true' si se encuentra, en caso contrario 'false'
 */
template <class Key>
bool HashTable<Key, dynamicSequence<Key>>::search(const Key& key) {
  unsigned index = fd_->operator()(key);
  return table_[index]->search(key);
}

/**
 * @brief Método para insertar un elemento en la tabla
 * @param[in] key: referencia (constante) de la clave a insertar
 * @return Devuelve 'true' si se ha insertado, en caso contrario 'false'
 */
template <class Key>
bool HashTable<Key, dynamicSequence<Key>>::insert(const Key& key) {
  unsigned index = fd_->operator()(key);
  return table_[index]->insert(key);
}

/**
 * @brief Método para imprimir la Tabla Hash
 * @param[in] os referencia al objeto ostream (flujo de datos de salida)
 * @return Devuelve la impresión de la tabla hash
 */
template <class Key>
std::ostream& HashTable<Key, dynamicSequence<Key>>::print(std::ostream& os) const {
  for (int i = 0; i < tableSize_; i++) {
    os << "Secuencia -> " << i << ": " << table_[i]->print() << std::endl;
  }
  return os;  
}
