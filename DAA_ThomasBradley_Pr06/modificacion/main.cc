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
 * @example: ./tsp
 */

// g++ --std=c++14 -o tsp tsp.cc main.cc

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
  std::cout << "tsp" << std::endl << std::endl;
  std::cout << "Se leeran todos los ficheros en el directorio ./grafos para que luego imprimir " << std::endl;
  std::cout << "una tabla con todos los valores obtenidos y los tiempos de ejecución de cada algoritmo " << std::endl;
  std::cout << "en cada fichero. Estos algoritmos siendo: fuerza bruta, programación dinámica y voraz" << std::endl;
}

/** @desc Texto de como usar el programa y como encontrar más información sobre ella */
const void kFuncText() {
  std::cout << "Modo de empleo: tsp" << std::endl;
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

double average(std::vector<double> arr) {
  double total = 0.0;
  for (int i{0}; i < int(arr.size()); i++) {
    total += arr[i];
  }
  total /= arr.size();
  return total;
}

int main(int argc, char* argv []) {
  Usage(argc, argv);
  const int maxTime = 5; // Set to 5 seconds, for 5 minutes -> maxTime = 300;
  const char* directory_path = "./grafos/";
  std::vector<double> brutaVal, vorazVal, dinamicaVal;
  std::vector<double> brutaTemp, vorazTemp, dinamicaTemp;

  // Results header
  std::cout << std::setw(15) << "Fichero" << std::setw(15) <<
  "Valor FB" << std::setw(20) << "Tiempo(ns) FB" << std::setw(15) <<
  "Valor PD" << std::setw(20) << "Tiempo(ns) PD" << std::setw(15) <<
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
      bruta.solve(maxTime);
      brutaVal.push_back(bruta.getValue());
      std::string brutaTime = ((bruta.getTime() >= 0) ? std::to_string(bruta.getTime()) : "EXCESIVO");
      if (brutaTime != "EXCESIVO") {
        brutaTemp.push_back(bruta.getTime());
      } else {
        brutaTemp.push_back(maxTime * 1e+9);
      }
      TSPVoraz voraz(nombre_fichero);
      voraz.solve(maxTime);
      vorazVal.push_back(voraz.getValue());
      std::string vorazTime = ((voraz.getTime() >= 0) ? std::to_string(voraz.getTime()) : "EXCESIVO");
      if (vorazTime != "EXCESIVO") {
        vorazTemp.push_back(voraz.getTime());
      } else {
        vorazTemp.push_back(maxTime * 1e+9);
      }
      TSPDinamica dinamica(nombre_fichero);
      dinamica.solve(maxTime);
      dinamicaVal.push_back(dinamica.getValue());
      std::string dinamicaTime = ((dinamica.getTime() >= 0) ? std::to_string(dinamica.getTime()) : "EXCESIVO");
      if (dinamicaTime != "EXCESIVO") {
        dinamicaTemp.push_back(dinamica.getTime());
      } else {
        dinamicaTemp.push_back(maxTime * 1e+9);
      }

      // Results for this file
      std::cout << std::setw(15) << entry->d_name << std::setw(15) <<
      bruta.getValue() << std::setw(20) << brutaTime << std::setw(15) <<
      dinamica.getValue() << std::setw(20) << dinamicaTime << std::setw(15) <<
      voraz.getValue() << std::setw(20) << vorazTime << std::endl;
    }
  }

  // Results for this file
  std::cout << std::setw(15) << "MEDIA" << std::setw(15) <<
  average(brutaVal) << std::setw(20) << average(brutaTemp) << std::setw(15) <<
  average(dinamicaVal) << std::setw(20) << average(dinamicaTemp) << std::setw(15) <<
  average(vorazVal) << std::setw(20) << average(vorazTemp) << std::endl;

  closedir(dir);
  return 0;
}