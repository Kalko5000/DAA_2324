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
 * @brief:   Algoritmos de Divide y Vencerás. Aqui esta la declaración de la clase QuickSort
 */

#include <iostream>
#include <vector>
#include "binary.h"

using namespace std;

template<class key>
class QuickSort : public Sort<key> {
 public:
  void printExtraResult() override;
 private:
  bool small(vector<key>& arr, int ini, int fin) override;
  void SolveSmall(vector<key>& arr, key value) override;
  int Divide(vector<key>& arr, int ini, int fin) override;
  void Combine(vector<key>& arr, int ini, int med, int fin) override;
  int Minus() override;
  int Plus() override;
  vector<string> values() override;
};