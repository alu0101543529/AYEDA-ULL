/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 2: Juego de la Vida

 * @file   lattice.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   14/02/2024
 * @brief  Implementación de la clase Lattice
 */
#include <cassert>
#include <fstream>

#include "header_files/cell.h"
#include "header_files/lattice.h"
#include "header_files/border_types/border.h"
#include "header_files/border_types/open.h"
#include "header_files/border_types/periodic.h"
#include "header_files/border_types/noborder.h"
#include "header_files/border_types/reflective.h"

/**
 * @brief Constructor del retículo.
 * @param[in] rows: entero que representa el número de filas que tendrá la matriz <=> retículo.
 * @param[in] cols: entero que representa el número de columnas que tendrá la matriz <=> retículo.
 * @param[in] type_border: cadena de caracteres que representa el tipo de frontera que tiene el retículo.
 */
Lattice::Lattice(int rows, int cols, std::string border_type, int temperature) {
  // Nos aseguramos de que el número de filas y columnas sea mayor que 0.
  assert (rows > 0 && cols > 0);
  rows_ = rows;
  cols_ = cols;

  // Definimos el tamaño que tendrá la matriz <=> retículo, y inicializamos todas las células.
  cells_.resize(rows_);
  for (int i = 0; i < rows_; i++) { cells_[i].resize(cols_, Cell()); }

  if(border_type == "open") {
    border_type_ = new Open(temperature);
  } else if (border_type == "periodic") {
    border_type_ = new Periodic();
  } else if (border_type == "noborder") {
    border_type_ = new NoBorder();
  } else if (border_type == "reflective") {
    border_type_ = new Reflective();
  } 
  else {
    std::cerr << "Error: Tipo de borde no válido." << std::endl;
    exit(EXIT_FAILURE);
  }

  // Inicializamos el retículo con la configuración inicial deseada por el usuario.
  InitialSetting();
}

/**
 * @brief Constructor del retículo mediante fichero.
 * @param[in] filename: referencia (constente) de la cadena de caracteres que representa el nombre del fichero que contiene el retículo.
 * @param[in] type_border: cadena de caracteres que representa el tipo de frontera que tiene el retículo.
 */
