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

  /// Método para insertar un nodo AVL en el árbol, haciendo un rebalanceo si es necesario
  bool InsertAVL(nodoB<Key>*&, nodoAVL<Key>*, bool&);

  //-------------MÉTODOS-------------
  /// Método de rotación izquierda-izquierda del árbol
  void rotateLeftLeft(nodoB<Key>*);
  /// Método de rotación derecha-derecha del árbol
  void rotateRightRight(nodoB<Key>*);
  /// Método de rotación izquierda-derecha del árbol
  void rotateLeftRight(nodoB<Key>*);
  /// Método de rotación derecha-izquierda del árbol
  void rotateRightLeft(nodoB<Key>*);

  /// Método de rebalanceo del árbol tras insertar un nodo en la rama izquierda
  void ReBalanceLeft (nodoB<Key>*&, bool&);
  /// Método de rebalanceo del árbol tras insertar un nodo en la rama derecha
  void ReBalanceRight (nodoB<Key>*&, bool&);
};

/**
 * @brief Método para insertar un nodo en el árbol
 * @param[in] key: referencia (constante) de la clave a insertar
 * @return Devuelve true si el nodo ha sido insertado correctamente, false en caso contrario
 */
template <class Key>
bool AVL<Key>::insert(const Key& key) {
  nodoAVL<Key>* new_node = new nodoAVL<Key>(key);
  bool grow = false;
  if (InsertAVL(AB<Key>::root_, new_node, grow)) { return true; }
  return false;
}

/**
 * @brief Método para insertar un nodo AVL en el árbol, haciendo un rebalanceo si es necesario
 * @param[in] root: referencia (constante) al nodo raíz del árbol
 * @param[in] new_node: puntero al nodo AVL que se va a insertar
 * @param[in] grow: referencia (constante) a un booleano que indica si el árbol ha crecido
 */
template <class Key>
bool AVL<Key>::InsertAVL(nodoB<Key>*& root, nodoAVL<Key>* new_node, bool& grow) {
  // Si el árbol está vacío, se inserta el nodo en la raíz
  if (root == nullptr) {
    root = new_node;
    grow = true;
  }
  // Si la clave ya existe en el árbol, se devuelve false
  if (new_node->getData() == root->getData()) { return false; }

  // Si la clave es menor que la del nodo actual, se inserta en el subárbol izquierdo
  else if (new_node->getData() < root->getData()) {
    InsertAVL(root->getLeft(), new_node, grow);
    // Si el árbol ha crecido, se rebalancea
    if (grow) { ReBalanceLeft(root, grow); }
  }

  // Si la clave es mayor que la del nodo actual, se inserta en el subárbol derecho
  else if (new_node->getData() > root->getData()) {
    InsertAVL(root->getRight(), new_node, grow);
    // Si el árbol ha crecido, se rebalancea
    if (grow) { ReBalanceRight(root, grow); }
  }

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

/**
 * @brief Método de rotación izquierda-izquierda del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateLeftLeft(nodoB<Key>* node_) {
  std::cout << "Rotación izquierda-izquierda" << std::endl;
  nodoB<Key>* aux = node_->getLeft();
  node_->getLeft() = aux->getRight();
  aux->getRight() = node_;

  nodoAVL<Key>* node = reinterpret_cast<nodoAVL<Key>*>(node_);

  // Actualizamos los factores de balanceo
  if (node->getBalance() == 1) {
    node->setBalance(0);
    nodoAVL<Key>* left_node = reinterpret_cast<nodoAVL<Key>*>(node_->getLeft());
    std::cout << "left_node: " << left_node->getBalance() << std::endl;
    left_node->setBalance(0);
  } 
  else {
    node->setBalance(1);
    nodoAVL<Key>* left_node = reinterpret_cast<nodoAVL<Key>*>(node_->getLeft());
    left_node->setBalance(-1);
  }

  node_ = aux;
}

/**
 * @brief Método de rotación derecha-derecha del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateRightRight(nodoB<Key>* node_) {
  std::cout << "Rotación derecha-derecha" << std::endl;
  nodoB<Key>* aux = node_->getRight();
  node_->getRight() = aux->getLeft();
  aux->getLeft() = node_;

  nodoAVL<Key>* node = reinterpret_cast<nodoAVL<Key>*>(node_);

  // Actualizamos los factores de balanceo...
  if (node->getBalance() == -1) {
    node->setBalance(0);
    nodoAVL<Key>* right_node = reinterpret_cast<nodoAVL<Key>*>(node_->getRight());
    right_node->setBalance(0);
  } 
  else {
    node->setBalance(-1);
    nodoAVL<Key>* right_node = reinterpret_cast<nodoAVL<Key>*>(node_->getRight());
    right_node->setBalance(1);
  }

  node_ = aux;
}

/**
 * @brief Método de rotación izquierda-derecha del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateLeftRight(nodoB<Key>* node) {
  std::cout << "Rotación izquierda-derecha" << std::endl;
  rotateRightRight(node->getLeft());
  rotateLeftLeft(node);
}

/**
 * @brief Método de rotación derecha-izquierda del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateRightLeft(nodoB<Key>* node) {
  std::cout << "Rotación derecha-izquierda" << std::endl;
  rotateLeftLeft(node->getRight());
  rotateRightRight(node);
}

/**
 * @brief Método de rebalanceo del árbol tras insertar un nodo en la rama izquierda
 * @param[in] root_: referencia (constante) al nodo raíz del árbol
 * @param[in] grow: referencia (constante) a un booleano que indica si el árbol ha crecido
 */
template <class Key>
void AVL<Key>::ReBalanceLeft(nodoB<Key>*& root_, bool& grow) {
  std::cout << "Rebalanceo izquierda" << std::endl;
  nodoAVL<Key>* rootAVL = reinterpret_cast<nodoAVL<Key>*>(root_);
  switch (rootAVL->getBalance()) {
    case -1: {
      rootAVL->setBalance(0);
      grow = false;
      break;
    }
    case 0: {
      rootAVL->setBalance(1);
      break;
    }
    case 1: {
      nodoAVL<Key>* left_root = reinterpret_cast<nodoAVL<Key>*>(root_->getLeft());
      if (left_root->getBalance() == 1) { rotateLeftLeft(rootAVL); }
      else { rotateLeftRight(rootAVL);}
      grow = false;
      break;
    }
  }
}

/**
 * @brief Método de rebalanceo del árbol tras insertar un nodo en la rama derecha
 * @param[in] root_: referencia (constante) al nodo raíz del árbol
 * @param[in] grow: referencia (constante) a un booleano que indica si el árbol ha crecido
 */
template <class Key>
void AVL<Key>::ReBalanceRight(nodoB<Key>*& root_, bool& grow) {
  nodoAVL<Key>* rootAVL = reinterpret_cast<nodoAVL<Key>*>(root_);
  switch (rootAVL->getBalance()) {
    case -1: {
      nodoAVL<Key>* right_root = reinterpret_cast<nodoAVL<Key>*>(root_->getRight());
      if (right_root->getBalance() == -1) { rotateRightRight(rootAVL); } 
      else { rotateRightLeft(rootAVL); }
      grow = false;
      break;
    }
    case 0: {
      rootAVL->setBalance(-1);
      break;
    }
    case 1: {
      rootAVL->setBalance(0);
      grow = false;
      break;
    }
  }
}