/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 07: Parallel Machine Scheduling Problem with Dependent Setup Times
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    02.apr.2024
 * @brief:   Main program to solve the problem at hand
 * @example: ./machine tests
 */

// g++ --std=c++14 -o machine scheduling.cc vorazscheduling.cc main.cc

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
#include "vorazscheduling.h"

using namespace std::chrono;

/** @desc Texto de ayuda para el correcto funcionamiento del código */
const void kHelpText() {
  std::cout << "machine [1]" << std::endl << std::endl;
  std::cout << "[1] - Nombre del directorio donde se encuentran los ficheros PML, no se debe poner '/' al final de este" << std::endl << std::endl;
  std::cout << "Se leeran todos los ficheros en el directorio pasado para que luego imprimir " << std::endl;
  std::cout << "una tabla con todos los valores obtenidos y los tiempos de ejecución de cada algoritmo " << std::endl;
  std::cout << "en cada fichero. Estos algoritmos siendo: voraz y GRASP" << std::endl;
}

/** @desc Texto de como usar el programa y como encontrar más información sobre ella */
const void kFuncText() {
  std::cout << "Modo de empleo: machine [DIRECTORIO]" << std::endl;
  std::cout << "Pruebe 'machine --help' para más información" << std::endl;
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
    } 
  } else {
    kFuncText();
    exit(1);
  }
}

int main(int argc, char* argv []) {
  Usage(argc, argv);
  char* directoryPath = new char[std::strlen(argv[1]) + std::strlen("/")];  // Set length to be correct, so we can add necesarry elements
  std::strcpy(directoryPath, argv[1]);
  std::strcat(directoryPath, "/");

  // Results header
  std::cout << std::setw(20) << "Problema" << std::setw(5) <<
  "n" << std::setw(5) << "m" << std::setw(12) << "Ejecución" << std::setw(10) <<
  "TCT" << std::setw(15) << "CPU" << std::endl;

  // Open the directory
  DIR* dir = opendir(directoryPath);
  if (dir == nullptr) {
    std::cerr << "Error opening directory\n";
    return 1;
  }

  int counter{1};
  dirent* entry;
  while ((entry = readdir(dir)) != nullptr) { // Read the directory entries
    if (std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0) {  // Filter out "." and ".."
      std::string nombre_fichero = directoryPath + std::string(entry->d_name);
      VorazScheduling voraz(nombre_fichero);
      auto start = std::chrono::high_resolution_clock::now();
      voraz.evaluate();
      auto end = std::chrono::high_resolution_clock::now();
      
      std::cout << std::setw(20) << std::string(entry->d_name) << std::setw(5) <<
      voraz.getTasks() << std::setw(5) << voraz.getMachines() << std::setw(11) << counter << std::setw(10) <<
      voraz.getTCT() << std::setw(15) << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;

      counter++;
    }
  }

  closedir(dir);
  return 0;
}