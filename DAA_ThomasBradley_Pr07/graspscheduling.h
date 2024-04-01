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
 * @brief:   Program that solves titular problem. Here we declare the GraspScheduling class
 */

#include "vorazscheduling.h"

class GraspScheduling : public Scheduling {
 public:
  GraspScheduling(std::string nombre_fichero, int candidateSize) : Scheduling(nombre_fichero) {
    candidateSize_ = candidateSize;
  };
  void evaluate();
  void construct(std::vector<int>& used);
  int getGlobalTCT();
  int getMachineTCT(std::vector<int> tasks);
  void setupS(std::vector<int>& used);
  bool inVector(std::vector<int> vect, int val);
  int indexOfBiggest(std::vector<int> arr);
  int randomInt(int max);
 private:
  int candidateSize_;
};