Lattice::Lattice(const std::string& filename, std::string border_type, int temperature) {
  // Definimos una variable como flujo de entrada de ficheros, pasandole como parámetros el fichero que deseamos abrir.
  std::ifstream input_file(filename);

  // Comprobamos si se ha abierto correctamente.
  if (!(input_file.is_open())) {
    std::cout << "Error: No se pudo abrir el fichero." << std::endl;
    exit(EXIT_FAILURE);
  }
  // En caso de que se haya abierto correctamente, mostramos un mensaje informativo.
  std::cout << "El fichero '" << filename << "' se ha cargado correctamente." << std::endl << std::endl;
  
  // Definimos una variable como la cadena de texto que se recogerá del archivo.
  std::string input_lattice;

  // Como las dos primeras líneas del fichero (si está en el formato correcto) serán el nº de filas y el nº de colunmas, las insertamos manualmente, para posteriormente definirlas.
  input_file >> rows_; 
  input_file >> cols_;

  // Definimos el tamaño que tendrá el vector que representa las filas, según el número leído del fichero.
  cells_.resize(rows_);
  // Para cada posición del vector de filas, es decir los que representan las columnas, definimos el tamaño que tendrán según el número leído del fichero.
  for (int j = 0; j < rows_; j++) { cells_[j].resize(cols_, Cell()); }
  
  // Definimos un bucle que recorrerá todas las líneas del fichero, y para cada línea, recorrerá todos los caracteres que contiene, definiendo su estado.
  char state;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      input_file >> state;
      cells_[i][j] = Cell(Position(i,j), State(state == '1' ? 1 : 0));
    }
  }

  // Cerramos el fichero una vez hemos terminado de leerlo.
  input_file.close();

  if (border_type == "open") {
    border_type_ = new Open(temperature);
  } else if (border_type == "periodic") {
    border_type_ = new Periodic();
  } else if (border_type == "noborder") {
    border_type_ = new NoBorder();
  } else if (border_type == "reflective") {
    border_type_ = new Reflective();
  }
  else {
    std::cerr << "Error: Tipo de borde no válido." << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Método que establece la configuración inicial del retículo.
 */
void Lattice::InitialSetting() {
  // Definimos el tamaño que tendrá la matriz <=> retículo, y inicializamos todas las células a un estado muerto.
  cells_.resize(rows_);
  for (int i = 0; i < rows_; i++) {
    cells_[i].resize(cols_, Cell());
    for (int j = 0; j < rows_; j++) {
      cells_[i][j] = Cell(Position(i, j), State(0));
    }
  }

  char choice;
  do {
    std::cout << "¿Desea insertar una célula viva? (S/N): ";
    std::cin >> choice;
    std::cout << std::endl;
    if ((choice == 's') || (choice == 'S')) {
      // Pedimos al usuario que inserte la fila y la columna de la célula viva, y nos aseguramos de que estén dentro de los límites del retículo.
      int row, col;
      std::cout << "Inserte la fila de la célula viva: ";
      std::cin >> row;
      assert (row >= 0 && row < rows_);
      std::cout << "Inserte la columna de la célula viva: ";
      std::cin >> col;
      assert (col >= 0 && col < cols_);

      // Insertamos la célula viva en la posición especificada por el usuario.
      cells_[row][col] = Cell(Position(row, col), State(1));
      std::cout << "La célula en la posición (" << row << "," << col << ") está ahora en estado viva." << std::endl;
    }
    std::cout << std::endl;
  } while ((choice != 'n') && (choice != 'N'));
}

/**
 * @brief Método que actualiza los estados de todas las células del retículo a su siguiente generación.
 */
void Lattice::nextGeneration() {
  // Primero hacemos un recorrido de todo el retículo calculando el siguiente estado que tendrán las células.
  for (int i = 0; i < getRows(); i++) {
    for (int j = 0; j < getCols(); j++) {
      cells_[i][j].NextState(*this);
    }
  }
  // Posteriormente, vamos actualizando las células a su siguiente estado previamente calculado
  for (int i = 0; i < getRows(); i++) {
    for (int j = 0; j < getCols(); j++) {
      cells_[i][j].updateState();
    }
  }
}

/**
 * @brief Método que devuelve la célula que ocupa la posición especificada por parámetros dentro del retículo.
 * @param[in] position: referencia (constante) a la posición de la célula que deseamos obtener.
 * @return Devuelve la célula que ocupa la posición especificada por parámetros dentro del retículo.
 */
const Cell Lattice::getCell(const Position& position) const {
  return (cells_[position.getPosition().first][position.getPosition().second]);
}

/**
 * @brief Método que calcula el número de células vivas (población) en el retículo en su generación actual.
 * @return Devuelve el número de células vivas (población).
 */
std::size_t Lattice::Population() const {
  std::size_t population = 0;
  for (int i = 0; i < getRows(); i++) {
    for (int j = 0; j < getCols(); j++) {
      if (getCell(Position(i, j)).getState().getState() == State(1).getState()) { population++; }
    }
  }
  return population;
}

/**
 * @brief Método para poder cargar el retículo desde un fichero.
 * @param[in] filename: referencia (constante) al nombre del fichero que se desea cargar.
 */
void Lattice::OpenFile(const std::string& filename) {
  // Definimos una variable como flujo de entrada de ficheros, pasandole como parámetros el fichero que deseamos abrir.
  std::ifstream input_file(filename);

  // Comprobamos si se ha abierto correctamente.
  if (!(input_file.is_open())) {
    std::cout << "Error: No se pudo abrir el fichero." << std::endl;
    exit(EXIT_FAILURE);
  }
  // En caso de que se haya abierto correctamente, mostramos un mensaje informativo.
  std::cout << "El fichero '" << filename << "' se ha cargado correctamente." << std::endl << std::endl;
  
  // Definimos una variable como la cadena de texto que se recogerá del archivo.
  std::string input_lattice;

  // Como las dos primeras líneas del fichero (si está en el formato correcto) serán el nº de filas y el nº de colunmas, las insertamos manualmente, para posteriormente definirlas.
  input_file >> rows_; 
  input_file >> cols_;

  // Definimos el tamaño que tendrá el vector que representa las filas, según el número leído del fichero.
  cells_.resize(rows_);
  // Para cada posición del vector de filas, es decir los que representan las columnas, definimos el tamaño que tendrán según el número leído del fichero.
  for (int j = 0; j < rows_; j++) { cells_[j].resize(cols_, Cell()); }
  
  // Definimos un bucle que recorrerá todas las líneas del fichero, y para cada línea, recorrerá todos los caracteres que contiene, definiendo su estado.
  char state;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      input_file >> state;
      cells_[i][j] = Cell(Position(i, j), State(state == '1' ? 1 : 0));
    }
  }

  // Cerramos el fichero una vez hemos terminado de leerlo.
  input_file.close();
}

