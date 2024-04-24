/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 6: TAD Árbol

 * @file   AVL.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   08/04/2024
 * @brief  Declaración de la clase AVL (Árbol Adelson-Velskii y Landis)
 */

#pragma once

#include "ABB.h"
#include "../nodo/nodoAVL.h"

template <class Key>
struct NodeLevelAVL {
  NodeLevelAVL(nodoAVL<Key>* node, int level) : node_(node), level_(level) {}
  nodoAVL<Key>* node_;
  int level_;
};

/**
 * @brief Clase AVL: tipo de dato para representar un árbol Adelson-Velskii y Landis.
 */
template <class Key>
class AVL : public ABB<Key> {
 public:
  //-----CONSTRUCTOR (POR DEFECTO)-----
  AVL() : ABB<Key>() {}

  //----------------MÉTODOS----------------
  /// Método para insertar un nodo en el árbol
  virtual bool insert(const Key&) override;

  /// Método para buscar un nodo en el árbol
  virtual bool search(const Key&) const override;

  //----------------MÉTODO I/O----------------
  /// Sobrecarga del operador de inserción del flujo de entrada (<<) usando un recorrido por niveles
  template <class Keyy>
  friend std::ostream& operator<<(std::ostream&, const AVL<Keyy>*);

 private:
  /// root_: puntero a un nodo de tipo Key que representa la raíz del árbol.
  nodoAVL<Key>* root_;

  //----------------MÉTODOS----------------
  /// Método de rotación izquierda-izquierda del árbol
  void rotateLeftLeft(nodoAVL<Key>*);
  /// Método de rotación derecha-derecha del árbol
  void rotateRightRight(nodoAVL<Key>*);
  /// Método de rotación izquierda-derecha del árbol
  void rotateLeftRight(nodoAVL<Key>*);
  /// Método de rotación derecha-izquierda del árbol
  void rotateRightLeft(nodoAVL<Key>*);
};

/**
 * @brief Método para insertar un nodo en el árbol
 * @param[in] key: referencia (constante) de la clave a insertar
 * @return Devuelve true si el nodo ha sido insertado correctamente, false en caso contrario
 */
template <class Key>
bool AVL<Key>::insert(const Key& key) {
  // Si el árbol está vacío, insertamos el nodo como raíz (con sus respectivos hijos nulos)
  if (root_ == nullptr) {
    root_ = new nodoAVL<Key>(nullptr, nullptr, key, 0);
    return true;
  }

  // En caso contrario, se busca la posición adecuada para insertar el nodo...
  nodoAVL<Key>* actual_node = root_;
  nodoAVL<Key>* parent_node = nullptr;

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
  if (key < parent_node->getData()) { parent_node->getLeft() = new nodoAVL<Key>(nullptr, nullptr, key, 0); }
  // Si la clave es mayor que la del padre, se inserta en el subárbol derecho
  else { parent_node->getRight() = new nodoAVL<Key>(nullptr, nullptr, key, 0); }

  return true;
}

/**
 * @brief Método para buscar un nodo en el árbol binario de búsqueda
 * @param[in] key: referencia (constante) de la clave a buscar
 * @return Devuelve true si el nodo se encuentra en el árbol, false en caso contrario
 */
template <class Key>
bool AVL<Key>::search(const Key& key) const {
  // Si el árbol está vacío, se devuelve false
  if (root_ == nullptr) { return false; }

  // En caso contrario, se busca la clave en el árbol...
  nodoAVL<Key>* actual_node = root_;

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

/**
 * @brief Método de rotación izquierda-izquierda del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateLeftLeft(nodoAVL<Key>* node) {
  nodoAVL<Key>* aux = node->getLeft();
  node->getLeft() = aux->getRight();
  aux->getRight() = node;

  // Actualizamos los factores de balanceo
  if (node->getBalance() == 1) {
    node->getBalance() = 0;
    node->getLeft()->getBalance() = 0;
  } else {
    node->getBalance() = 1;
    node->getLeft()->getBalance() = -1;
  }

  node = aux;
}

/**
 * @brief Método de rotación derecha-derecha del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateRightRight(nodoAVL<Key>* node) {
  nodoAVL<Key>* aux = node->getRight();
  node->getRight() = aux->getLeft();
  aux->getLeft() = node;

  // Actualizamos los factores de balanceo
  if (node->getBalance() == -1) {
    node->getBalance() = 0;
    node->getRight()->getBalance() = 0;
  } else {
    node->getBalance() = -1;
    node->getRight()->getBalance() = 1;
  }

  node = aux;
}

/**
 * @brief Método de rotación izquierda-derecha del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateLeftRight(nodoAVL<Key>* node) {
  rotateRightRight(node->getLeft());
  rotateLeftLeft(node);
}

/**
 * @brief Método de rotación derecha-izquierda del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateRightLeft(nodoAVL<Key>* node) {
  rotateLeftLeft(node->getRight());
  rotateRightRight(node);
}

/**
 * @brief Sobrecarga del operador de inserción del flujo de entrada (<<) usando un recorrido por niveles
 * @param[in] os: flujo de salida
 * @param[in] tree: puntero al árbol que se va a imprimir
 * @return Devuelve una referencia al flujo de salida
 */
template <class Key>
std::ostream& operator<<(std::ostream& os, const AVL<Key>* tree) {
  // En caso de que contenga nodos, se realiza un recorrido por niveles, usando una cola de pares para almacenar los nodos, junto con su nivel.
  std::queue<NodeLevelAVL<Key>> queue;
  queue.push(NodeLevelAVL(tree->root_, 0));
  int actual_level = -1;

  // Mientras la cola no esté vacía...
  while (!queue.empty()) {
    // Se extrae el nodo actual y su nivel
    NodeLevelAVL<Key> node = queue.front();
    queue.pop();

    // Si el nivel actual es distinto al anterior, se imprime un salto de línea
    if (node.level_ != actual_level) {
      actual_level = node.level_;
      os << std::endl;
      os << "Nivel " << actual_level << ": ";
    }

    // Si el nodo actual es nulo, se imprime un vacio, y se continúa con el siguiente nodo.
    if (node.node_ == nullptr) {
      os << "[.] ";
      continue;
    }

    os << "[" << node.node_->getData() << "] ";

    // Se añaden los hijos del nodo a la cola (si existen) empezando por el hijo izquierdo y siguiendo por el derecho.
    queue.push(NodeLevelAVL<Key>(node.node_->getLeft(), (node.level_ + 1)));
    queue.push(NodeLevelAVL<Key>(node.node_->getRight(), (node.level_ + 1)));
  }

  os << std::endl;

  return os;
}
