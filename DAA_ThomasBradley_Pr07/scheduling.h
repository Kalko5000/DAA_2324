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
 * @brief:   Program that solves titular problem. Here we declare the Scheduling class
 */

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>
#include <limits>
#include <cmath>
#include <map>
#include <chrono>

using namespace std::chrono;

class Scheduling {
 public:
  Scheduling(std::string nombre_fichero);
  void buildNodes(int size);
  virtual void solve(int maxTime) = 0;
  virtual int getValue() = 0;
  virtual int getTime() = 0;
  virtual void printSolution() = 0;
 protected:
  std::vector<std::vector<int>> nodes_; // Matrix with definition of TSP problem
  int value_; // Minimum value found to solve TSP problem
  int time_;  // Time it took to solve TSP problem
  std::vector<int> path_;  // Path chosen in final sequence
};