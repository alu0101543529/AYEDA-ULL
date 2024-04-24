/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 6: TAD Árbol

 * @file   AB.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   08/04/2024
 * @brief  Declaración de la clase abstracta AB (Árbol Binario)
 */

#pragma once

#include <iostream>
#include <queue>
#include <stack>

#include "../nodo/nodoB.h"

template <class Key>
struct NodeLevel {
  NodeLevel(nodoB<Key>* node, int level) : node_(node), level_(level) {}
  nodoB<Key>* node_;
  int level_;
};

/**
 * @brief Clase AB: tipo de dato para representar un árbol binario.
 */
template <class Key>
class AB {
 public:
  //-----CONSTRUCTOR (POR DEFECTO)-----
  AB() : root_(nullptr) {}

  //----------------MÉTODOS----------------
  /// Método polimórfico para insertar un nodo en el árbol
  virtual bool insert(const Key&) = 0;

  /// Método polimórfico para buscar un nodo en el árbol
  virtual bool search(const Key&) const = 0;

  /// Método para realizar un recorrido en inorden del árbol
  void inorder() const;

  /// Sobrecarga del operador de inserción del flujo de entrada (<<) usando un recorrido por niveles
  template <class Keyy>
  friend std::ostream& operator<<(std::ostream&, const AB<Keyy>*);

 protected:
  //----ATRIBUTO----
  /// root_: puntero a un nodo de tipo Key que representa la raíz del árbol.
  nodoB<Key>* root_;

 private:
  ///Método para realizar el recorrido en inorden recursivo del árbol (método auxiliar de inorder())
  void inorder_(nodoB<Key>*) const;
};

/**
 * @brief Método para realizar el recorrido en inorden recursivo del árbol (método auxiliar de inorder())
 * @param[in] node: puntero al nodo actual
 */
template <class Key>
void AB<Key>::inorder_(nodoB<Key>* node) const {
  // Si el nodo actual no es nulo...
  if (node != nullptr) {
    // Se recorre el árbol hacia la izquierda
    inorder_(node->getLeft());
    // Se imprime el valor del nodo actual
    std::cout << node->getData() << " ";
    // Se recorre el árbol hacia la derecha
    inorder_(node->getRight());
  }
}

/**
 * @brief Método para realizar un recorrido en inorden del árbol
 */
template <class Key>
void AB<Key>::inorder() const {
  // Si el árbol está vacío, se imprime un mensaje de error.
  if (root_ == nullptr) {
    std::cerr << "El árbol está vacío." << std::endl;
    return;
  }

  // En caso de que contenga nodos, se realiza un recorrido en inorden.
  inorder_(root_);
  std::cout << std::endl;
}

template <class Key>
std::ostream& operator<<(std::ostream& os, const AB<Key>* tree) {
  // En caso de que contenga nodos, se realiza un recorrido por niveles, usando una cola de pares para almacenar los nodos, junto con su nivel.
  std::queue<NodeLevel<Key>> queue;
  queue.push(NodeLevel(tree->root_, 0));
  int actual_level = -1;

  // Mientras la cola no esté vacía...
  while (!queue.empty()) {
    // Se extrae un nodo de la cola y se imprime su valor.
    const auto& node = queue.front();
    queue.pop();

    // Si se cambia de nivel, se cambia el nivel actual y se imprime un salto de línea.
    if (node.level_ != actual_level) {
      actual_level = node.level_;
      os << std::endl;
      os << "Nivel " << actual_level << ": ";
    }

    // Si el nodo es nulo, se imprime un vacío, y se continúa con el siguiente nodo.
    if (node.node_ == nullptr) {
      os << "[.]";
      continue;
    }

    os << "[" << node.node_->getData() << "]";

    // Se añaden los hijos del nodo a la cola (si existen) empezando por el hijo izquierdo y siguiendo por el derecho.
    queue.push(NodeLevel<Key>(node.node_->getLeft(), (node.level_ + 1)));
    queue.push(NodeLevel<Key>(node.node_->getRight(), (node.level_ + 1)));
  }

  os << std::endl;

  return os;
}