/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 7: Árbol AVL

 * @file   ABB.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   15/04/2024
 * @brief  Declaración de la clase ABB (Árbol Binario de Búsqueda)
 */

#pragma once

#include "AB.h"

/**
 * @brief Clase ABB: tipo de dato para representar un árbol binario de búsqueda.
 */
template <class Key>
class ABB : public AB<Key> {
 public:
  //-----CONSTRUCTOR (POR DEFECTO)-----
  ABB() : AB<Key>() {}

  //----------------MÉTODOS----------------
  /// Método para insertar un nodo en el árbol
  virtual bool insert(const Key&) override;

  /// Método para buscar un nodo en el árbol
  virtual bool search(const Key&) const override;
};

/**
 * @brief Método para insertar un nodo en el árbol
 * @param[in] key: referencia (constante) de la clave a insertar
 * @return Devuelve true si el nodo ha sido insertado correctamente, false en caso contrario
 */
template <class Key>
bool ABB<Key>::insert(const Key& key) {
  // Si el árbol está vacío, insertamos el nodo como raíz (con sus respectivos hijos nulos)
  if (AB<Key>::root_ == nullptr) {
    AB<Key>::root_ = new nodoB<Key>(nullptr, nullptr, key);
    return true;
  }

  // En caso contrario, se busca la posición adecuada para insertar el nodo...
  nodoB<Key>* actual_node = AB<Key>::root_;
  nodoB<Key>* parent_node = nullptr;

  // Mientras que no se llegue a un nodo hoja...
  while (actual_node != nullptr) {
    // Definimos el nodo actual como el padre y seguimos buscando
    parent_node = actual_node;

    // Si la clave es menor que la del nodo actual, se busca en el subárbol izquierdo
    if (key < actual_node->getData()) { actual_node = actual_node->getLeft(); }
    // Si la clave es mayor que la del nodo actual, se busca en el subárbol derecho
    else if (key > actual_node->getData()) { actual_node = actual_node->getRight(); }
    // Si la clave ya existe en el árbol, se devuelve false
    else { return false; }
  }

  // Si la clave es menor que la del padre, se inserta en el subárbol izquierdo
  if (key < parent_node->getData()) { parent_node->getLeft() = new nodoB<Key>(nullptr, nullptr, key); }
  // Si la clave es mayor que la del padre, se inserta en el subárbol derecho
  else { parent_node->getRight() = new nodoB<Key>(nullptr, nullptr, key); }

  return true;
}

/**
 * @brief Método para buscar un nodo en el árbol binario de búsqueda
 * @param[in] key: referencia (constante) de la clave a buscar
 * @return Devuelve true si el nodo se encuentra en el árbol, false en caso contrario
 */
template <class Key>
bool ABB<Key>::search(const Key& key) const {
  // Si el árbol está vacío, se devuelve false
  if (AB<Key>::root_ == nullptr) { return false; }

  // En caso contrario, se busca la clave en el árbol...
  nodoB<Key>* actual_node = AB<Key>::root_;

  // Mientras que no se llegue a un nodo hoja...
  while (actual_node != nullptr) {
    // Si la clave es igual a la del nodo actual, se devuelve true
    if (key == actual_node->getData()) { return true; }
    // Si la clave es menor que la del nodo actual, se busca en el subárbol izquierdo
    if (key < actual_node->getData()) { actual_node = actual_node->getLeft(); }
    // Si la clave es mayor que la del nodo actual, se busca en el subárbol derecho
    else if (key > actual_node->getData()) { actual_node = actual_node->getRight(); }
  }

  // Si no se ha encontrado la clave, se devuelve false
  return false;
}
