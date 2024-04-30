/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 08: B&B - Maximum Diversity Problem
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    21.apr.2024
 * @brief:   Main program to solve the problem at hand
 * @example: ./diversity node_files
 */

// g++ --std=c++14 -o diversity solution.cc vorazsolution.cc graspsolution.cc main.cc

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
#include "graspsolution.h"

using namespace std::chrono;

/** @desc Texto de ayuda para el correcto funcionamiento del código */
const void kHelpText() {
  std::cout << "diversity [1]" << std::endl << std::endl;
  std::cout << "[1] - Nombre del directorio donde se encuentran los ficheros MDP, no se debe poner '/' al final de este" << std::endl << std::endl;
  std::cout << "Se leeran todos los ficheros en el directorio pasado para que luego imprimir " << std::endl;
  std::cout << "una tabla con todos los valores obtenidos y los tiempos de ejecución de cada algoritmo " << std::endl;
  std::cout << "en cada fichero." << std::endl;
}

/** @desc Texto de como usar el programa y como encontrar más información sobre ella */
const void kFuncText() {
  std::cout << "Modo de empleo: diversity [DIRECTORIO]" << std::endl;
  std::cout << "Pruebe 'diversity --help' para más información" << std::endl;
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

/**
 * @desc Prints a Greedy execution of the sorting algorithm with a list of files
 * @param {std::vector<std::pair<std::string, std::string>>} files A list of files locations and names
 * @param {int} m Number of points to include in solution
*/
void printVoraz(std::vector<std::pair<std::string, std::string>> files, int m) {
  int counter{1};
  std::cout << "-- VORAZ --" << std::endl;
  std::cout << std::setw(20) << "Problema" << std::setw(5) 
  << "n" << std::setw(5) << "k" << std::setw(5) << "m" << std::setw(11) << "z" 
  << std::setw(32) << "s" << std::setw(15) << "CPU(ms)" << std::endl;

  for (int i{0}; i < int(files.size()); ++i) {
    VorazSolution voraz(files[i].first);
    auto start = std::chrono::high_resolution_clock::now();
    float distance = voraz.evaluate(m);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << std::setw(20) << std::string(files[i].second) << std::setw(5) 
    << voraz.getSize() << std::setw(5) << voraz.getDimension() << std::setw(5) 
    << m << std::setw(11) << distance << std::setw(32) << voraz.getS() << std::setw(15)
    << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    counter++;
  }
  std::cout << std::endl;
}

/**
 * @desc Prints a Greedy execution of the sorting algorithm with a list of files
 * @param {std::vector<std::pair<std::string, std::string>>} files A list of files locations and names
 * @param {int} m Number of points to include in solution
*/
void printGrasp(std::vector<std::pair<std::string, std::string>> files, int candidates, int m) {
  int counter{1};
  std::cout << "-- GRASP --" << std::endl;
  std::cout << std::setw(20) << "Problema" << std::setw(5) 
  << "n" << std::setw(5) << "k" << std::setw(5) << "m" << std::setw(7) << "|LRC|" << std::setw(11) << "z" 
  << std::setw(32) << "s" << std::setw(15) << "CPU(ms)" << std::endl;

  for (int i{0}; i < int(files.size()); ++i) {
    GraspSolution grasp(files[i].first, candidates);
    auto start = std::chrono::high_resolution_clock::now();
    float distance = grasp.evaluate(m);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << std::setw(20) << std::string(files[i].second) << std::setw(5) 
    << grasp.getSize() << std::setw(5) << grasp.getDimension() << std::setw(5) 
    << m << std::setw(7) << grasp.getCandidateSize() << std::setw(11) << distance << std::setw(32) 
    << grasp.getS() << std::setw(15)
    << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    counter++;
  }
  std::cout << std::endl;
}

/**
 * @desc Compares the second string of two pairs and returns true if the first is smaller
 * @param {std::pair<std::string, std::string> } string01 First pair of strings to check second value of
 * @param {std::pair<std::string, std::string> } string02 Second pair of strings to check second value of
 * @returns {bool} True if first paramater is smaller
*/
bool stringPairCompare(std::pair<std::string, std::string> string01, std::pair<std::string, std::string> string02) { 
  return string01.second < string02.second; 
}

int main(int argc, char* argv []) {
  Usage(argc, argv);
  char* directoryPath = new char[std::strlen(argv[1]) + std::strlen("/")];  // Set length to be correct, so we can add necesarry elements
  std::strcpy(directoryPath, argv[1]);
  std::strcat(directoryPath, "/");

  // Open the directory
  DIR* dir = opendir(directoryPath);
  if (dir == nullptr) {
    std::cerr << "Error opening directory\n";
    return 1;
  }

  std::vector<std::pair<std::string, std::string>> files{};
  dirent* entry;
  while ((entry = readdir(dir)) != nullptr) { // Read the directory entries
    if (std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0) {  // Filter out "." and ".."
      std::string nombre_fichero = directoryPath + std::string(entry->d_name);
      files.push_back(std::pair<std::string, std::string>({nombre_fichero, entry->d_name}));
    }
  }
  closedir(dir);
  std::sort(files.begin(),files.end(), stringPairCompare);  // Sort files by unicode order

  printVoraz(files, 2);
  printVoraz(files, 3);
  printVoraz(files, 4);

  printGrasp(files, 3, 2);
  printGrasp(files, 3, 3);
  printGrasp(files, 3, 4);

  return 0;
}
