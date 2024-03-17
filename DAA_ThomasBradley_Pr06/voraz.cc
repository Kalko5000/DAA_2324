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

void TSPVoraz::solve() {
  auto start = high_resolution_clock::now();
  int sum{0}, counter{0}, min{100000};
  int j{0}, i{0};
  std::map<int, int> visitedRouteList;

  visitedRouteList[0] = 1;
  int route[nodes_.size()];

  while (i < int(nodes_.size()) && j < int(nodes_[i].size())) {
    if (counter >= int(nodes_[i].size()) - 1) break;

    if (j != i && (visitedRouteList[j] == 0)) {
      if (nodes_[i][j] < min) {
        min = nodes_[i][j];
        route[counter] = j + 1;
      }
    }
    ++j;

    if (j == int(nodes_[i].size())) {
      sum += min;
      min = 100000;
      visitedRouteList[route[counter] - 1] = 1;
      j = 0;
      i = route[counter] - 1;
      ++counter;
    }
  }

  i = route[counter - 1] - 1;
  for (j = 0; j < int(nodes_.size()); ++j) {
    if ((i != j) && nodes_[i][j] < min) {
      min = nodes_[i][j];
      route[counter] = j + 1;
    }
  }
  sum += min;
  auto end = high_resolution_clock::now();
  value_ = sum;
  time_ = duration_cast<nanoseconds>(end - start).count();
}

void TSPVoraz::printSolution() {
  std::cout << "Valor Voraz: " << value_ << std::endl;
  std::cout << "Tiempo Voraz (ns): " << time_ << std::endl;
}