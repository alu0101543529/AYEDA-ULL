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

#include "header_files/lattice.h"
#include "header_files/cell.h"

/**
 * @brief Menú para la selección de opciones para el uso del autómata celular elemental.
 * @param[in] opcion: caracter (referencia) que recoge las opciones del usuario para ser evaluadas.
 */
void Menu (char& opcion) {
  std::cout << "Práctica 1: Autómata Celular Elemental, Algoritmos y Estructuras de Datos Avanzadas 2023-2024, Raúl González Acosta" << std::endl;
  std::cout << "c. [C]argar retículo desde fichero." << std::endl;
  std::cout << "a. Mostrar la generación [a]ctual del retículo." << std::endl;
  std::cout << "g. Mostrar la siguiente [g]eneración del retículo." << std::endl;
  std::cout << "i. Mostrar las siguientes generaciones del retículo [i]ndefinidamente." << std::endl;
  std::cout << "n. Mostrar las siguientes [n] generaciones del retículo." << std::endl;
  std::cout << "v. Mostrar cuántas células [v]ivas hay en la generación actual." << std::endl;
  std::cout << "m  Mostrar cuántas células [m]uertas hay en la generación actual." << std::endl << std::endl;

  std::cout << "q. Finalizar el programa" << std::endl << std::endl;
  
  std::cout << "Introduce la letra de la accion a ejecutar  > ";
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
  exit (EXIT_FAILURE);
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
  int tamaño;
  std::string tipo_de_frontera;
  bool temperatura_de_la_frontera;
  std::string fichero_reticulo_personalizado;

  for (int i = 1; i < argc; i++) {
    std::string argumento_actual = argv[i];
    
    if ((argumento_actual == "-h")|| (argumento_actual == "-help")) { ShowHelp(argv); }

    else if (argumento_actual == "-size") {
      if ((i + 1) > argc) {
        std::cerr << "Falta argumento de tamaño del retículo." << std::endl << std::endl;
        Usage(argc, argv); 
      }
      tamaño = std::stoi(argv[i + 1]);
    }

    else if (argumento_actual == "-border") {
      if ((i + 1) > argc) {
        std::cerr << "Falta argumento de tipo de borde del retículo." << std::endl << std::endl;
        Usage(argc, argv);
      }
      if (std::string(argv[i + 1]) == "open") { 
        tipo_de_frontera = "open";
        if ((i + 4) > argc) {
          std::cerr << "Falta argumento de temperatura de las células exteriores." << std::endl << std::endl;
          Usage(argc, argv); 
        }
        if (std::string(argv[i + 4]) == "0") { temperatura_de_la_frontera = 0; }
        else if (std::string(argv[i + 4]) == "1") { temperatura_de_la_frontera = 1; }
        else { 
          std::cerr << "Error: Temperatura de frontera no conocida." << std::endl << std::endl;
          Usage(argc, argv);
        }
      }
      else if (std::string(argv[i + 1]) == "periodic") { tipo_de_frontera = "periodic"; }
      else { 
        std::cerr << "Error: Tipo de frontera no conocido." << std::endl << std::endl;
        Usage(argc, argv);
      }
    }

    else if (argumento_actual == "-init") {
      if ((i + 1) > argc) {
        std::cerr << "Falta el fichero para cargar una configuración del retículo." << std::endl << std::endl;
        Usage(argc, argv);
      }
      fichero_reticulo_personalizado = std::string(argv[i + 1]);
    }
  }

  Lattice reticulo(tamaño, tipo_de_frontera, temperatura_de_la_frontera);

  return reticulo;
}


int main (int argc, char *argv[]) {
  // Se necesitan al menos 4 argumentos para poder ejecutar el programa: -size <tamaño> -border <periodic|open>.
  if (argc <= 3) { Usage(argc, argv); }

  // Construimos el retículo con el que vamos a trabajar según los parámetros de línea de comandos introducidos por el usuario.
  Lattice reticulo = CommandLineArgs(argc, argv);
    
  //Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
  // std::cout << "Cargando datos desde el fichero dado como argumento" << std::endl;
  // strcpy(nombrefichero, argv[1]);
  
  char opcion;                // Variable donde guardaremos la opción a ser evaluada por el menú del programa
  int generacion_actual{0};   // Variable contadora de la generación en la que se encuentra el retículo

  do {
    Menu(opcion);
    std::cout << std::endl;
    switch (opcion) {
      // case ('c'): {
      //   system("clear");
      //   std::cout << "Introduce el nombre completo del fichero de datos" << std::endl;
      //   cin >> nombrefichero;
      //   G.actualizar(nombrefichero, error_apertura);
      //   if (error_apertura == 1) {
      //     std::cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << std::endl;
      //   }
      //   else {
      //     std::cout << std::endl;
      //     std::cout << "Fichero cargado correctamente desde " << nombrefichero << std::endl;
      //   }
      //   break;
      // }

      case ('a'): {      // Mostrar informacion basica del grafo
        system("clear");
        std::cout << "Generación: " << generacion_actual << " -> " << reticulo << std::endl << std::endl;
        break;
      }

      case ('g'): {      // Mostrar lista de sucesores del grafo
        system("clear");
        reticulo.nextGeneration();
        generacion_actual++;
        std::cout << "Generación: " << generacion_actual << " -> " << reticulo << std::endl << std::endl;
        break;
      }

      case ('i'): {      // Mostrar lista de predecesores del grafo
        system("clear");
        char caracter, caracter_salida;
        std::cout << "Pulse cualquier tecla alfanumérica para comenzar la secuencia de generaciones indefinidas, y 'x' para finalizarla." << std::endl << std::endl;
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
      
      case ('n'): {      // Mostrar matriz de adyacencia del grafo
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

      case ('v'): {      // Recorrido en amplitud
        system("clear");
        std::cout << "En la generación " << generacion_actual << " se encuentran vivas " << reticulo.AliveCells() << " células." << std::endl << std::endl;
        break;
      }

      case ('m'): {      // Recorrido en amplitud
        system("clear");
        std::cout << "En la generación " << generacion_actual << " se encuentran muertas " << reticulo.DeadCells() << " células." << std::endl << std::endl;
        break;
      }

      case ('q'): { break; }

      default: {
        system("clear");
        std::cout << std::endl << "Opción no valida, intentalo de nuevo" << std::endl << std::endl;
        break;
      }
    }
  } while (opcion != 'q');

  return 0;
}