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
 * @brief:   Framework para algoritmos de Programación Dinámica. Aqui se define la clase TSPDinamica
 */

#include "dinamica.h"

/**
 * @desc Applies a top-down Dynamic Programming algorithm for our complete TSP problem
 * @param {int} maxTime Time after which we want to halt execution and store current result (in seconds)
*/
void TSPDinamica::solve(int maxTime) {
  auto start = high_resolution_clock::now();
  int ans{0};
  startTime_ = start;
  maxTime_ = maxTime;
  
  std::vector<std::vector<int>> state(int(nodes_.size()));
  for(auto& neighbors : state) {
    neighbors = std::vector<int>((1 << int(nodes_.size())) - 1, INT_MAX);
  }
  try {
    ans = recursiveSolve(0, 1, state);
  } catch (const int value) { // Gone over time
    time_ = -1;
    value_ = value;
    return;
  }

  auto end = high_resolution_clock::now();
  value_ = ans;
  time_ = duration_cast<nanoseconds>(end - start).count();
}

/**
 * @desc Recursive method for our top-down Dynamic Programming complete TSP solver
 * @param {int} pos Node the algorithm is positioned on, the one we will evaluate
 * @param {int} visited Used to keep track of which nodes have been visited (bitmask)
 * @param {std::vector<std::vector<int>>&} state Memoization table where we store the minimum computed values so far
 * @returns {int} Minimum distance to visit all unvisited nodes from pos
*/
int TSPDinamica::recursiveSolve(int pos, int visited, std::vector<std::vector<int>>& state) {
  if (duration_cast<seconds>(high_resolution_clock::now() - startTime_).count() >= maxTime_) {  // Over time limit
    throw(state[pos][visited]);
  }
  
  if(visited == ((1 << nodes_.size()) - 1)) {
    return nodes_[pos][0]; // return to starting node
  }

  if(state[pos][visited] != INT_MAX) {  // Checks if from pos to visited has already been computed
    return state[pos][visited];
  }

  for(int i = 0; i < int(nodes_.size()); ++i) {
    // can't visit ourselves unless we're ending & skip if already visited
    if(i == pos || (visited & (1 << i))) continue;
    int distance = nodes_[pos][i] + recursiveSolve(i, visited | (1 << i), state); // Min distance from every node after current
    if(distance < state[pos][visited]) { 
      state[pos][visited] = distance;
    }
  }

  return state[pos][visited];
}

/**
 * @desc Returns the value of value_ stored within the class
 * @returns {int} Value of value_
*/
int TSPDinamica::getValue() {
  return value_;
}

/**
 * @desc Returns the value of time_ stored within the class
 * @returns {int} Value of time_
*/
int TSPDinamica::getTime() {
  return time_;
}

/**
 * @desc Prints our the value of the chosen route and the time it took
*/
void TSPDinamica::printSolution() {
  std::cout << "Valor Prog Dinámica: " << value_ << std::endl;
  std::cout << "Tiempo Prog Dinámica (ns): " << time_ << std::endl;
}