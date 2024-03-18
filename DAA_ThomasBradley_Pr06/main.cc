/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 06: Problema del Viajante de Comercio (TSP)
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    19.mar.2024
 * @brief:   Framework para algoritmos de Programación Dinámica
 */

// g++ --std=c++14 -o tsp tsp.cc main.cc
// ./tsp 4_nodos.txt

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <dirent.h>
#include <cstring>
#include "bruta.h"

using namespace std::chrono;

/** @desc Texto de ayuda para el correcto funcionamiento del código */
const void kHelpText() {
  std::cout << "tsp [1]" << std::endl << std::endl;
  std::cout << "[1]: Fichero de entrada." << std::endl;
  std::cout << "Se leera un fichero de entrada que especifique cuantos nodos tendra el problema " << std::endl;
  std::cout << "y a continuación lista las distancias entre todos estos. Tras esto se resolvera " << std::endl;
  std::cout << "por tres medios distintos: por fuerza bruta, con un algoritmo voraz y con programación dinámica" << std::endl;
}

/** @desc Texto de como usar el programa y como encontrar más información sobre ella */
const void kFuncText() {
  std::cout << "Modo de empleo: tsp [FICHERO]" << std::endl;
  std::cout << "Pruebe 'tsp --help' para más información" << std::endl;
}

/**
 * @desc Analiza los valores pasados por la linea de comandos
 * @param {int} kArgc número de comandos pasados
 * @param {int} argv[] array con el texto pasado por linea de comandos
 * @return {void}
*/
void Usage(const int kArgc, char* argv[]) {
  if (kArgc == 2) {
    if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
      kHelpText();
      exit(0);
    } else {
      kFuncText();
      exit(1);
    }
  } else if (kArgc != 1) {
    kFuncText();
    exit(1);
  }
}

int main(int argc, char* argv []) {
  Usage(argc, argv);
  const char* directory_path = "./grafos/";

  std::cout << std::setw(15) << "Fichero" << std::setw(20) <<
  "Valor FB" << std::setw(20) << "Tiempo(ns) FB" << std::setw(20) <<
  "Valor PD" << std::setw(20) << "Tiempo(ns) PD" << std::setw(20) <<
  "Valor V" << std::setw(20) << "Tiempo(ns) V" << std::endl;

  // Open the directory
  DIR* dir = opendir(directory_path);
  if (dir == nullptr) {
    std::cerr << "Error opening directory\n";
    return 1;
  }

  dirent* entry;
  while ((entry = readdir(dir)) != nullptr) { // Read the directory entries
    if (std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0) {  // Filter out "." and ".."
      std::string nombre_fichero = directory_path + std::string(entry->d_name);
      TSPBruta bruta(nombre_fichero);
      bruta.solve();
      TSPVoraz voraz(nombre_fichero);
      voraz.solve();
      TSPDinamica dinamica(nombre_fichero);
      dinamica.solve();

      std::cout << std::setw(15) << entry->d_name << std::setw(20) <<
      bruta.getValue() << std::setw(20) << bruta.getTime() << std::setw(20) <<
      dinamica.getValue() << std::setw(20) << dinamica.getTime() << std::setw(20) <<
      voraz.getValue() << std::setw(20) << voraz.getTime() << std::endl;
    }
  }

  closedir(dir);
  return 0;
}

// 5 minutes = 300,000,000,000ns