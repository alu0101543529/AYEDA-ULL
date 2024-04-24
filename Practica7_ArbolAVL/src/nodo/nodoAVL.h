/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 6: TAD Árbol

 * @file   nodoAVL.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   08/04/2024
 * @brief  Declaración de la clase NodoAVL
 */

#pragma once

/**
 * @brief Clase NodoAVL: tipo de dato que representa un nodo de un árbol Adelson-Velskii y Landis.
 */
template <class Key>
class nodoAVL : public nodoB<Key> {
 public:
  //--------------CONSTRUCTOR (POR DEFECTO)--------------
  nodoAVL() : left_(nullptr), right_(nullptr), data_(-1), balance_(0) {}

  //---------------------------------CONSTRUCTOR (POR PARÁMETROS)---------------------------------
  nodoAVL(nodoAVL<Key>* left, nodoAVL<Key>* right, Key data, int balance) : left_(left), right_(right), data_(data), balance_(balance) {}

  //------------------GETTER------------------
  /// Método para obtener el factor de balanceo del nodo
  int getBalance() const { return balance_; }

  /// Método para obtener el hijo izquierdo del nodo
  nodoAVL<Key>* getLeft() const { return left_; }
  nodoAVL<Key>*& getLeft() { return left_; }

  /// Método para obtener el hijo derecho del nodo
  nodoAVL<Key>* getRight() const { return right_; }
  nodoAVL<Key>*& getRight() { return right_; }

 private:
  //----ATRIBUTOS----
  /// data_: valor de tipo Key que representa el dato que se almacena en el nodo.
  Key data_;
  /// balance_: valor entero que representa el factor de balanceo del nodo.
  int balance_;
  /// left_: puntero a un nodo de tipo Key que representa el hijo izquierdo del nodo.
  nodoAVL<Key>* left_;
  /// right_: puntero a un nodo de tipo Key que representa el hijo derecho del nodo.
  nodoAVL<Key>* right_;
};