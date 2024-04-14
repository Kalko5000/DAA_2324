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
  virtual int evaluate() = 0;
  virtual int getGlobalTCT(std::vector<std::vector<int>> S) = 0;
  virtual int getMachineTCT(std::vector<int> tasks) = 0;
  void buildT();
  void printS();
  int getTasks();
  int getMachines();
  int internalInsertion(std::vector<std::vector<int>>& S);
  int externalInsertion(std::vector<std::vector<int>>& S);
  int internalInterchange(std::vector<std::vector<int>>& S);
  int externalInterchange(std::vector<std::vector<int>>& S);
 protected:
  int tareas_;
  int maquinas_;
  std::vector<int> procesamiento_;
  std::vector<std::vector<int>> setup_;
  std::vector<std::vector<int>> S_;
  std::vector<std::vector<int>> t_;
};