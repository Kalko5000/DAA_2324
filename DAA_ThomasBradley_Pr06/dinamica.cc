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

int TSPDinamica::recursiveSolve(int pos, int visited, std::vector<std::vector<int>>& state) {
  auto mid = high_resolution_clock::now();
  // std::cout << duration_cast<seconds>(mid - start).count() << std::endl;
  if (duration_cast<seconds>(mid - startTime_).count() >= maxTime_) {  // Over time limit
    throw(state[pos][visited]);
  }
  
  if(visited == ((1 << nodes_.size()) - 1)) {
    return nodes_[pos][0]; // return to starting node
  }

  if(state[pos][visited] != INT_MAX) {
    return state[pos][visited];
  }

  for(int i = 0; i < int(nodes_.size()); ++i) {
    // can't visit ourselves unless we're ending & skip if already visited
    if(i == pos || (visited & (1 << i))) continue;
    int distance = nodes_[pos][i] + recursiveSolve(i, visited | (1 << i), state);
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
 * @desc Prints our the value of the chosen routew and the time it took
*/
void TSPDinamica::printSolution() {
  std::cout << "Valor Prog Dinámica: " << value_ << std::endl;
  std::cout << "Tiempo Prog Dinámica (ns): " << time_ << std::endl;
}

/* CODE TO PRINT OUT VALUE MATRIX
for(int i{0}; i < sizeof(memo); ++i) {
    for(int j{0}; j < sizeof(memo); ++j) {
      std::cout << memo[i][j] << " ";
    }
    std::cout << std::endl;
  }
*/