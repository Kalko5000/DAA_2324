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

void TSPBruta::solve() {
  auto start = high_resolution_clock::now();

  int s{0};
  std::vector<int> vertex;
  for (int i{0}; i < int(nodes_.size()); ++i) {
    if (i != s) vertex.push_back(i);
  }
  int min_cost{std::numeric_limits<int>::max()};
  while(std::next_permutation(vertex.begin(), vertex.end())) {
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

int TSPBruta::getValue() {
  return value_;
}

int TSPBruta::getTime() {
  return time_;
}

void TSPBruta::printSolution() {
  std::cout << "Valor Fuerza Bruta: " << value_ << std::endl;
  std::cout << "Tiempo Fuerza Bruta (ns): " << time_ << std::endl;
}