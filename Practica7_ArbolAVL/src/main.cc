/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 7: Árbol AVL

 * @file   main.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   15/04/2024
 * @brief  Implementación del programa principal
 */

#include <fstream>

#include "AB/ABB.h"
#include "AB/ABE.h"
#include "AB/AVL.h"
#include "nif.h"

/**
 * @brief Mensaje para mostrar el correcto uso de la línea de comandos.
 * @param[in] argv: variable para recoger los argumentos por línea de comandos.
 */
void Usage(char* argv[]) {
  std::cout << "Modo de uso: " << argv[0] << " [-h | --help ] -ab <'abb'|'abe'|'avl'> -init <'manual'|'random' <nº elementos a generar> |'file' <nº elementos a generar> <nombre del fichero>>" << std::endl << std::endl;
  std::cout << "-h | --help: Muestra las instrucciones para el correcto funcionamiento del programa." << std::endl;
  std::cout << "-ab: Con esta opción se indica el tipo de árbol a utilizar (ABB o ABE)." << std::endl;
  std::cout << "\tÁrbol Binario de Búsqueda (ABB): es un tipo de árbol en el que las claves/llaves se ordenan de menor (subárbol izquierdo) a mayor (subárbol derecho) con respecto a la raíz." << std::endl;
  std::cout << "\tÁrbol binario Equilibrado (ABE): es un tipo de árbol en el que las claves/llaves se van ordenando por niveles, es decir independientemente del orden, hasta que un nivel no se haya completado, no se empieza a rellenar el siguiente." << std::endl;
  std::cout << "\tÁrbol binario Adelson-Velskii y Landis (AVL): es un tipo de árbol binario de búsqueda en el que para cada nodo, las alturas de los subárboles izquierdo y derecho difieren en como máximo uno." << std::endl;
  std::cout << "-init <'manual'|'random' <nº elementos a generar> |'file' <nº elementos a generar> <nombre del fichero>>: Con esta opción se indica cómo se van a inicializar los nodos del árbol." << std::endl;
  std::cout << "\tInicialización manual ('manual'): se inicializan los nodos introduciendo los valores por teclado." << std::endl;
  std::cout << "\tInicialización aleatoria ('random' <nº elementos a generar>): se inicializan el número de nodos especificado con claves aleatorias." << std::endl;
  std::cout << "\tInicialización mediante fichero ('file' <nº elementos a generar> <fichero de entrada>): se inicializan el número de nodos especificado leyendo los valores del fichero proporcionado." << std::endl;
  std::cout << std::endl;
}

/**
 * @brief Menú para la selección de opciones para el uso del árbol binario.
 * @param[in] opcion: caracter (referencia) que recoge las opciones del usuario para ser evaluadas.
 */
void Menu (char& opcion) {
  std::cout << "Práctica 6: TAD Árbol, Algoritmos y Estructuras de Datos Avanzadas 2023-2024, Raúl González Acosta" << std::endl << std::endl;
  std::cout << "============== MENÚ DE OPCIONES ==============" << std::endl;
  std::cout << "i. [I]nsertar una clave en el árbol." << std::endl;
  std::cout << "b. [B]uscar una clave en el árbol." << std::endl;
  std::cout << "o. Mostrar el recorrido en in[o]rden del árbol." << std::endl;
  std::cout << "m. [M]ostrar el árbol en pantalla (por niveles)." << std::endl << std::endl;

  std::cout << "q. Finalizar el programa" << std::endl << std::endl;
  
  std::cout << "Introduce la letra de la acción a ejecutar  > ";
  std::cin >> opcion;
}

