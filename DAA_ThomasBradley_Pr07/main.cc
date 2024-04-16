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
#include "gvnssolution.h"

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

/**
 * @desc Prints a Greedy execution of the sorting algorithm with a list of files
 * @param {std::vector<std::pair<std::string, std::string>>} files A list of files locations and names
*/
void printVoraz(std::vector<std::pair<std::string, std::string>> files) {
  int counter{1};
  std::cout << "-- VORAZ --" << std::endl;
  std::cout << std::setw(20) << "Problema" << std::setw(5) 
  << "n" << std::setw(5) << "m" << std::setw(12) << "Ejecución" << std::setw(10) << "TCT" 
  << std::setw(15) << "CPU(ms)" << std::endl;

  for (int i{0}; i < int(files.size()); ++i) {
    VorazSolution voraz(files[i].first);
    auto start = std::chrono::high_resolution_clock::now();
    int VorTCT = voraz.evaluate();
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << std::setw(20) << std::string(files[i].second) << std::setw(5) 
    << voraz.getTasks() << std::setw(5) << voraz.getMachines() << std::setw(11) 
    << counter << std::setw(10) << VorTCT << std::setw(15) 
    << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    counter++;
  }
  std::cout << std::endl;
}

/**
 * @desc Prints a Greedy execution of the sorting algorithm with a list of files
 * @param {std::vector<std::pair<std::string, std::string>>} files A list of files locations and names
 * @param {int} candidates How many candidates GRASP's constructive phase will use
*/
void printGrasp(std::vector<std::pair<std::string, std::string>> files, int candidates) {
  int counter{1};
  std::cout << "-- GRASP --" << std::endl;
  std::cout << std::setw(20) << "Problema" << std::setw(5) 
  << "n" << std::setw(5) << "m" << std::setw(7) << "|LRC|" 
  << std::setw(12) << "Ejecución" << std::setw(10) << "TCT" << std::setw(15) << "CPU(ms)" << std::endl;

  for (int i{0}; i < int(files.size()); ++i) {
    GraspSolution grasp(files[i].first, candidates);
    auto startGrasp = std::chrono::high_resolution_clock::now();
    int GraspTCT = grasp.evaluate();
    auto endGrasp = std::chrono::high_resolution_clock::now();
    
    std::cout << std::setw(20) << std::string(files[i].second) << std::setw(5) 
    << grasp.getTasks() << std::setw(5) << grasp.getMachines() << std::setw(11) << std::setw(7) << grasp.getCandidateSize()
    << std::setw(11) << counter << std::setw(10) << GraspTCT << std::setw(15) 
    << std::chrono::duration_cast<std::chrono::microseconds>(endGrasp - startGrasp).count() << std::endl;
    counter++;
  }
  std::cout << std::endl;
}

/**
 * @desc Prints a Greedy execution of the sorting algorithm with a list of files
 * @param {std::vector<std::pair<std::string, std::string>>} files A list of files locations and names
 * @param {int} candidates How many candidates GRASP's constructive phase will use
 * @param {int} k Maximum value of k in GVNS algorithm
*/
void printGvns(std::vector<std::pair<std::string, std::string>> files, int candidates, int k) {
  int counter{1};
  std::cout << "-- GVNS --" << std::endl;
  std::cout << std::setw(20) << "Problema" << std::setw(5) 
  << "n" << std::setw(5) << "m" << std::setw(7) << "|LRC|" << std::setw(7) << "kMax" 
  << std::setw(12) << "Ejecución" << std::setw(10) << "TCT" << std::setw(15) << "CPU(ms)" << std::endl;

  for (int i{0}; i < int(files.size()); ++i) {  
    GvnsSolution gvns(files[i].first, candidates, k);
    auto startGvns = std::chrono::high_resolution_clock::now();
    int GvnsTCT = gvns.evaluate();
    auto endGvns = std::chrono::high_resolution_clock::now();
    
    std::cout << std::setw(20) << std::string(files[i].second) << std::setw(5) 
    << gvns.getTasks() << std::setw(5) << gvns.getMachines() << std::setw(11) << std::setw(7) 
    << gvns.getCandidateSize() << std::setw(7) << gvns.getKMax()
    << std::setw(11) << counter << std::setw(10) << GvnsTCT << std::setw(15)
    << std::chrono::duration_cast<std::chrono::microseconds>(endGvns - startGvns).count() << std::endl;
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

  printVoraz(files);
  printGrasp(files, 2);
  printGrasp(files, 3);
  printGrasp(files, 4);
  printGvns(files, 2, 3);
  printGvns(files, 4, 6);

  return 0;
}
