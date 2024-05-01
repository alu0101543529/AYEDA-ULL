/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 7: Árbol AVL

 * @file   AVL.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   15/04/2024
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
  virtual bool insert(const Key&, bool) override;

  /// Método para buscar un nodo en el árbol
  virtual bool search(const Key&) const override;

 private:
  //--------------------MÉTODOS AVL--------------------
  /// Método para insertar un nodo AVL en el árbol, haciendo un rebalanceo si es necesario
  bool InsertAVL(nodoAVL<Key>*&, nodoAVL<Key>*, bool&, bool);

  /// Método de rebalanceo del árbol tras insertar un nodo en la rama izquierda
  void ReBalanceLeft (nodoAVL<Key>*&, bool&, bool);
  /// Método de rebalanceo del árbol tras insertar un nodo en la rama derecha
  void ReBalanceRight (nodoAVL<Key>*&, bool&, bool);

  /// Método de rotación izquierda-izquierda del árbol
  void rotateLeftLeft(nodoAVL<Key>*&, bool);
  /// Método de rotación derecha-derecha del árbol
  void rotateRightRight(nodoAVL<Key>*&, bool);
  /// Método de rotación izquierda-derecha del árbol
  void rotateLeftRight(nodoAVL<Key>*&, bool);
  /// Método de rotación derecha-izquierda del árbol
  void rotateRightLeft(nodoAVL<Key>*&, bool);
};

/**
 * @brief Método para insertar un nodo en el árbol
 * @param[in] key: referencia (constante) de la clave a insertar
 * @return Devuelve true si el nodo ha sido insertado correctamente, false en caso contrario
 */
