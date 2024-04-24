/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 6: TAD Árbol

 * @file   nodoB.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   08/04/2024
 * @brief  Declaración de la clase NodoB
 */

#pragma once

/**
 * @brief Clase NodoB: tipo de dato que representa un nodo de un árbol binario.
 */
template <class Key>
class nodoB {
 public:
  //--------------CONSTRUCTOR (POR DEFECTO)--------------
  nodoB() : left_(nullptr), right_(nullptr), data_(-1) {}

  //---------------------------------CONSTRUCTOR (POR PARÁMETROS)---------------------------------
  nodoB(nodoB<Key>* left, nodoB<Key>* right, Key data) : left_(left), right_(right), data_(data) {}

  //--------------------GETTERS--------------------
  /// Método para obtener el valor del nodo
  Key getData() const { return data_; }

  /// Método para obtener el hijo izquierdo del nodo
  nodoB<Key>* getLeft() const { return left_; }
  nodoB<Key>*& getLeft() { return left_; }

  /// Método para obtener el hijo derecho del nodo
  nodoB<Key>* getRight() const { return right_; }
  nodoB<Key>*& getRight() { return right_; }

 protected:
  //----ATRIBUTOS----
  /// data_: valor de tipo Key que representa el dato que se almacena en el nodo.
  Key data_;
  /// left_: puntero a un nodo de tipo Key que representa el hijo izquierdo del nodo.
  nodoB<Key>* left_;
  /// right_: puntero a un nodo de tipo Key que representa el hijo derecho del nodo.
  nodoB<Key>* right_;
};