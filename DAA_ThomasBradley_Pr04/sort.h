/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 04: Framework para algoritmos de Divide y Vencerás
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    05.mar.2024
 * @brief:   Framework para algoritmos de Divide y Vencerás. Aqui esta la declaración de la clase Sort
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Sort {
public:
  int print(vector<int> arr, string name);
  void sort(vector<int>& arr, int ini, int fin);
protected:
  virtual bool small(vector<int>& arr, int ini, int fin) = 0;
  virtual void SolveSmall(vector<int>& arr) = 0;
  virtual int Divide(vector<int>& arr, int ini, int fin) = 0;
  virtual void Combine(vector<int>& arr, int ini, int med, int fin) = 0;
  virtual int Minus() = 0;
  virtual int Plus() = 0;
};

class MergeSort : public Sort {
protected:
  bool small(vector<int>& arr, int ini, int fin) override;
  void SolveSmall(vector<int>& arr) override;
  int Divide(vector<int>& arr, int ini, int fin) override;
  void Combine(vector<int>& arr, int ini, int med, int fin) override;
  int Minus() override;
  int Plus() override;
};

class QuickSort : public Sort {
protected:
  bool small(vector<int>& arr, int ini, int fin) override;
  void SolveSmall(vector<int>& arr) override;
  int Divide(vector<int>& arr, int ini, int fin) override;
  void Combine(vector<int>& arr, int ini, int med, int fin) override;
  int Minus() override;
  int Plus() override;
};