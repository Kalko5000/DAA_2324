/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 05: Algoritmos de Divide y Vencerás
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    12.mar.2024
 * @brief:   Algoritmos de Divide y Vencerás
 */

// g++ --std=c++14 -o dyv sort.cc main.cc
// ./dyv

#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cctype>
#include "merge.h"

const int START_SIZE = 500; // Starting size of arrays to analyze
const int MAX_SIZE = 550; // Biggest size of arrays to analyze

/**
 * @desc Texto de ayuda para el correcto funcionamiento del código
*/
const void kHelpText() {
  std::cout << "dyv [1]" << std::endl << std::endl;
  std::cout << "Se generara un array aleatorio y se le pasara a un" << std::endl;
  std::cout << "algoritmo tipo divide y venceras, para medir su eficiencia" << std::endl;
  std::cout << "[1] = '1' para modo normal, '2' para modo debug" << std::endl;
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
  } else {
    kFuncText();
    exit(1);
  } 
}

/**
 * @desc Generates an array of random numbers between 1 and 1000 of a certain size
 * @param {int} size Size of resulting Array
 * @return {std::vector<int>} Randomly generated array
*/
std::vector<int> RandomArray(int size) {
  std::vector<int> randArray;
  for(int i{0}; i < size; ++i) {
    randArray.push_back(rand()%1000);
  }
  return randArray;
}

/**
 * @desc Prints a given Array
 * @param {std::vector<int>} array Array to be printed
*/
void printArray(std::vector<int> array) {
  for(int j{0}; j < int(array.size()); ++j) {
    std::cout << array[j] << " ";
  }
  std::cout << std::endl << std::endl;
}

/**
 * @desc Prints a table of all the times an algorithm took to sort an array of n size
 * @param {int} initialSize Size of smallest array
 * @param {std::vector<int>} mergeTimes Times for MergeSort algorithm
 * @param {std::vector<int>} quickTimes Times for QuickSort algorithm
*/
void printTable(int initialSize, std::vector<int> times) {
  std::cout << std::setw(6) << "N" << std::setw(16) << "Times (ns)" << std::endl;
  for (int i{}; i < int(times.size()); i++) {
    std::cout << std::setw(6) << initialSize + i << std::setw(16) << times[i] << std::endl;
  }
  std::cout << std::endl;
}

/**
 * @desc Prints the average value in an array, of a certain name
 * @param {std::vector<int>} times Array with values to average out
*/
void printAverage(std::vector<int> times) {
  int total = 0;
  for (int i{0}; i < int(times.size()); i++) {
    total += times[i];
  }
  total /= times.size();
  std::cout << "Average Time: " << total << "ns" << std::endl;
}

/**
 * @desc Prints a Hanoi Table for multiple instance sizes
*/
void printHanoiTable() {
  std::vector<int> times;  // Used for average
  int max{0}; // Used for deepest recurrence level
  int value{-1}; // Value to search for in Binary search

  for(int i{1}; i <= 10; ++i) {
    HanoiSolver<int> algorithm(i);
    std::vector<int> array = RandomArray(i);
    int ini{0};
    int fin{int(array.size() - 1)};
    array = {i};
    ini = 1;
    fin = 3;

    auto start = high_resolution_clock::now();
    algorithm.solve(array, ini, fin, value, 0);
    auto end = high_resolution_clock::now();
    float time = duration_cast<nanoseconds>(end - start).count();
    times.push_back(time);

    if (algorithm.getLevel() > max) max = algorithm.getLevel();
  }

  std::cout << "HANOI SOLVER" << std::endl;
  printTable(1, times);
  std::cout << "Recurrence Ecuation: " << HanoiSolver<int>(1).recurrence() << std::endl;
  printAverage(times);
  std::cout << "Highest Depth Reached: " << max << std::endl;
}

