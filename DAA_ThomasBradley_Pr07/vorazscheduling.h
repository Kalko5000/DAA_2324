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
 * @brief:   Program that solves titular problem. Here we declare the VorazScheduling class
 */

#include "scheduling.h"

class VorazScheduling : public Scheduling {
 public:
  VorazScheduling(std::string nombre_fichero) : Scheduling(nombre_fichero) {};
  void solve(int maxTime);
  int getValue();
  int getTime();
  void printSolution();
};