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

  int sum = 0;
	int counter = 0;
	int j = 0, i = 0;
	int min = INT_MAX;
	std::map<int, int> visitedRouteList;
	visitedRouteList[0] = 1;  // Starting from first node
	int route[nodes_.size()];
	while (i < int(nodes_.size()) && j < int(nodes_[i].size())) { // Traverse adjacencies
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
int sum = 0;
  int counter = 0;
  int j = 0, i = 0;
  int min = INT_MAX;
  std::map<int, int> visitedRouteList;

  // Starting from the 0th indexed
  // city i.e., the first city
  visitedRouteList[0] = 1;
  int route[nodes_.size()];

  // Traverse the adjacency
  // matrix tsp[][]
  while (i < int(nodes_.size()) && j < int(nodes_[i].size())) {
    // Corner of the Matrix
    if (counter >= int(nodes_[i].size()) - 1) {
      break;
    }

    // If this path is unvisited then
    // and if the cost is less then
    // update the cost
    if (j != i && (visitedRouteList[j] == 0)) {
      if (nodes_[i][j] < min) {
          min = nodes_[i][j];
          route[counter] = j + 1;
      }
    }
    j++;

    // Check all paths from the
    // ith indexed city
    if (j == int(nodes_[i].size())) {
      sum += min;
      min = INT_MAX;
      visitedRouteList[route[counter] - 1] = 1;
      j = 0;
      i = route[counter] - 1;
      counter++;
    }
  }
 
  // Update the ending city in array
  // from city which was last visited
  i = route[counter - 1] - 1;
  for (j = 0; j < int(nodes_.size()); j++) {
    if ((i != j) && nodes_[i][j] < min) {
        min = nodes_[i][j];
        route[counter] = j + 1;
    }
  }
  sum += min;
*/