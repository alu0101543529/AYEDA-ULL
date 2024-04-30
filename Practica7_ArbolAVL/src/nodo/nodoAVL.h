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
  //-------CONSTRUCTOR (POR DEFECTO)-------
  nodoAVL() : nodoB<Key>(), balance_(0) {}

  //-----------------------------------------------CONSTRUCTOR (POR PARÁMETROS)-----------------------------------------------
  nodoAVL(nodoAVL<Key>* left, nodoAVL<Key>* right, Key data, int balance) : nodoB<Key>(left, right, data), balance_(balance) {}
  nodoAVL(Key data) : nodoB<Key>(data), balance_(0) {}

  //------------------GETTER------------------
  /// Método para obtener el factor de balanceo del nodo
  int getBalance() const { return balance_; }
  void setBalance(int balance) { balance_ = balance; }

  //---------------------------MÉTODO I/O---------------------------
  std::ostream& print(std::ostream& os) const override {
    os << "[" << nodoB<Key>::data_ << "]" << "(" << balance_ << ")";
    return os;
  }

 private:
  //--ATRIBUTO--
  /// balance_: valor entero que representa el factor de balanceo del nodo.
  int balance_;
};