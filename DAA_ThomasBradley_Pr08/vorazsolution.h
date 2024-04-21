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
 * @brief:   Program that solves titular problem. Here we declare the VorazSolution class
 */

#include "solution.h"

class VorazSolution : public Solution {
 public:
  VorazSolution(std::string nombre_fichero) : Solution(nombre_fichero) {};
  float evaluate(int m);
  std::vector<float> getCenter();
  std::vector<float> getCenterOfSolution();
};