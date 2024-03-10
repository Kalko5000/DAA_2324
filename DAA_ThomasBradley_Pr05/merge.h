/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 05: Algoritmos de Divide y Vencerás
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    12.mar.2024
 * @brief:   Algoritmos de Divide y Vencerás. Aqui esta la declaración de la clase MergeSort
 */

#include <iostream>
#include <vector>
#include "quick.h"

using namespace std;

class MergeSort : public Sort {
 private:
  bool small(vector<int>& arr, int ini, int fin) override;
  void SolveSmall(vector<int>& arr) override;
  int Divide(vector<int>& arr, int ini, int fin) override;
  void Combine(vector<int>& arr, int ini, int med, int fin) override;
  int Minus() override;
  int Plus() override;
  std::vector<string> values() override;
};