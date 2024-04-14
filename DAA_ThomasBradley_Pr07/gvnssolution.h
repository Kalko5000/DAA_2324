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
 * @brief:   Program that solves titular problem. Here we declare the GvnsSolution class
 */

#include "graspsolution.h"

class GvnsSolution : public Solution {
 public:
  GvnsSolution(std::string nombre_fichero, int candidateSize, int kMax) : Solution(nombre_fichero) {
    candidateSize_ = candidateSize;
    kMax_ = kMax;
  };
  int evaluate();
  int construct();
  std::vector<std::vector<int>> shake(std::vector<std::vector<int>> S, int k);
  std::vector<std::vector<int>> vnd(std::vector<std::vector<int>> S);
  int getGlobalTCT(std::vector<std::vector<int>> S);
  int getMachineTCT(std::vector<int> tasks);
  void setupS(std::vector<int>& used);
  bool inVector(std::vector<int> vect, int val);
  int indexOfBiggest(std::vector<int> arr);
  int indexOfSmallest(std::vector<int> arr);
  int randomInt(int max);
  int getCandidateSize();
  int getKMax();
 private:
  int candidateSize_;
  int kMax_;
};