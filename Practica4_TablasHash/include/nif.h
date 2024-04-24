/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 4: Tabla Hash

 * @file   nif.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   07/03/2024
 * @brief  Declaración de la clase NIF
 */

#pragma once

#include <iostream>
#include <random>

class NIF {
 public:
  //---------------------CONSTRUCTOR-----------------------
  NIF() { srand(time(NULL)); number_ = rand() % 100000000; }
  
  //-----------------CONSTRUCTOR (PARAMETRIZADO)-------------------
  NIF(long number) { 
    if ((number < 10000000 || number > 99999999) && number != -1) {
      std::cerr << "Error: el número de NIF debe tener 8 dígitos" << std::endl;
      exit(1);
    }
    number_ = number; 
  }

  //-----------------------------MÉTODOS-----------------------------
  /// Operador de conversión a long
  operator long() const { return number_; }

  /// Sobrecarga del operador de igualdad (==)
  bool operator==(const NIF& nif) const { return number_ == nif.number_; }
  bool operator==(const int& number) const { return number == number_; }

  /// Sobrecarga del operador de módulo (%)
  unsigned operator%(const unsigned& otherNumber) const { return number_ % otherNumber; }

  /// Sobrecarga del operador de suma (+)
  unsigned operator+(const unsigned& otherNumber) const { return number_ + otherNumber; }

  /// Sobrecarga del operador de extracción del flujo de entrada (>>)
  friend std::istream& operator>>(std::istream& is, NIF& nif) {
    long number;
    is >> number;
    if ((number < 10000000 || number > 99999999) && number != -1) {
      std::cerr << "Error: el número de NIF debe tener 8 dígitos" << std::endl;
      exit(1);
    }
    nif.number_ = number;
    return is;
  }

 private:
  //---------ATRIBUTO---------
  /// number_: representa el número del NIF
  long number_;
};