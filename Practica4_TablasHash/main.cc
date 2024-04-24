/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 4: Tabla Hash

 * @file   main.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   07/03/2024
 * @brief  Implementación del programa principal
 */

#include "include/hash_table.h"
#include "include/nif.h"

/**
 * @brief Menú para la selección de opciones para el uso de la Tabla Hash.
 * @param[in] opcion: caracter (referencia) que recoge las opciones del usuario para ser evaluadas.
 */
void Menu (char& opcion) {
  std::cout << "Práctica 4: Tabla Hash, Algoritmos y Estructuras de Datos Avanzadas 2023-2024, Raúl González Acosta" << std::endl << std::endl;
  std::cout << "================================================ MENÚ DE OPCIONES ================================================" << std::endl;
  std::cout << "m. [M]ostrar la Tabla Hash." << std::endl;
  std::cout << "i. [I]nsertar un valor en la Tabla Hash." << std::endl;
  std::cout << "b. [B]uscar un valor en la Tabla Hash." << std::endl << std::endl;

  std::cout << "q. Finalizar el programa" << std::endl << std::endl;
  
  std::cout << "Introduce la letra de la acción a ejecutar  > ";
  std::cin >> opcion;
}

/**
 * @brief Mensaje para mostrar el correcto uso de la línea de comandos.
 * @param[in] argv: variable para recoger los argumentos por línea de comandos.
 */
void Usage(char* argv[]) {
  std::cout << "Modo de uso: " << argv[0] << " [-h | --help ] -ts <tamaño de la tabla> -fd <'module'|'sum'|'random'> -hash <'open'|'close' -bs <tamaño de la secuencia> -fe <'lineal'|'cuadratic'|'redispersion'|'doubledispersion'>>" << std::endl << std::endl;
  std::cout << "-h | --help: Muestra las instrucciones para el correcto funcionamiento del programa." << std::endl;
  std::cout << "-ts <tamaño de la tabla>: Con esta opción se indica el tamaño que tiene la Tabla Hash donde se almacenan las llaves/claves." << std::endl;
  std::cout << "-fd <'module'|'sum'|'random'>: Con esta opción definimos la función de dispersión que vamos a usar: " << std::endl;
  std::cout << "\tFunción Módulo ('module'): se ajusta en la posición de la tabla el elemento insertado según la siguiente operación: elemento % tamaño de la tabla." << std::endl;
  std::cout << "\tFunción Suma ('sum'): se ajusta en la posición de la tabla el elemento insertado según el número de la suma de sus dígitos (ajustándose al tamaño de esta)." << std::endl;
  std::cout << "\tFunción Pseudoaletoria ('random'): se ajusta en la posición de la tabla el elemento insertado aleatoriamente." << std::endl;
  std::cout << "-hash <'open'|'close>: Con esta opción definimos la técnica de dispersión a usar:" << std::endl;
  std::cout << "\tSecuencia dinámica ('open'): cada secuencia de la tabla tiene tamaño indefinido." << std::endl;
  std::cout << "\tSecuencia estática ('close'): cada secuencia de la tabla tiene un tamaño definido, y por tanto se deben espeficiar las siguientes opciones:." << std::endl;
  std::cout << "\t-bs <tamaño del bloque>: Con esta opción se indica el tamaño que va a tener cada secuencia." << std::endl;
  std::cout << "\t-fe <'lineal'|'cuadratic'|'redispersion'|'doubledispersion'>: Con esta opción definimos la función de exploración que vamos a usar en caso de desbordamiento de la secuencia:" << std::endl;
  std::cout << "\t\tExploración Lineal ('lineal'): se reajusta en la posición de la tabla el elemento insertado incrementando en uno el índice." << std::endl;
  std::cout << "\t\tExploración Cuadrática ('cuadratic'): se ajusta en la posición de la tabla el elemento insertado incrementando cuadráticamente el índice." << std::endl;
  std::cout << "\t\tRedispersión ('redispersion'): se ajusta en la posición de la tabla el elemento insertado según la siguiente operación: (posición + i * h'(k)) % tamaño de la tabla." << std::endl;
  std::cout << "\t\tDoble Dispersión ('doubledispersion'): se ajusta en la posición de la tabla el elemento insertado según la siguiente operación: (posición + i * h'(k)) % tamaño de la tabla." << std::endl;
}

