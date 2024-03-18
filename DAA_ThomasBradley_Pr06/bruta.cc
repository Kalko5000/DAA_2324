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

  int s{0};
  std::vector<int> vertex;
  for (int i{0}; i < int(nodes_.size()); ++i) {
    if (i != s) vertex.push_back(i);
  }
  int min_cost{std::numeric_limits<int>::max()};
  while(std::next_permutation(vertex.begin(), vertex.end())) {
    auto mid = high_resolution_clock::now();
    // std::cout << duration_cast<seconds>(mid - start).count() << std::endl;
    if (duration_cast<seconds>(mid - start).count() >= maxTime) {  // Over time limit
      time_ = -1;
      value_ = min_cost;
      return;
    }
    int current_cost{0}, j{s};
    for (int i{0}; i < int(vertex.size()); ++i) {
      current_cost += nodes_[j][vertex[i]];
      j = vertex[i];
    }
    current_cost += nodes_[j][s];
    min_cost = std::min(min_cost, current_cost);
	}

  auto end = high_resolution_clock::now();
  value_ = min_cost;
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