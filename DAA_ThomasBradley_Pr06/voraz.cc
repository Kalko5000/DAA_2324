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

int TSPVoraz::getValue() {
  return value_;
}

int TSPVoraz::getTime() {
  return time_;
}

void TSPVoraz::printSolution() {
  std::cout << "Valor Voraz: " << value_ << std::endl;
  std::cout << "Tiempo Voraz (ns): " << time_ << std::endl;
}

/*
auto start = high_resolution_clock::now();

  int sum = 0;
	int counter = 0;
	int j = 0, i = 0;
	int min = INT_MAX;
	std::map<int, int> visitedRouteList;
	visitedRouteList[0] = 1;  // Starting from first node
	int route[nodes_.size()];
	while (i < int(nodes_.size()) && j < int(nodes_[i].size())) { // Traverse adjacencies
		auto mid = high_resolution_clock::now();
    // std::cout << duration_cast<seconds>(mid - start).count() << std::endl;
    if (duration_cast<seconds>(mid - start).count() >= maxTime) {  // Over time limit
      time_ = -1;
      value_ = sum;
      return;
    }
    if (counter >= int(nodes_[i].size()) - 1) {  // Corner
			break;
		}
		if (j != i && (visitedRouteList[j] == 0)) { // If node is unvisited + has a smaller cost
			if (nodes_[i][j] < min) {
				min = nodes_[i][j];
				route[counter] = j + 1;
			}
		}
		j++;
		if (j == int(nodes_[i].size())) {  // Check paths
			sum += min;
			min = INT_MAX;
			visitedRouteList[route[counter] - 1] = 1;
			j = 0;
			i = route[counter] - 1;
			counter++;
		}
	}
  // Update last visited node
	i = route[counter - 1] - 1; 
	for (j = 0; j < int(nodes_.size()); j++) {
		if ((i != j) && nodes_[i][j] < min) {
			min = nodes_[i][j];
			route[counter] = j + 1;
		}
	}
	sum += min;

  auto end = high_resolution_clock::now();
  value_ = sum;
  time_ = duration_cast<nanoseconds>(end - start).count();
*/