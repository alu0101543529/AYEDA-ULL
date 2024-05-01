/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 7: Árbol AVL

 * @file   ABE.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   15/04/2024
 * @brief  Declaración de la clase ABE (Árbol Binario Equilibrado)
 */

#pragma once

#include "AB.h"

/**
 * @brief Clase ABE: tipo de dato para representar un árbol binario equilibrado.
 */
template <class Key>
class ABE : public AB<Key> {
 public:
  //-----CONSTRUCTOR (POR DEFECTO)-----
  ABE() : AB<Key>() {}

  //----------------MÉTODOS----------------
  /// Método para insertar un nodo en el árbol
  virtual bool insert(const Key&) override;

  /// Método para buscar un nodo en el árbol
  virtual bool search(const Key&) const override;

 private:
  /// Método para realizar un recorrido en preorden del árbol (método auxiliar de search())
  bool searchPreorder(nodoB<Key>*, const Key&) const;
};

/**
 * @brief Método para insertar un nodo en el árbol
 * @param[in] key: referencia (constante) de la clave a insertar
 * @return Devuelve true si el nodo ha sido insertado correctamente, false en caso contrario
 */
template <class Key>
bool ABE<Key>::insert(const Key& key) {
  // En caso de que la clave ya exista en el árbol, no se inserta
  if (search(key)) { return false; }

  // Si el árbol está vacío, insertamos el nodo como raíz
  if (AB<Key>::root_ == nullptr) {
    AB<Key>::root_ = new nodoB<Key>(nullptr, nullptr,key);
    return true;
  }

  // En caso contrario, se busca la posición adecuada para insertar el nodo, usando una cola para recorrer el árbol por niveles...
  std::queue<nodoB<Key>*> queue;
  queue.push(AB<Key>::root_);

  // Mientras que no se llegue a un nodo hoja...
  while (!queue.empty()) {
    // Se extrae un nodo de la cola, y se comprueba si tiene hijos libres
    nodoB<Key>* node = queue.front();
    queue.pop();

    // Si el nodo actual no tiene hijo izquierdo, se inserta el nodo en el árbol
    if (node->getLeft() == nullptr) {
      node->getLeft() = new nodoB<Key>(nullptr, nullptr,key);
      return true;
    }
    // Si el nodo actual no tiene hijo derecho, se inserta el nodo en el árbol
    else if (node->getRight() == nullptr) {
      node->getRight() = new nodoB<Key>(nullptr, nullptr,key);
      return true;
    }
    // Si el nodo actual tiene ambos hijos, se añaden a la cola para seguir buscando al siguiente nivel
    else {
      queue.push(node->getLeft());
      queue.push(node->getRight());
    }
  }

  // Si no se ha podido insertar el nodo en el árbol, se devuelve false
  return false;
}


/**
 * @brief Método para buscar un nodo en el árbol
 * @param[in] key: referencia (constante) de la clave a buscar
 * @return Devuelve true si el nodo se encuentra en el árbol, false en caso contrario
 */
template <class Key>
bool ABE<Key>::search(const Key& key) const {
  // Realizamos una búsqueda en preorden recursiva del árbol, para encontrar la clave, puesto que no sigue un orden específico
  return searchPreorder(AB<Key>::root_, key);
}

/**
 * @brief Método para realizar un recorrido en preorden del árbol (método auxiliar de search())
 * @param[in] node: puntero al nodo actual
 * @param[in] key: referencia (constante) de la clave a buscar
 */
template <class Key>
bool ABE<Key>::searchPreorder(nodoB<Key>* node, const Key& key) const {
  // Si el nodo actual es nulo, se devuelve false
  if (node == nullptr) { return false; }

  // Si la clave es igual a la del nodo actual, se devuelve true
  if (key == node->getData()) { return true; }

  // Se realizan llamadas en preorden del árbol, buscando la clave
  if (searchPreorder(node->getLeft(), key)) { return true; }
  if (searchPreorder(node->getRight(), key)) { return true; }

  // Si no se ha encontrado la clave, se devuelve false
  return false;
}