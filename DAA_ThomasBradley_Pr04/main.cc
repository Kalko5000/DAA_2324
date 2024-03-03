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

#include <fstream>
#include <string>
#include "sort.h"

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

/**
 * @desc Generates an array of random numbers between 1 and 100 of a certain size
 * @param {int} size Size of resulting Array
 * @return {std::vector<int>} Randomly generated array
*/
std::vector<int> RandomArray(int size) {
  std::vector<int> randArray;
  for(int i{0}; i < size; ++i) {
    randArray.push_back(rand()%100);
  }
  return randArray;
}

/**
 * @desc Prints a given Array
 * @param {std::vector<int>} array Array to be printed
*/
void printArray(std::vector<int> array) {
  std::cout << "Random Array size [" << array.size() << "]: ";
  for(int j{0}; j < int(array.size()); ++j) {
    std::cout << array[j] << " ";
  }
  std::cout << std::endl;
}

/**
 * @desc Prints the average value in an array, of a certain name
 * @param {std::vector<int>} times Array with values to average out
 * @param {string} name Name given to the array, to be displayed on screen
*/
void printAverage(std::vector<int> times, string name) {
  int total = 0;
  for (int i{0}; i < int(times.size()); i++) {
    total += times[i];
  }
  total /= times.size();
  std::cout << name << " average: " << total << "ns" << std::endl;
}

int main(int argc, char* argv []) {
  srand(time(0)); // Random Seed, to generate random numbers later
  Usage(argc, argv);
  const int MAX_SIZE = 15; // Biggest size of arrays to analyze
  std::vector<int> mergeTimes;
  std::vector<int> quickTimes;

  for(int i{1}; i <= MAX_SIZE; ++i) {
    std::vector<int> array = RandomArray(i);
    printArray(array);

    MergeSort mergesort;
    mergeTimes.push_back(mergesort.print(array, "Mergesort"));
    QuickSort quicksort;
    quickTimes.push_back(quicksort.print(array, "Quicksort"));
    std::cout << std::endl;
  }

  printAverage(mergeTimes, "Mergesort");
  printAverage(quickTimes, "Quicksort");

  return 0;
}