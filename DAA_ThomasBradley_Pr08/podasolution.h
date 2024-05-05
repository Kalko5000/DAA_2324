/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 08: B&B - Maximum Diversity Problem
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    07.may.2024
 * @brief:   Program that solves titular problem. Here we declare the PodaSolution class
 */

#include "graspsolution.h"

class PodaSolution : public Solution {
 public:
  PodaSolution(std::string nombre_fichero, int candidateSize) : Solution(nombre_fichero) {
    candidateSize_ = candidateSize;
  };
  float evaluate(int m);
  void construct(int m);
  std::vector<float> getCenter();
  std::vector<float> getCenterOfSolution();
  int indexOfBiggest(std::vector<float> arr);
  int randomInt(int max);
  int getCandidateSize();
 private:
  int candidateSize_;
};