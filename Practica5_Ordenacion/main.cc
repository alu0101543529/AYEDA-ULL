/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 5: Ordenación

 * @file   main.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   20/03/2024
 * @brief  Implementación del programa principal
 */

#include <fstream>

#include "include/sorting_methods/sort_method.h"
#include "include/nif.h"

/**
 * @brief Mensaje para mostrar el correcto uso de la línea de comandos.
 * @param[in] argv: variable para recoger los argumentos por línea de comandos.
 */
void Usage(char* argv[]) {
  std::cout << "Modo de uso: " << argv[0] << " [-h | --help ] -size <tamaño de la secuencia> -ord <'selection'|'heap'|'quick'|'shell'|'radix'> -init <'manual'|'random'|'file' <fichero de entrada>> -trace <'y'|'n'>" << std::endl << std::endl;
  std::cout << "-h | --help: Muestra las instrucciones para el correcto funcionamiento del programa." << std::endl;
  std::cout << "-size <tamaño de la secuencia>: Con esta opción se indica el tamaño que tiene la secuencia donde se almacenan las llaves/claves." << std::endl;
  std::cout << "-ord <'selection'|'heap'|'quick'|'shell'|'radix'>: Con esta opción se indica el algoritmo de ordenación que se va a utilizar." << std::endl;
  std::cout << "\tOrdenación por selección ('selection'): se ordena la secuencia mediante el algoritmo de ordenación de selección." << std::endl;
  std::cout << "\tOrdenación por montículo ('heap'): se ordena la secuencia mediante el algoritmo de ordenación de montículo." << std::endl;
  std::cout << "\tOrdenación rápida ('quick'): se ordena la secuencia mediante el algoritmo de ordenación rápida." << std::endl;
  std::cout << "\tOrdenación por shell ('shell'): se ordena la secuencia mediante el algoritmo de ordenación por shell." << std::endl;
  std::cout << "\tOrdenación por radix ('radix'): se ordena la secuencia mediante el algoritmo de ordenación por radix." << std::endl;
  std::cout << "-init <'manual'|'random'|'file' <fichero de entrada>>: Con esta opción se indica cómo se va a inicializar la secuencia." << std::endl;
  std::cout << "\tInicialización manual ('manual'): se inicializa la secuencia introduciendo los valores por teclado." << std::endl;
  std::cout << "\tInicialización aleatoria ('random'): se inicializa la secuencia con valores aleatorios." << std::endl;
  std::cout << "\tInicialización mediante fichero ('file' <fichero de entrada>): se inicializa la secuencia leyendo los valores del fichero proporcionado." << std::endl;
  std::cout << "-trace <'y'|'n'>: Con esta opción se indica si se quiere mostrar el rastro de la secuencia." << std::endl;
  std::cout << "\tMostrar rastro ('y'): se muestra el rastro de la secuencia." << std::endl;
  std::cout << "\tNo mostrar rastro ('n'): no se muestra el rastro de la secuencia." << std::endl;
  std::cout << std::endl;
}

/**
 * @brief Función para construir la Tabla Hash según los parámetros introducidos por el usuario por la línea de comandos.
 * @param[in] argc: entero que almacena el número de parámetros recogidos por línea de comandos.
 * @param[in] argv: variable para recoger los argumentos por línea de comandos.
 * @return Devuelve la secuencia de datos construida según los parámetros introducidos por el usuario por la línea de comandos.
 */
