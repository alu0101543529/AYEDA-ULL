/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 1: Autómata Celular Elemental

 * @file   main.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2024
 * @brief  Implementación del programa principal
 */

#include <cassert>

#include "header_files/lattice.h"
#include "header_files/cell.h"

/**
 * @brief Menú para la selección de opciones para el uso del autómata celular elemental.
 * @param[in] opcion: caracter (referencia) que recoge las opciones del usuario para ser evaluadas.
 */
void Menu (char& opcion) {
  std::cout << "Práctica 1: Autómata Celular Elemental, Algoritmos y Estructuras de Datos Avanzadas 2023-2024, Raúl González Acosta" << std::endl << std::endl;
  std::cout << "============== MENÚ DE OPCIONES ==============" << std::endl;
  std::cout << "c. [C]argar retículo desde fichero." << std::endl;
  std::cout << "a. Mostrar la generación [a]ctual del retículo." << std::endl;
  std::cout << "g. Mostrar la siguiente [g]eneración del retículo." << std::endl;
  std::cout << "i. Mostrar las siguientes generaciones del retículo [i]ndefinidamente." << std::endl;
  std::cout << "n. Mostrar las siguientes [n] generaciones del retículo." << std::endl;
  std::cout << "v. Mostrar cuántas células [v]ivas hay en la generación actual." << std::endl;
  std::cout << "m. Mostrar cuántas células [m]uertas hay en la generación actual." << std::endl << std::endl;

  std::cout << "r. [R]einiciar el retículo a la configuración inicial." << std::endl;
  std::cout << "q. Finalizar el programa" << std::endl << std::endl;
  
  std::cout << "Introduce la letra de la acción a ejecutar  > ";
  std::cin >> opcion;
}

/**
 * @brief Mensaje para mostrar el correcto uso del autómata celular elemental.
 * @param[in] argv: variable para recoger los argumentos por línea de comandos.
 */
void ShowHelp(char* argv[]) {
  std::cout << "Modo de uso: " << argv[0] << " <tamaño del retículo> [-h | --help ] -size <tamaño del retículo> -border <'open' v = <0|1> | 'periodic'> [-init <fichero de entrada>]" << std::endl << std::endl;
  std::cout << "-h | --help: Muestra las instrucciones para el correcto funcionamiento del programa." << std::endl;
  std::cout << "-size <tamaño del retículo>: Con esta opción se indica el tamaño que debe tener el retículo donde se desarrola el autómata celular." << std::endl;
  std::cout << "-border <'open' v = <0|1> | 'periodic'>: Con esta opción el autómata toma comportamientos distintos: " << std::endl;
  std::cout << "\t1. Si el tipo de frontera es abierta ('open'), se le debe indicar si las células frontera tienen las células adyacentes con estado '0' o '1'." << std::endl;
  std::cout << "\t2. Si el tipo de frontera es periódica ('periodic') las células adyacentes de estas son las que se encuentran en el otro lado del retículo de forma espejo, generandose así una estructura cíclica." << std::endl;
  std::cout << "-init <fichero de entrada>: Con esta opción se le puede indicar un fichero con una configuración incial de estado de células en el formato correcto." << std::endl;
}

/**
 * @brief Función para regular el uso correcto del autómata celular elemental.
 * @param[in] argc: entero que almacena el número de parámetros recogidos por línea de comandos.
 * @param[in] argv: variable para recoger los argumentos por línea de comandos.
 */
void Usage(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cout << "Error: Para la correcta ejecución de " << argv[0] << " se le debe pasar un tamaño para el retículo." << std::endl;
    ShowHelp(argv);
    exit (EXIT_FAILURE);
  } else { ShowHelp(argv); }
}

/**
 * @brief Función para construir el retículo según los parámetros introducidos por el usuario por la línea de comandos.
 * @param[in] argc: entero que almacena el número de parámetros recogidos por línea de comandos.
 * @param[in] argv: variable para recoger los argumentos por línea de comandos.
 * @return Devuelve el retículo construido según los parámetros introducidos por línea de comandos.
 */
