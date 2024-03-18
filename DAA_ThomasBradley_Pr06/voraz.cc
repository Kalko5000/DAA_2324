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
 * @brief:   Framework para algoritmos de Programación Dinámica. Aqui se define la clase TSPVoraz
 */

#include "voraz.h"

/**
 * @desc Applies a Greedy algorithm for our complete TSP problem
 * @param {int} maxTime Time after which we want to halt execution and store current result (in seconds)
*/
void TSPVoraz::solve(int maxTime) {
  auto start = high_resolution_clock::now();

  std::vector<int> visitedRouteList(nodes_.size(), 0);
  visitedRouteList[0] = 1;  // Starting from the first node
  int current{0}, sum{0};
  for (int i{0}; i < int(nodes_.size() - 1); ++i) {
    int min{INT_MAX}, minIndex{0};
    for (int j{0}; j < int(nodes_.size()); ++j) { // Find min node that hasn't been visited yet
      if (nodes_[current][j] < min && visitedRouteList[j] == 0) {
        min = nodes_[current][j];
        minIndex = j;
      }
    }
    sum += min;
    visitedRouteList[minIndex] = 1;
    current = minIndex;
  }
  sum += nodes_[current][0];

  auto end = high_resolution_clock::now();
  value_ = sum;
  time_ = duration_cast<nanoseconds>(end - start).count();
}

/**
 * @desc Returns the value of value_ stored within the class
 * @returns {int} Value of value_
*/
int TSPVoraz::getValue() {
  return value_;
}

/**
 * @desc Returns the value of time_ stored within the class
 * @returns {int} Value of time_
*/
int TSPVoraz::getTime() {
  return time_;
}

/**
 * @desc Prints our the value of the chosen route and the time it took
*/
void TSPVoraz::printSolution() {
  std::cout << "Valor Voraz: " << value_ << std::endl;
  std::cout << "Tiempo Voraz (ns): " << time_ << std::endl;
}