int main(int argc, char* argv[]) {
  srand(time(NULL));         // Inicializamos la semilla para la generación de números aleatorios

  AB<NIF>* tree;             // Variable para almacenar el árbol
  int num_elements = 0;      // Variable para almacenar el número de elementos a generar
  NIF key;                   // Variable para almacenar la clave del nodo
  char opcion;               // Variable donde guardaremos la opción a ser evaluada por el menú del programa

  // Si no se han introducido argumentos por línea de comandos, se muestra un mensaje de error y la función que muestra el uso correcto del programa
  if (argc <= 1) {
    std::cerr << "Error: No se han introducido argumentos por línea de comandos." << std::endl << std::endl;
    Usage(argv);
    exit(EXIT_FAILURE);
  }

  // Parseamos los argumentos de la línea de comandos
  for (int i = 1; i < argc; i++) {
    std::string argumento_actual = argv[i];

    // Opción -h | -help: Muestra el funcionamiento del programa.
    if ((argumento_actual == "-h")|| (argumento_actual == "-help")) { 
      Usage(argv);
      exit(EXIT_SUCCESS);
    }

    // Opción -ab: Selecciona el tipo de árbol a utilizar
    if (argumento_actual == "-ab") {
      // Si no se ha especificado el tipo de árbol, se muestra un mensaje de error y la función que muestra el uso correcto del programa
      if ((i + 1) > argc) {
        std::cerr << "Error: Falta argumento del tipo de árbol." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }

      if (std::string(argv[i + 1]) == "abb") { tree = new ABB<NIF>(); }
      else if (std::string(argv[i + 1]) == "abe") { tree = new ABE<NIF>(); }
      else if (std::string(argv[i + 1]) == "avl") { tree = new AVL<NIF>(); }

      // Si el tipo de árbol no es válido, se muestra un mensaje de error y se muestra el uso correcto del programa
      else {
        std::cerr << "Error: Tipo de árbol no válido." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }
    }

    // Opción -init: Selecciona el método de inicialización de los nodos del árbol
    else if (argumento_actual == "-init") {
      // Si no se ha especificado la forma de introducir los datos, se muestra un mensaje de error y la función que muestra el uso correcto del programa
      if ((i + 1) > argc) {
        std::cerr << "Error: Falta argumento de la forma de introducir los datos." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }

      if (std::string(argv[i + 1]) == "manual") {
        std::cout << "Introduzca una clave a insertar en el árbol (inserte -1 para finalizar):" << std::endl;
        while (std::cin >> key && key != NIF(-1)) {
          if (tree->insert(key)) { std::cout << "La clave " << key << " se ha insertado correctamente de manera manual en el árbol." << std::endl; }
          else { std::cout << "La clave " << key << " ya existe en el árbol." << std::endl; }
        }
      }

      else if (std::string(argv[i + 1]) == "random") {
        // Si no se ha especificado el número de elementos a generar, se muestra un mensaje de error y la función que muestra el uso correcto del programa
        if ((i + 2) > argc) {
          std::cerr << "Error: Falta argumento del número de elementos a generar." << std::endl << std::endl;
          Usage(argv);
          exit(EXIT_FAILURE);
        }
        
        num_elements = std::stoi(argv[i + 2]);
        for (int i = 0; i < num_elements; i++) {
          key = NIF();
          if (tree->insert(key)) { std::cout << "La clave " << key << " se ha insertado correctamente de manera aleatoria en el árbol." << std::endl; }
          else { std::cout << "La clave " << key << " ya existe en el árbol." << std::endl; }
        }
      }

      else if (std::string(argv[i + 1]) == "file") {
        if ((i + 2) > argc || (i + 3) > argc){
          std::cerr << "Error: Falta argumento del número de elementos a generar o del nombre del fichero." << std::endl << std::endl;
          Usage(argv);
          exit(EXIT_FAILURE);
        }

        num_elements = std::stoi(argv[i + 2]);
        std::string filename = argv[i + 3];

        std::ifstream input_file(filename);

        // Si no se ha podido abrir el fichero, se muestra un mensaje de error y se finaliza el programa
        if (!input_file.is_open()) {
          std::cerr << "Error: No se ha podido abrir el fichero de entrada." << std::endl << std::endl;
          Usage(argv);
          exit(EXIT_FAILURE);
        }

        // Leemos los datos del fichero y los insertamos en el árbol
        for (int i = 0; i < num_elements; i++) {
          input_file >> key;
          if (tree->insert(key)) { std::cout << "La clave " << key << " se ha insertado correctamente desde el fichero " << filename << " en el árbol." << std::endl; }
          else { std::cout << "La clave " << key << " ya existe en el árbol." << std::endl; }
        }
        
        // Cerramos el fichero
        input_file.close();
      }

      // Si la forma de introducir los datos no es válida, se muestra un mensaje de error y se finaliza el programa
      else {
        std::cerr << "Error: Forma de introducir los datos no válida." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }
    }
  }

  // Hacemos un bucle que después de ejecutarse cualquier opción != 'q' vuelva al menú.
  do {
    Menu(opcion);
    std::cout << std::endl;
    switch (opcion) {
      // Opción 'i': Insertar una clave en el árbol.
      case ('i'): {
        system("clear");
        std::cout << "Introduzca una clave a insertar en el árbol (inserte -1 para finalizar):" << std::endl;
        while (std::cin >> key && key != NIF(-1)) {
          if (tree->insert(key)) { std::cout << "La clave " << key << " se ha insertado correctamente en el árbol." << std::endl; }
          else { std::cout << "La clave " << key << " ya existe en el árbol." << std::endl; }
        }
        std::cout << tree << std::endl;
        break;
      }

      // Opción 'b': Buscar una clave en el árbol.
      case ('b'): {
        system("clear");
        std::cout << "Introduzca una clave a buscar en el árbol (inserte -1 para salir):" << std::endl;
        while (std::cin >> key && key != NIF(-1)) {
          if (tree->search(key)) { std::cout << "La clave " << key << " se encuentra en el árbol." << std::endl; }
          else { std::cout << "La clave " << key << " no se encuentra en el árbol." << std::endl; }
        }
        std::cout << std::endl;
        break;
      }

      // Opción 'o': Mostrar el recorrido en inorden del árbol.
      case ('o'): {
        system("clear");
        std::cout << "Recorrido en inorden del árbol: ";
        tree->inorder();
        std::cout << tree << std::endl;
        break;
      }

      // Opción 'm': Mostrar el árbol en pantalla (por niveles).
      case ('m'): {
        system("clear");
        std::cout << tree << std::endl;
        break;
      }

      // Opción 'q': Salir del programa.
      case ('q'): { break; }

      // Opción 'default': Ninguna de las opciones anteriores.
      default: {
        system("clear");
        std::cout << std::endl << "Opción no valida, intentalo de nuevo" << std::endl << std::endl;
        break;
      }
    }
  } while (opcion != 'q');

  delete tree;  // Liberamos la memoria del árbol

  return 0;
}