Lattice CommandLineArgs(int argc, char* argv[]) {
  int tamaño;                                   // Variable que almacena el tamaño que tiene el retículo
  std::string tipo_de_frontera;                 // Variable que almacena el tipo de frontera que tiene el retículo ("open" || "periodic")
  bool temperatura_de_la_frontera;              // Variable que almacena, en caso de ser forntera de tipo "open", la temperatura de las células exteriores ('0' || '1')
  std::string fichero_reticulo_personalizado;   // Variable que almacena el nombre del fichero que contiene el retículo a cargar

  // Parseamos la línea de comandos
  for (int i = 1; i < argc; i++) {
    std::string argumento_actual = argv[i];
    
    // Opción -h | -help: Muestra el funcionamiento del programa.
    if ((argumento_actual == "-h")|| (argumento_actual == "-help")) { 
      ShowHelp(argv);
      exit(EXIT_SUCCESS);
    }

    // Opción -size: Se introduce el tamaño que va a tener el retículo
    else if (argumento_actual == "-size") {
      // Si no se especifica el tamaño del retículo, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      if ((i + 1) > argc) {
        std::cerr << "Falta argumento de tamaño del retículo." << std::endl << std::endl;
        Usage(argc, argv); 
      }

      tamaño = std::stoi(argv[i + 1]);
    }

    // Opción -border: Se introduce el tipo de frontera que va a tener el retículo.
    else if (argumento_actual == "-border") {
      // Si no se especifica el tipo de borde, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      if ((i + 1) > argc) {
        std::cerr << "Falta argumento de tipo de borde del retículo." << std::endl << std::endl;
        Usage(argc, argv);
      }

      // Si la frontera es de tipo abierto, nos tienen que indicar la temperatura de las células exteriores.
      if (std::string(argv[i + 1]) == "open") { 
        tipo_de_frontera = "open";

        // Si no se especifica la temperatura de las células exteriores, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
        if ((i + 4) > argc) {
          std::cerr << "Falta argumento de temperatura de las células exteriores." << std::endl << std::endl;
          Usage(argc, argv); 
        }

        if (std::string(argv[i + 4]) == "0") { temperatura_de_la_frontera = 0; }
        else if (std::string(argv[i + 4]) == "1") { temperatura_de_la_frontera = 1; }
        // Si no se especifica una temperatura conocida, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
        else {
          std::cerr << "Error: Temperatura de células frontera no conocida." << std::endl << std::endl;
          Usage(argc, argv);
        }
      }

      else if (std::string(argv[i + 1]) == "periodic") { tipo_de_frontera = "periodic"; }
      
      // Si no se especifica un tipo de frontera conocido, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      else { 
        std::cerr << "Error: Tipo de frontera no conocido." << std::endl << std::endl;
        Usage(argc, argv);
      }
    }

    // Opción -init: Se introduce un fichero que contiene el retículo a usar.
    else if (argumento_actual == "-init") {
      // Si no se especifica el fichero a cargar, mostramos un mensaje de error y la función que muestra el correcto funcionamiento.
      if ((i + 1) > argc) {
        std::cerr << "Falta el fichero para cargar una configuración del retículo." << std::endl << std::endl;
        Usage(argc, argv);
      }

      fichero_reticulo_personalizado = std::string(argv[i + 1]);
      Lattice reticulo_fichero;
      reticulo_fichero.OpenFile(fichero_reticulo_personalizado);
      return reticulo_fichero;
    }
  }

  // Construimos el retículo con los parámetros recogidos según las opciones indicadas por línea de comandos
  Lattice reticulo(tamaño, tipo_de_frontera, temperatura_de_la_frontera);

  return reticulo;
}


int main (int argc, char *argv[]) {
  // Se necesitan al menos 2 argumentos para poder ejecutar el programa: "<programa> -h" || "<programa> -init <nombre fichero>" || "<programa> -size <tamaño> -border <periodic|open <v = <temperatura>>".
  if (argc <= 1) { Usage(argc, argv); }

  // Construimos el retículo con el que vamos a trabajar según los parámetros de línea de comandos introducidos por el usuario.
  Lattice reticulo = CommandLineArgs(argc, argv);
  
  char opcion;                // Variable donde guardaremos la opción a ser evaluada por el menú del programa
  int generacion_actual{0};   // Variable contadora de la generación en la que se encuentra el retículo

  // Hacemos un bucle que después de ejecutarse cualquier opción != 'q' vuelva al menú.
  do {
    Menu(opcion);
    std::cout << std::endl;
    switch (opcion) {
      // Opción 'c': Permite cargar un retículo desde un fichero introducido.
      case ('c'): {
        system("clear");
        std::string nombre_fichero;
        std::cout << "Introduzca el nombre del fichero que se desea cargar: ";
        std::cin >> nombre_fichero;
        std::cout << std::endl;
        reticulo.OpenFile(nombre_fichero);
        break;
      }

      // Opción 'a': Muestra el retículo en la generación actual en la que se encuentra.
      case ('a'): {
        system("clear");
        std::cout << "Generación: " << generacion_actual << " -> " << reticulo << std::endl << std::endl;
        break;
      }

      // Opción 'g': Muestra la siguiente generación del retículo.
      case ('g'): {
        system("clear");
        reticulo.nextGeneration();
        generacion_actual++;
        std::cout << "Generación: " << generacion_actual << " -> " << reticulo << std::endl << std::endl;
        break;
      }

      // Opción 'i': Muestra indefinidamente las generaciones del retículo.
      case ('i'): {
        system("clear");
        std::cout << "Pulse cualquier tecla alfanumérica para comenzar la secuencia de generaciones indefinidas." << std::endl << std::endl;
        std::cin.ignore();
        std::cin.ignore();

        while (true) {
          std::cout << "Generación: " << generacion_actual << " -> " << reticulo;
          reticulo.nextGeneration();
          generacion_actual++;
        }
        std::cout << std::endl << std::endl;
        break;
      }
      
      // Opción 'n': Muestra la siguientes 'n' generaciones del retículo.
      case ('n'): {
        system("clear");
        int iteraciones{0};
        std::cout << "Introduzca el número de generaciones a realizar: ";
        std::cin >> iteraciones;
        system("clear");
        for (int i = 0; i < iteraciones; i++) {
          reticulo.nextGeneration();
          generacion_actual++;
          std::cout << "Generación: " << generacion_actual << " -> " << reticulo;
        }
        std::cout << std::endl << std::endl;
        break;
      }

      // Opción 'v': Muestra las células que se encuentran vivas en el retículo en la generación actual.
      case ('v'): {
        system("clear");
        std::cout << "En la generación " << generacion_actual << " se encuentran vivas " << reticulo.AliveCells() << " células." << std::endl << std::endl;
        break;
      }

      // Opción 'm': Muestra las células que se encuentran muertas en el retículo en la generación actual.
      case ('m'): {
        system("clear");
        std::cout << "En la generación " << generacion_actual << " se encuentran muertas " << reticulo.DeadCells() << " células." << std::endl << std::endl;
        break;
      }

      // Opción 'r': Reinicia el retículo a la generación '0' con su configuración inicial.
      case ('r'): {
        system("clear");
        reticulo.InitialSetting();
        generacion_actual = 0;
        std::cout << "Se ha reiniciado correctamente el retículo." << std::endl << std::endl;
        std::cout << "Actualmente está en la generación " << generacion_actual << " -> " << reticulo << std::endl << std::endl;
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

  return 0;
}