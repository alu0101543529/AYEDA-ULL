/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 7: Árbol AVL

 * @file   nodoAVL.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   15/04/2024
 * @brief  Declaración de la clase NodoAVL
 */

#pragma once

/**
 * @brief Clase NodoAVL: tipo de dato que representa un nodo de un árbol Adelson-Velskii y Landis.
 */
template <class Key>
class nodoAVL : public nodoB<Key> {
 public:
  //-------CONSTRUCTOR (POR DEFECTO)-------
  nodoAVL() : nodoB<Key>(), balance_(0) {}

  //-----------------------------------------------CONSTRUCTOR (POR PARÁMETROS)-----------------------------------------------
  nodoAVL(nodoAVL<Key>* left, nodoAVL<Key>* right, Key data, int balance) : nodoB<Key>(left, right, data), balance_(balance) {}
  nodoAVL(Key data) : nodoB<Key>(data), balance_(0) {}

  //------------------------------------------GETTERS------------------------------------------
  /// Método para obtener el hijo izquierdo del nodo
  nodoAVL<Key>* getLeft() const { return reinterpret_cast<nodoAVL<Key>*>(nodoB<Key>::left_); }
  nodoAVL<Key>*& getLeft() { return reinterpret_cast<nodoAVL<Key>*&>(nodoB<Key>::left_); }

  /// Método para obtener el hijo derecho del nodo
  nodoAVL<Key>* getRight() const { return reinterpret_cast<nodoAVL<Key>*>(nodoB<Key>::right_); }
  nodoAVL<Key>*& getRight() { return reinterpret_cast<nodoAVL<Key>*&>(nodoB<Key>::right_); }

  /// Método para obtener el factor de balanceo del nodo
  int getBalance() const { return balance_; }

  //-----------------------------------------------------SETTERS-----------------------------------------------------
  /// Método para establecer el hijo izquierdo del nodo
  nodoAVL<Key>* setLeft(nodoAVL<Key>* left) { return reinterpret_cast<nodoAVL<Key>*>(nodoB<Key>::left_ = left); }

  /// Método para establecer el hijo derecho del nodo
  nodoAVL<Key>* setRight(nodoAVL<Key>* right) { return reinterpret_cast<nodoAVL<Key>*>(nodoB<Key>::right_ = right); }
  
  /// Método para establecer el factor de balanceo del nodo
  void setBalance(int balance) { balance_ = balance; }

  //---------------------------MÉTODO I/O---------------------------
  /// Método para imprimir el nodo AVL
  std::ostream& print(std::ostream& os) const override {
    os << "[" << nodoB<Key>::data_ << "]" << "(" << balance_ << ")";
    return os;
  }

 private:
  //--ATRIBUTO--
  /// balance_: valor entero que representa el factor de balanceo del nodo.
  int balance_;
};