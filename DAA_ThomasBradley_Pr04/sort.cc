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
 * @brief:   Framework para algoritmos de Divide y Vencerás. Aqui esta la definición de la clase Sort
 */

#include "sort.h"

void Sort::sort(vector<int>& arr, int ini, int fin) {
  if (small(arr, ini, fin)) {
    SolveSmall(arr);
  } else {
    int med = Divide(arr, ini, fin);
    sort(arr, ini, med);
    sort(arr, med+1, fin);
    // std::cout << ini << ' ' << med << ' ' << fin << std::endl;
    Combine(arr, ini, med, fin);
  }
}

// MERGESORT

bool MergeSort::small(vector<int>& arr, int ini, int fin) {
  return fin - ini < 1; // Empezamos en 0 por lo que <1 ([1,2] = size 2; 1-0 = 1, queremos que se vuelva a separar)
}

void MergeSort::SolveSmall(vector<int>& arr) {
  // Do nothing since the array is already sorted.
  return;
}

int MergeSort::Divide(vector<int>& arr, int ini, int fin) {
  return (ini + fin) / 2;
}

void MergeSort::Combine(vector<int>& arr, int ini, int med, int fin) { // Fix
  int iniCount{ini}, medCount{med + 1};
  std::vector<int> ordered;

  while (iniCount <= med && medCount <= fin) { // Ir metiendo orden actualizado en ordered
    if(arr[iniCount] < arr[medCount]) {
      ordered.push_back(arr[iniCount]);
      iniCount++;
    } else {
      ordered.push_back(arr[medCount]);
      medCount++;
    }
  }
  if (iniCount > med) { // Llenar los que faltan de la primera mitad
    for (int i{medCount}; i <= fin; i++) {
      ordered.push_back(arr[i]);
    }
  }
  if (medCount > fin) { // Llenar los que faltan de la segunda mitad
    for (int i{iniCount}; i <= med; i++) {
      ordered.push_back(arr[i]);
    }
  }

  for (int i{0}; i < int(ordered.size()); i++) {  // Cambiar valores de arr a los de ordered
    arr[ini + i] = ordered[i];
  }
 }

// QUICKSORT

bool QuickSort::small(vector<int>& arr, int ini, int fin) {
  return fin - ini < 1; // Empezamos en 0 por lo que <1 ([1,2] = size 2; 1-0 = 1, queremos que se vuelva a separar)
}

void QuickSort::SolveSmall(vector<int>& arr) {
  // Do nothing since the array is already sorted.
  return;
}

int QuickSort::Divide(vector<int>& arr, int ini, int fin) {
  return 1;
}

void QuickSort::Combine(vector<int>& arr, int ini, int med, int fin) {
  
}

// 1 3 5 6
// 2 4 7 8

// 1-0 3-2

// 1 3 5 6 2 4 7 8
// 1 2 5 6 3 4 7 8