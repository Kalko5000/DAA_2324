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
 * @brief:   Program that solves titular problem. Here we declare the VorazSolution class
 */

#include "solution.h"

class VorazSolution : public Solution {
 public:
  VorazSolution(std::string nombre_fichero) : Solution(nombre_fichero) {};
  int evaluate();
  int getGlobalTCT(std::vector<std::vector<int>> S);
  int getMachineTCT(std::vector<int> tasks);
  void setupS(std::vector<int>& used);
  bool inVector(std::vector<int> vect, int val);
};