template <class Key>
bool AVL<Key>::insert(const Key& key, bool trace) {
  nodoAVL<Key>* new_node = new nodoAVL<Key>(key);
  bool grow = false;
  if (InsertAVL(reinterpret_cast<nodoAVL<Key>*&>(AB<Key>::root_), new_node, grow, trace)) { return true; }
  return false;
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
 * @brief Método para insertar un nodo AVL en el árbol, haciendo un rebalanceo si es necesario
 * @param[in] root: referencia (constante) al nodo raíz del árbol
 * @param[in] new_node: puntero al nodo AVL que se va a insertar
 * @param[in] grow: referencia (constante) a un booleano que indica si el árbol ha crecido
 */
template <class Key>
bool AVL<Key>::InsertAVL(nodoAVL<Key>*& root, nodoAVL<Key>* new_node, bool& grow, bool trace) {
  // Si el árbol está vacío, se inserta el nodo en la raíz
  if (root == nullptr) {
    root = new_node;
    grow = true;
    return true;
  }

  // Si la clave es menor que la del nodo actual, se inserta en el subárbol izquierdo
  else if (new_node->getData() < root->getData()) {
    InsertAVL(root->getLeft(), new_node, grow, trace);
    // Si el árbol ha crecido, se rebalancea
    if (grow) { ReBalanceLeft(root, grow, trace); }

    return true;
  }

  // Si la clave es mayor que la del nodo actual, se inserta en el subárbol derecho
  else if (new_node->getData() > root->getData()) {
    InsertAVL(root->getRight(), new_node, grow, trace);
    // Si el árbol ha crecido, se rebalancea
    if (grow) { ReBalanceRight(root, grow, trace); }

    return true;
  }

  return false;
}

/**
 * @brief Método de rebalanceo del árbol tras insertar un nodo en la rama izquierda
 * @param[in] root_: referencia (constante) al nodo raíz del árbol
 * @param[in] grow: referencia (constante) a un booleano que indica si el árbol ha crecido
 */
template <class Key>
void AVL<Key>::ReBalanceLeft(nodoAVL<Key>*& root, bool& grow, bool trace) {
  switch (root->getBalance()) {
    // Si el factor de balanceo es -1, se establece a 0 y se indica que el árbol no ha crecido
    case -1: {
      root->setBalance(0);
      grow = false;
      break;
    }
    // Si el factor de balanceo es 0, se establece a 1
    case 0: {
      root->setBalance(1);
      break;
    }
    // Si el factor de balanceo es 1, se realiza una rotación
    case 1: {
      nodoAVL<Key>* aux_node = root->getLeft();

      // Si el factor de balanceo del hijo izquierdo es 1, se realiza una rotación izquierda-izquierda
      if (aux_node->getBalance() == 1) { rotateLeftLeft(root, trace); }
      // En otro caso, se realiza una rotación izquierda-derecha
      else { rotateLeftRight(root, trace);}

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
void AVL<Key>::ReBalanceRight(nodoAVL<Key>*& root, bool& grow, bool trace) {  
  switch (root->getBalance()) {
    // Si el factor de balanceo es 1, se establece a 0 y se indica que el árbol no ha crecido
    case 1: {
      root->setBalance(0);
      grow = false;
      break;
    }
    // Si el factor de balanceo es 0, se establece a -1
    case 0: {
      root->setBalance(-1);
      break;
    }
    // Si el factor de balanceo es -1, se realiza una rotación
    case -1: {
      nodoAVL<Key>* aux_node = root->getRight();

      // Si el factor de balanceo del hijo derecho es -1, se realiza una rotación derecha-derecha
      if (aux_node->getBalance() == -1) { rotateRightRight(root, trace); }
      // En otro caso, se realiza una rotación derecha-izquierda
      else { rotateRightLeft(root, trace); }

      grow = false;
      break;
    }
  }
}

/**
 * @brief Método de rotación izquierda-izquierda del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateLeftLeft(nodoAVL<Key>*& node, bool trace) {
  if (trace) { std::cout << "Realizando una rotación izquierda-izquierda desde el nodo " << node << "..." << std::endl; }

  nodoAVL<Key>* aux_node = node->getLeft();
  node->setLeft(aux_node->getRight());
  aux_node->setRight(node);

  // Actualizamos los factores de balanceo
  if (aux_node->getBalance() == 1) {
    node->setBalance(0);
    aux_node->setBalance(0);
  } 
  else {
    node->setBalance(1);
    aux_node->setBalance(-1);
  }

  node = aux_node;
}

/**
 * @brief Método de rotación derecha-derecha del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateRightRight(nodoAVL<Key>*& node, bool trace) {
  if (trace) { std::cout << "Realizando una rotación derecha-derecha desde el nodo " << node << "..." << std::endl; }

  nodoAVL<Key>* aux = node->getRight();
  node->setRight(aux->getLeft());
  aux->setLeft(node);

  // Actualizamos los factores de balanceo...
  if (aux->getBalance() == -1) {
    node->setBalance(0);
    aux->setBalance(0);
  } 
  else {
    node->setBalance(-1);
    aux->setBalance(1);
  }

  node = aux;
}

/**
 * @brief Método de rotación izquierda-derecha del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateLeftRight(nodoAVL<Key>*& node, bool trace) {
  if (trace) { std::cout << "Realizando una rotación izquierda-derecha desde el nodo " << node << "..." << std::endl; }

  nodoAVL<Key>* aux_node = node->getLeft();
  nodoAVL<Key>* aux_node2 = aux_node->getRight();
  node->setLeft(aux_node2->getRight());
  aux_node2->setRight(node);
  aux_node->setRight(aux_node2->getLeft());
  aux_node2->setLeft(aux_node);

  // Actualizamos los factores de balanceo...
  if (aux_node2->getBalance() == -1) { aux_node->setBalance(1); }
  else { aux_node->setBalance(0); }

  if (aux_node2->getBalance() == 1) { node->setBalance(-1); }
  else { node->setBalance(0); }

  aux_node2->setBalance(0);
  node = aux_node2;
}

/**
 * @brief Método de rotación derecha-izquierda del árbol
 * @param[in] node: puntero al nodo que se va a rotar
 */
template <class Key>
void AVL<Key>::rotateRightLeft(nodoAVL<Key>*& node, bool trace) {
  if (trace) { std::cout << "Realizando una rotación derecha-izquierda desde el nodo " << node << "..." << std::endl; }

  nodoAVL<Key>* aux_node = node->getRight();
  nodoAVL<Key>* aux_node2 = aux_node->getLeft();
  node->setRight(aux_node2->getLeft());
  aux_node2->setLeft(node);
  aux_node->setLeft(aux_node2->getRight());
  aux_node2->setRight(aux_node);

  // Actualizamos los factores de balanceo...
  if (aux_node2->getBalance() == 1) { aux_node->setBalance(-1); }
  else { aux_node->setBalance(0); }

  if (aux_node2->getBalance() == -1) { node->setBalance(1); }
  else { node->setBalance(0); }

  aux_node2->setBalance(0);
  node = aux_node2;
}