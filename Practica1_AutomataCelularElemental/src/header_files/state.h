/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 1: Autómata Celular Elemental

 * @file   state.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2024
 * @brief  Declaración de la clase State
 */

#pragma once

/**
 * @brief Clase State: tipo de dato para representar el estado de las células.
 */
class State {
 public:
  State() { state_ = 0; }
  //-------CONSTRUCTOR (PARAMETRIZADO)-------
  State(const int& state) { state_ = state; }

  //---------------GETTER---------------
  /// Getter para obtener el atributo "state_".
  int getState() const { return state_; }

  //---------------SETTER---------------
  /// Setter para establecer el atributo "state_" que se recibe por parámetros.
  void setState(const int& new_state) { state_ = new_state; }

  //---------------------------SOBRECARGA DE OPERADORES ARITMÉTICOS---------------------------
  // Sobrecarga del operador de suma (+) para la clase State
  State operator+(const State& state) const { return (State(getState() + state.getState())); }

  // Sobrecarga del operador de producto (*) para la clase State
  State operator*(const State& state) const { return (State(getState() * state.getState())); }

  // Sobrecarga del operador de módulo (%) para la clase State
  State operator%(const int& state) const { return (State(getState() % state)); }

 private:
  //-------ATRIBUTO-------
  /// state_: representa el estado de la célula en la generación que se encuentra.
  int state_;
};
