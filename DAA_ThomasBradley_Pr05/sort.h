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
 * @brief:   Algoritmos de Divide y Vencerás. Aqui esta la declaración de la clase Sort
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

template<class key>
class Sort {
 public:
  void sort(vector<key>& arr, int ini, int fin, int level);
  string recurrence();
  int getLevel();
 protected:
  virtual bool small(vector<key>& arr, int ini, int fin) = 0;
  virtual void SolveSmall(vector<key>& arr) = 0;
  virtual int Divide(vector<key>& arr, int ini, int fin) = 0;
  virtual void Combine(vector<key>& arr, int ini, int med, int fin) = 0;
  virtual int Minus() = 0;
  virtual int Plus() = 0;
  virtual vector<string> values() = 0;
 private:
  int level_ = 0;
};