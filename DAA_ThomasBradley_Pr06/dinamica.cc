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

void TSPDinamica::solve() {
  auto start = high_resolution_clock::now();
  int memo[16][16]; // memoization table
  int n{4};
  // Base case: g(i, {}) = c(i, 0)
  for (int i{0}; i < n; ++i) {
    memo[i][0] = nodes_[i][0];
  }
    
  // Compute g(i, S) for increasing sizes of S
  for (int s{1}; s < (1 << n); ++s) {
    for (int i{0}; i < n; ++i) {
      if (!(s & (1 << i))) { // node i not in S
        memo[i][s] = n;
        for (int j{0}; j < n; ++j) {
          if (s & (1 << j)) { // node j in S
            memo[i][s] = std::min(memo[i][s], nodes_[i][j] + memo[j][s ^ (1 << j)]);
          }
        }
      }
    }
  }
  // Compute the final answer g(0, {1, 2, ..., n-1})
  int ans = std::numeric_limits<int>::max();
  for (int i{1}; i < n; ++i) {
    // std::cout << ans << " ";
    ans = std::min(ans, nodes_[0][i] + memo[i][(1 << n) - 1]);
  }
  auto end = high_resolution_clock::now();
  value_ = ans;
  time_ = duration_cast<nanoseconds>(end - start).count();
}

void TSPDinamica::printSolution() {
  std::cout << "Valor Prog Dinámica: " << value_ << std::endl;
  std::cout << "Tiempo Prog Dinámica (ms): " << time_ << std::endl;
}