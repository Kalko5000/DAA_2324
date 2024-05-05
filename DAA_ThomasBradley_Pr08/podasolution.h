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
  PodaSolution(std::string nombre_fichero, int candidateSize, bool useGrasp) : Solution(nombre_fichero) {
    candidateSize_ = candidateSize;
    useGrasp_ = useGrasp; 
    cota_ = 0.0;
    nodos_generados_ = 0;
  };
  float evaluate(int m);
  void graspBuild(int m);
  void greedyBuild(int m);
  void widthSearch(std::vector<int> S, int m, int pointCount);
  void depthSearch(std::vector<int> S, int m, int pointCount);
  std::vector<float> getCenter();
  std::vector<float> getCenterOfSolution(std::vector<int> S);
  float getUpperQuota(std::vector<int> S, int m, int pointCount);
  int indexOfBiggest(std::vector<float> arr);
  int randomInt(int max);
  int getCandidateSize();
  int getGeneratedNodes();
 private:
  int candidateSize_;
  bool useGrasp_;
  float cota_;
  int nodos_generados_;
};