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

class Sort {
 public:
  int print(vector<int> arr, string name, bool showArray);
  void sort(vector<int>& arr, int ini, int fin, int level);
  string recurrence();
  int getLevel();
 protected:
  virtual bool small(vector<int>& arr, int ini, int fin) = 0;
  virtual void SolveSmall(vector<int>& arr) = 0;
  virtual int Divide(vector<int>& arr, int ini, int fin) = 0;
  virtual void Combine(vector<int>& arr, int ini, int med, int fin) = 0;
  virtual int Minus() = 0;
  virtual int Plus() = 0;
  virtual std::vector<string> values() = 0;
 private:
  int level_ = 0;
};