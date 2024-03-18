/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 06: Problema del Viajante de Comercio (TSP)
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    21.mar.2023
 * @brief:   Framework para algoritmos de Programación Dinámica. Aqui se define la clase TSPBruta
 */

#include "bruta.h"

/**
 * @desc Applies a Brute Force algorithm for our complete TSP problem
 * @param {int} maxTime Time after which we want to halt execution and store current result (in seconds)
*/
void TSPBruta::solve(int maxTime) {
  auto start = high_resolution_clock::now();

  int minCost{INT_MAX}; // s = starting node
  std::vector<int> sequence;

  for (int i{0}; i < int(nodes_.size()); ++i) { // Add all node indexes to sequence
    sequence.push_back(i);
  }

  while(std::next_permutation(sequence.begin(), sequence.end())) {  // Iterate through all possible combinations of array
    if (duration_cast<seconds>(high_resolution_clock::now() - start).count() >= maxTime) {  // Over time limit
      time_ = -1;
      value_ = minCost;
      return;
    }
    int currentCost{0};
    for (int i{0}; i < int(sequence.size() - 1); ++i) { // Calculate cost of current sequence
      currentCost += nodes_[sequence[i]][sequence[(i+1)]];
    }
    currentCost += nodes_[sequence[sequence.size() - 1]][sequence[0]];  // Return to starting node
    minCost = std::min(minCost, currentCost);
	}

  auto end = high_resolution_clock::now();
  value_ = minCost;
  time_ = duration_cast<nanoseconds>(end - start).count();
}

/**
 * @desc Returns the value of value_ stored within the class
 * @returns {int} Value of value_
*/
int TSPBruta::getValue() {
  return value_;
}

/**
 * @desc Returns the value of time_ stored within the class
 * @returns {int} Value of time_
*/
int TSPBruta::getTime() {
  return time_;
}

/**
 * @desc Prints our the value of the chosen routew and the time it took
*/
void TSPBruta::printSolution() {
  std::cout << "Valor Fuerza Bruta: " << value_ << std::endl;
  std::cout << "Tiempo Fuerza Bruta (ns): " << time_ << std::endl;
}