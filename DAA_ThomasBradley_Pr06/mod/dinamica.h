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
 * @brief:   Framework para algoritmos de Programación Dinámica. Aqui se declara la clase TSPDinamica
 */

#include "tsp.h"

class TSPDinamica : public TSP {
 public:
  TSPDinamica(std::string nombre_fichero) : TSP(nombre_fichero) {};
  void solve(int maxTime);
  int recursiveSolve(int pos, int visited, std::vector<std::vector<std::pair<int, int>>>& state);
  int getValue();
  int getTime();
  void printSolution();
 private:
  std::chrono::_V2::system_clock::time_point startTime_;  // Stores start time of solve() function
  int maxTime_; // Stores the maximum allowed time for solve() method to run
};