/**
 * @brief Función para construir la Tabla Hash según los parámetros introducidos por el usuario por la línea de comandos.
 * @param[in] argc: entero que almacena el número de parámetros recogidos por línea de comandos.
 * @param[in] argv: variable para recoger los argumentos por línea de comandos.
 * @return Devuelve la Tabla Hash construida según los parámetros introducidos por línea de comandos.
 */
template <class Key, class Container>
HashTable<Key, Container> CommandLineArgs(int argc, char* argv[]) {
  int tableSize;                                  // Variable que almacena el tamaño de la tabla hash
  DispersionFunction<Key>* dispersion_function;   // Variable que almacena el tipo de función de dispersión a usar (modulo, basada en la suma o pseudoaleatoria)
  Sequence<Key>* dispersion_type;                 // Variable que almacena el técnica de dispersión a usar (abierta o cerrada)
  int blockSize;                                  // Variable que almacena el tamaño del bloque
  ExplorationFunction<Key>* exploration_function; // Variable que almacena el tipo de función de exploración a usar (lineal, cuadrática, redispersión o doble dispersión)

  // Parseamos la línea de comandos
  for (int i = 1; i < argc; i++) {
    std::string argumento_actual = argv[i];
    
    // Opción -h | -help: Muestra el funcionamiento del programa.
    if ((argumento_actual == "-h")|| (argumento_actual == "-help")) { 
      Usage(argv);
      exit(EXIT_SUCCESS);
    }

    // Opción -ts: Se introduce el tamaño de la tabla hash.
    else if (argumento_actual == "-ts") {
      // Si no se especifica el tamaño del retículo, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      if ((i + 1) > argc) {
        std::cerr << "Falta argumento de tamaño de la tabla hash." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }

      tableSize = std::stoi(argv[i + 1]);
    }

    // Opción -fd: Se introduce el tipo de función de dispersión.
    else if (argumento_actual == "-fd") {
      // Si no se especifica la función de dispersión, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      if ((i + 1) > argc) {
        std::cerr << "Falta argumento de función de dispersión." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }

      if (std::string(argv[i + 1]) == "module") { dispersion_function = new Module<Key>(tableSize); }
      else if (std::string(argv[i + 1]) == "sum") { dispersion_function = new SumBased<Key>(tableSize); }
      else if (std::string(argv[i + 1]) == "random") { dispersion_function = new Random<Key>(tableSize); }
      // Si el tipo de función de dispersión no es conocido, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      else { 
        std::cerr << "Error: Tipo de función de dispersión no conocido." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }
    }

    // Opción -hash: Se introduce la técnica de dispersión.
    else if (argumento_actual == "-hash") {
      // Si no se especifica la técnica de dispersión, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      if ((i + 1) > argc) {
        std::cerr << "Falta argumento de la técnica de dispersión a usar." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }
      
      // Si se especifica la técnica de dispersión 'close', se debe especificar el tamaño del bloque y la función de exploración.
      if (std::string(argv[i + 1]) == "close") { 
        // Si no se especifica el tamaño del bloque o la función de exploración, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
        if (((i + 3) > argc) || ((i + 5) > argc)) {
          std::cerr << "Falta argumento del tamaño de bloque o función de exploración." << std::endl << std::endl;
          Usage(argv);
          exit(EXIT_FAILURE);
        }

        blockSize = (std::stoi(argv[i + 3]));
        
        if (std::string(argv[i + 5]) == "lineal") { exploration_function = new LinealExploration<Key>; }
        else if (std::string(argv[i + 5]) == "cuadratic") { exploration_function = new CuadraticExploration<Key>; }
        else if (std::string(argv[i + 5]) == "redispersion") { exploration_function = new RedispersionExploration<Key>(new Module<Key>(tableSize)); }
        else if (std::string(argv[i + 5]) == "doubledispersion") { exploration_function = new DoubleDispersionExploration<Key>(new Module<Key>(tableSize)); }
        // Si el tipo de función de exploración no es conocido, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.  
        else { 
          std::cerr << "Error: Tipo de función de exploración no conocido." << std::endl << std::endl;
          Usage(argv);
          exit(EXIT_FAILURE);
        }
        return HashTable<Key, staticSequence<Key>>(tableSize, dispersion_function, exploration_function, blockSize);
      }

      // Si no se especifica un tipo de técnica de dispersión, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      else { 
        std::cerr << "Error: Tipo de técnica de dispersión no conocido." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }
    }
  }
}

