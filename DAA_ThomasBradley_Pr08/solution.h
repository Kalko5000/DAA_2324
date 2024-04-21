/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 08: B&B - Maximum Diversity Problem
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    21.apr.2024
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
  virtual float evaluate(int m) = 0;
  float stringToFloat(std::string word);
  float distanceTo(std::vector<float> start, std::vector<float> end);
  float getTotalDistance(std::vector<int> S);
  void setupS();
  void printS();
  int getSize();
  int getDimension();
  std::string getS();
  std::vector<int> localSearch(std::vector<int> S);
 protected:
  int size_;
  int dimension_;
  std::vector<std::vector<float>> puntos_;
  std::vector<int> S_;
};