/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 06: Problema del Viajante de Comercio (TSP)
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    21.mar.2023
 * @brief:   Framework para algoritmos de Programación Dinámica. Aqui se declara la clase TSPVoraz
 */

#include "dinamica.h"

class TSPVoraz : public TSP {
 public:
  TSPVoraz(std::string nombre_fichero) : TSP(nombre_fichero) {};
  void solve(int maxTime);
  int getValue();
  int getTime();
  void printSolution();
};