/**
 * @brief Función principal del programa.
 * @param[in] argc: entero que almacena el número de parámetros recogidos por línea de comandos.
 * @param[in] argv: variable para recoger los argumentos por línea de comandos.
 */
int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cerr << "Error: Para la correcta ejecución de " << argv[0] << " faltan argumentos." << std::endl << std::endl;
    Usage(argv);
    exit(EXIT_FAILURE);
  }
  
  // Construimos la Tabla Hash según los parámetros introducidos por el usuario por la línea de comandos.
  HashTable<NIF, staticSequence<NIF>> hashTable = CommandLineArgs<NIF, staticSequence<NIF>>(argc, argv);
  //HashTable<NIF, dynamicSequence<NIF>> hashTable(10, new Module<NIF>(10));

  // Variable donde guardaremos la opción a ser evaluada por el menú del programa
  char opcion;

  // Hacemos un bucle que después de ejecutarse cualquier opción != 'q' vuelva al menú.
  do {
    Menu(opcion);
    std::cout << std::endl;
    switch (opcion) {
      // Opción 'b': Busca el valor de una clave en la Tabla Hash.
      case ('b'): {
        system("clear");
        NIF key;
        std::cout << "Introduzca la clave a buscar en la Tabla Hash: ";
        std::cin >> key;

        if (hashTable.search(key)) { std::cout << "La clave " << key << " se encuentra en la Tabla Hash." << std::endl; }
        else { std::cout << "La clave " << key << " no se encuentra en la Tabla Hash." << std::endl; }

        std::cout << std::endl;
        break;
      }

      // Opción 'i': Inserta un valor en la Tabla Hash.
      case ('i'): {
        system("clear");

        NIF nif, key;
        std::cout << "Introduzca la clave a insertar en la Tabla Hash (Introduzca -1 para que la clave sea aleatoria): ";
        std::cin >> nif;

        if (nif == -1) { key = NIF(); }
        else { key = nif; }

        if (hashTable.insert(key)) { std::cout << "La clave " << key << " se ha insertado correctamente en la Tabla Hash." << std::endl; }
        else { std::cout << "La clave " << key << " no se ha podido insertar en la Tabla Hash." << std::endl; }

        std::cout << std::endl;
        break;
      }
      
      // Opción 'm': Muestra por pantalla la Tabla Hash.
      case ('m'): {
        system("clear");
        std::cout << hashTable << std::endl << std::endl;
        break;
      }

      // Opción 'q': Salir del programa.
      case ('q'): { break; }

      // Opción 'default': Ninguna de las opciones anteriores.
      default: {
        system("clear");
        std::cout << "Opción no valida, intentalo de nuevo" << std::endl << std::endl;
        break;
      }
    }
  } while (opcion != 'q');

  std::cout << "Fin del programa." << std::endl;

  return 0;
}