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
 * @brief:   Program that solves titular problem. Here we declare the Solution class
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

class Solution {
 public:
  Solution(std::string nombre_fichero);
  float stringToFloat(std::string word);
  int evaluate(); // virtual ... = 0
  void printS();
  int getSize();
  int getDimension();
 protected:
  int size_;
  int dimension_;
  std::vector<std::vector<float>> puntos_;
  std::vector<int> S_;
};