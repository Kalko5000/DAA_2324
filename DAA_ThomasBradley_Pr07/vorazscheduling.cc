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
 * @brief:   Program that solves titular problem. Here we define the VorazScheduling class
 */

#include "vorazscheduling.h"

/**
 * @desc Applies a Greedy algorithm for our complete TSP problem
 * @param {int} maxTime Time after which we want to halt execution and store current result (in seconds)
*/
void VorazScheduling::solve(int maxTime) {
  auto start = high_resolution_clock::now();

  std::vector<int> visitedRouteList(nodes_.size(), 0);
  visitedRouteList[0] = 1;  // Starting node = 0
  int current{0}, sum{0};   // ^
  path_.push_back(current); // ^
  for (int i{0}; i < int(nodes_.size() - 1); ++i) { // Visit every node
    if (duration_cast<seconds>(high_resolution_clock::now() - start).count() >= maxTime) {  // Over time limit
      time_ = -1;
      value_ = sum;
      return;
    }
    int min{INT_MAX}, minIndex{0};
    for (int j{0}; j < int(nodes_.size()); ++j) { // Find min node that hasn't been visited yet (from current)
      if (nodes_[current][j] < min && visitedRouteList[j] == 0) {
        min = nodes_[current][j];
        minIndex = j;
      }
    }
    sum += min;
    visitedRouteList[minIndex] = 1;
    current = minIndex;
    path_.push_back(minIndex);  // Update path
  }
  sum += nodes_[current][0];  // Return to beginning

  auto end = high_resolution_clock::now();
  value_ = sum;
  time_ = duration_cast<nanoseconds>(end - start).count();
}

/**
 * @desc Returns the value of value_ stored within the class
 * @returns {int} Value of value_
*/
int VorazScheduling::getValue() {
  return value_;
}

/**
 * @desc Returns the value of time_ stored within the class
 * @returns {int} Value of time_
*/
int VorazScheduling::getTime() {
  return time_;
}

/**
 * @desc Prints our the value of the chosen route and the time it took
*/
void VorazScheduling::printSolution() {
  std::cout << "Valor Voraz: " << value_ << std::endl;
  std::cout << "Tiempo Voraz (ns): " << time_ << std::endl;
}