template <class Key>
staticSequence<Key> CommandLineArgs(int argc, char* argv[]) {
  staticSequence<Key> sequence;    // Variable que almacena la secuencia a ordenar
  int size;                        // Variable que almacena el tamaño de la secuencia a ordenar
  SortMethod<Key>* sort_method;    // Variable que almacena el tipo de método de ordenación (Selección, QuickSort, HeapSort, ShellSort, RadixSort)
  Key key;                         // Variable que almacena las diferentes claves (Key) de la secuencia
  bool trace = false;              // Variable que almacena si se quiere mostrar el rastro de la secuencia

  // Parseamos la línea de comandos
  for (int i = 1; i < argc; i++) {
    std::string argumento_actual = argv[i];

    // Opción -h | -help: Muestra el funcionamiento del programa.
    if ((argumento_actual == "-h")|| (argumento_actual == "-help")) { 
      Usage(argv);
      exit(EXIT_SUCCESS);
    }

    // Opción -size: Se introduce el tamaño de la secuencia.
    else if (argumento_actual == "-size") {
      // Si no se especifica el tamaño del retículo, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      if ((i + 1) > argc) {
        std::cerr << "Error: Falta argumento de tamaño de la secuencia a ordenar." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }

      size = std::stoi(argv[i + 1]);
      sequence = staticSequence<Key>(size);
    }

    // Opción -ord: Se introduce el método de ordenación.
    else if (argumento_actual == "-ord") {
      // Si no se especifica el método de ordenación, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      if ((i + 1) > argc) {
        std::cerr << "Error: Falta argumento de método de ordenación." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }

      if (std::string(argv[i + 1]) == "selection") { sort_method = new SelectionSort<Key>(sequence, size, trace); }
      else if (std::string(argv[i + 1]) == "quick") { sort_method = new QuickSort<Key>(sequence, size, trace); }
      else if (std::string(argv[i + 1]) == "heap") { sort_method = new HeapSort<Key>(sequence, size, trace); }
      else if (std::string(argv[i + 1]) == "shell") { sort_method = new ShellSort<Key>(sequence, size, trace); }
      else if (std::string(argv[i + 1]) == "radix") { sort_method = new RadixSort<Key>(sequence, size, trace); }

      // Si el tipo de método de ordenación no es conocido, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      else { 
        std::cerr << "Error: Método de ordenación no conocido." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }
    }

    // Opción -init: Se introduce la forma de introducir los datos.
    else if (argumento_actual == "-init") {
      // Si no se especifica la forma de introducir los datos, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      if ((i + 1) > argc) {
        std::cerr << "Error: Falta argumento de la forma de introducir los datos." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }
      
      if (std::string(argv[i + 1]) == "manual") { 
        int terminos_restantes = sequence.getSize();
        
        while(!sequence.isFull()) {
          std::cout << "Introduzca un nuevo término: (Términos restantes por ingresar: " << terminos_restantes << ") ";
          std::cin >> key;
          if (sequence.insert(key)) {
            std::cout << "La clave " << key << " se ha insertado correctamente de manera manual en la secuencia." << std::endl;
            terminos_restantes--;
          } else { 
            std::cerr << "La clave " << key << " no se ha podido insertar de manera manual en la secuencia." << std::endl;
            std::cout << "Por favor, vuelva a intentarlo..." << std::endl << std::endl;
          }
        }
      }

      else if (std::string(argv[i + 1]) == "random") { 
        while(!sequence.isFull()) {
          key = NIF();
          sequence.insert(key);
        }
      }

      else if (std::string(argv[i + 1]) == "file") {
        // Si no se especifica el fichero de entrada, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
        if ((i + 2) > argc) {
          std::cerr << "Error: Falta argumento de fichero de entrada." << std::endl << std::endl;
          Usage(argv);
          exit(EXIT_FAILURE);
        }

        std::string file_name = argv[i + 2];
        std::ifstream input_file(file_name);

        // Si no se puede abrir el fichero de entrada, mostramos un mensaje de error y salimos del programa.
        if (!input_file.is_open()) {
          std::cerr << "Error: No se ha podido abrir el fichero de entrada." << std::endl;
          exit(EXIT_FAILURE);
        }

        // Leemos el fichero de entrada y almacenamos los datos en la secuencia.
        while(!input_file.eof()) {
          input_file >> key;
          sequence.insert(key);
        }
        std::cout << std::endl;

        // Cerramos el fichero de entrada.
        input_file.close();
      }

      // Si la forma de introducir los datos no es conocida, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      else { 
        std::cerr << "Error: Forma de introducir los datos no conocida." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }
    }

    // Opción -trace: Se introduce si se quiere mostrar el rastro de la secuencia.
    else if (argumento_actual == "-trace") {
      // Si no se especifica si quiere mostrar la traza o no, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      if ((i + 1) > argc) {
        std::cerr << "Error: Falta argumento de si desea mostrar la traz o no." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }

      if (std::string(argv[i + 1]) == "y") { trace = true; }
      else if (std::string(argv[i + 1]) == "n") { trace = false; }

      // Si no se especifica si quiere mostrar la traza o no, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      else { 
        std::cerr << "Error: No se especifica si desea mostrar la traza o no." << std::endl << std::endl;
        Usage(argv);
        exit(EXIT_FAILURE);
      }
    }
  }

  // Mostramos la secuencia original y la secuencia ordenada, y la traza si se ha solicitado.
  std::cout << "Secuencia original: " << sequence.print() << std::endl;
  if (trace) { std::cout << "\nTraza: " << std::endl; }
  sort_method->Sort();
  std::cout << std::endl;
  std::cout << "Secuencia ordenada: " << sort_method->print() << std::endl;
  
  return sequence;
}

int main(int argc, char* argv[]) {
  // Inicializamos la semilla para la generación de números aleatorios
  srand(time(NULL)); 

  // Si no se introducen argumentos por la línea de comandos, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
  if (argc <= 1) {
    std::cerr << "Error: Para la correcta ejecución de " << argv[0] << " faltan argumentos." << std::endl << std::endl;
    Usage(argv);
    exit(EXIT_FAILURE);
  }
  
  std::cout << "Práctica 5: Ordenación, Algoritmos y Estructuras de Datos Avanzadas 2023-2024, Raúl González Acosta" << std::endl;

  // Construimos la secuencia de datos según los parámetros introducidos por el usuario por la línea de comandos.
  CommandLineArgs<NIF>(argc, argv);

  return 0; 
}