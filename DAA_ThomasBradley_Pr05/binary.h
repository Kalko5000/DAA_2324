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
 * @brief:   Algoritmos de Divide y Vencerás. Aqui esta la declaración de la clase BinarySearch
 */

#include <iostream>
#include <vector>
#include "hanoisolver.h"

using namespace std;

template<class key>
class BinarySearch : public Sort<key> {
 public:
  void printExtraResult() override;
 private:
  bool small(vector<key>& arr, int ini, int fin, int level) override;
  void SolveSmall(vector<key>& arr, key value, int ini, int fin, int level) override;
  int Divide(vector<key>& arr, int ini, int fin) override;
  void Combine(vector<key>& arr, int ini, int med, int fin) override;
  void action(vector<key>& arr, int ini, int fin, int level) override;
  int Minus() override;
  int Plus() override;
  vector<string> values() override;

  int foundPos = -1;
  int searchValue = 0;
};