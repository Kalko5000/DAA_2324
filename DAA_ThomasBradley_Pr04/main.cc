/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 04: Framework para algoritmos de Divide y Vencerás
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    05.mar.2024
 * @brief:   Framework para algoritmos de Divide y Vencerás
 */

// g++ --std=c++14 -o dyv sort.cc main.cc
// ./dyv

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "sort.h"

using namespace std::chrono;

/**
 * @desc Texto de ayuda para el correcto funcionamiento del código
*/
const void kHelpText() {
  std::cout << "dyv" << std::endl << std::endl;
  std::cout << "Se generara un array aleatorio de varios tamaños y se le pasara por distintos" << std::endl;
  std::cout << "algoritmos tipo divide y venceras, para comparar su eficiencia" << std::endl;
}

/**
 * @desc Texto de como usar el programa y como encontrar más información sobre ella
*/
const void kFuncText() {
  std::cout << "Modo de empleo: dyv" << std::endl;
  std::cout << "Pruebe 'dyv --help' para más información" << std::endl;
}

/**
 * @desc Analiza los valores pasados por la linea de comandos
 * @param {int} kArgc número de comandos pasados
 * @param {int} argv[] array con el texto pasado por linea de comandos
*/
void Usage(const int kArgc, char* argv[]) {
  if (kArgc == 2) {
    if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
      kHelpText();
      exit(0);
    }
  }
  if (kArgc != 1) {
    kFuncText();
    exit(1);
  } 
}

std::vector<int> RandomArray(int size) {
  std::vector<int> randArray;
  srand((unsigned) time(NULL));
  for(int i{0}; i < size; ++i) {
    randArray.push_back(rand()%100);
  }
  return randArray;
}

void printSortedArray(std::vector<int> array) {
  std::vector<int> array_copy = array;

  MergeSort mergesort;
  auto start = high_resolution_clock::now();
  mergesort.sort(array, 0, array.size()-1);
  auto end = high_resolution_clock::now();
  std::cout << "Mergesort(ns: " << duration_cast<nanoseconds>(end - start).count() << "): ";
  for(int j{0}; j < int(array.size()); ++j) {
    std::cout << array[j] << " ";
  }

  QuickSort quickSort;
  start = high_resolution_clock::now();
  // quickSort.sort(array_copy, 0, array_copy.size()-1);
  end = high_resolution_clock::now();
  std::cout << std::endl << "Quicksort(ns: " << duration_cast<nanoseconds>(end - start).count() << "): ";
  for(int j{0}; j < int(array_copy.size()); ++j) {
    std::cout << array_copy[j] << " ";
  }

  std::cout << std::endl;
}

int main(int argc, char* argv []) {
  Usage(argc, argv);
  for(int i{1}; i < 11; ++i) {
    std::vector<int> array = RandomArray(i);
    std::cout << "Random Array size [" << i << "]: ";
    for(int j{0}; j < int(array.size()); ++j) {
      std::cout << array[j] << " ";
    }
    std::cout << std::endl;
    printSortedArray(array);
    if(i != 10) std::cout << std::endl;
  }

  return 0;
}