/**
 * @brief Método para guardar el retículo en un fichero.
 * @param[in] filename: referencia (constante) al nombre del fichero donde se desea guardar el retículo.
 */
void Lattice::SaveFile(const std::string& filename) {
  // Definimos una variable como flujo de salida de ficheros, pasandole como parámetros el fichero que deseamos abrir.
  std::ofstream output_file(filename);

  // Comprobamos si se ha abierto correctamente.
  if (!(output_file.is_open())) {
    std::cout << "Error: No se pudo abrir el fichero." << std::endl;
    exit(EXIT_FAILURE);
  }

  // Insertamos en el fichero el número de filas y columnas que tiene el retículo.
  output_file << rows_ << std::endl;
  output_file << cols_ << std::endl;

  // Insertamos en el fichero el estado de las células del retículo.
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      output_file << cells_[i][j].getState().getState();
    }
    output_file << std::endl;
  }
  // Cerramos el fichero una vez hemos terminado de escribir en él.
  output_file.close();

  std::cout << "El retículo se ha guardado correctamente en el fichero '" << filename << "'." << std::endl;
}

/**
 * @brief Sobrecarga del operador de indexación ([]) para acceder a una célula del retículo.
 * @param[in] position: referencia (constante) a la posición de la célula que deseamos obtener.
 * @return Devuelve la célula que ocupa la posición especificada por parámetros dentro del retículo.
 */
Cell Lattice::operator[](const Position& position) const {
  // Nos aseguramos de que la posición especificada por parámetros esté dentro de los límites de la matriz <=> retículo.
  assert((position.getPosition().first >= 0)  && (position.getPosition().first < getRows()) && 
         (position.getPosition().second >= 0) && (position.getPosition().second < getCols()));

  return (cells_[position.getPosition().first][position.getPosition().second]);
}

/**
 * @brief Sobrecarga del operador de flujo de salida (<<) para la clase Lattice.
 * @param[in] os: referencia al objeto ostream (flujo de datos de salida).
 * @param[in] lattice: referencia (constante) del retículo a imprimir.
 * @return Devuelve la impresión del retículo.
 */
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  std::cout << std::endl;
  // Recorremos todas las células del retículo, imprimiendo su estado.
  for (int i = 0; i < lattice.getCols(); i++) { os << " _"; }
  std::cout << std::endl;
  for (int i = 0; i < lattice.getRows(); i++) {
    os << "|";
    for (int j = 0; j < lattice.getCols(); j++) {
      os << lattice[Position(i, j)] << "|";
    }
    os << std::endl;
  }
  for (int i = 0; i < lattice.getCols(); i++) { os << " ¯"; }
  return os;
}