/**
 * @desc Prints results as a table for various executions of an algorithm
 * @param {Sort<int>*} algorithm Algorithm to use
 * @param {std::string} name Name of the algorithm 
*/
void printResults(Solution<int>* algorithm, std::string name) {
  std::vector<int> times;  // Used for average
  int max{0}; // Used for deepest recurrence level
  int value{-1}; // Value to search for in Binary search

  for(int i{START_SIZE}; i <= MAX_SIZE; ++i) {
    std::vector<int> array = RandomArray(i);
    if (name == "BINARY SEARCH") { // If binary search, sort array and add value to search for
      value = RandomArray(1)[0];
      QuickSort<int> tempSort;
      tempSort.solve(array, 0, array.size()-1, -1, 0);
    }

    auto start = high_resolution_clock::now();
    algorithm->solve(array, 0, int(array.size() - 1), value, 0);
    auto end = high_resolution_clock::now();
    float time = duration_cast<nanoseconds>(end - start).count();
    times.push_back(time);

    if (algorithm->getLevel() > max) max = algorithm->getLevel();
  }

  std::cout << name << std::endl;
  printTable(START_SIZE, times);
  std::cout << "Recurrence Ecuation: " << algorithm->recurrence() << std::endl;
  printAverage(times);
  std::cout << "Highest Depth Reached: " << max << std::endl;
}

/**
 * @desc Prints a single result from an algorithm execution, used for debug mode
 * @param {Sort<int>*} algorithm Algorithm to use
 * @param {std::string} name Name of the algorithm 
*/
void printSingleResult(Solution<int>* algorithm, std::string name) {
  int value{-1}; // Value to search for in Binary search
  std::cout << "Introduzca el tamaño del problema: ";
  int size{0};
  std::cin >> size;
  std::vector<int> array = RandomArray(size);
  int ini{0};
  int fin{int(array.size() - 1)};
  if (name == "HANOI SOLVER") {
    array = {size};
    ini = 1;
    fin = 3;
  } else {
    std::cout << std::endl << "Random Array size [" << size << "]: " << std::endl;
    printArray(array);
  }
  if (name == "BINARY SEARCH") { // If binary search, sort array and add value to search for
    value = RandomArray(1)[0];
    QuickSort<int> tempSort;
    tempSort.solve(array, 0, array.size()-1, -1, 0);
  }

  auto start = high_resolution_clock::now();
  algorithm->solve(array, ini, fin, value, 0);
  auto end = high_resolution_clock::now();
  float time = duration_cast<nanoseconds>(end - start).count();

  std::cout << name << " solution: " << std::endl;
  printArray(array);
  algorithm->printExtraResult();

  std::cout << "Time taken: " << time << "ns" << std::endl;
  std::cout << "Max Depth in Instance: " << algorithm->getLevel() << std::endl;
}

int main(int argc, char* argv []) {
  srand(time(0)); // Random Seed, to generate random numbers later
  Usage(argc, argv);
  int modo = std::stoi(argv[1]);
  bool debug{false};
  if (modo == 2) debug = true;

  bool validInput{false};
  while (!validInput) {
    std::cout << "Introduzca algoritmo (0: MergeSort, 1: QuickSort, 2: BinarySearch, 3: HanoiSolver): ";
    int input{0};
    std::cin >> input;
    switch (input) {
      case 0:
        if (!debug) printResults(new MergeSort<int>(), "MERGESORT");
        else printSingleResult(new MergeSort<int>(), "MERGESORT");
        validInput = true;
        break;
      case 1:
        if (!debug) printResults(new QuickSort<int>(), "QUICKSORT");
        else printSingleResult(new QuickSort<int>(), "QUICKSORT");
        validInput = true;
        break;
      case 2:
        if (!debug) printResults(new BinarySearch<int>(), "BINARY SEARCH");
        else printSingleResult(new BinarySearch<int>(), "BINARY SEARCH");
        validInput = true;
        break;
      case 3:
        if (!debug) printHanoiTable();
        else printSingleResult(new HanoiSolver<int>(1), "HANOI SOLVER");
        validInput = true;
        break;
      default:
        std::cout << "Algoritmo no válido, vuelva a intentar" << std::endl;
        break;
    }
  }
  return 0;
}