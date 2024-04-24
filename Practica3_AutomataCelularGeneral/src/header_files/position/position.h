/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   position.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Declaración de la clase Position
 */

#pragma once

typedef int Coor_t;

class Position {
 public:
  virtual Coor_t operator[] (unsigned int) const = 0;
};

#include "positionDim1.h"
#include "positionDim2.h"