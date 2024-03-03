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

int Sort::print(vector<int> arr , string name) {
  auto start = high_resolution_clock::now();
  sort(arr, 0, arr.size()-1);
  auto end = high_resolution_clock::now();
  float time = duration_cast<nanoseconds>(end - start).count();

  std::cout << name << "(ns: " << time << "): ";
  for(int j{0}; j < int(arr.size()); ++j) {
    std::cout << arr[j] << " ";
  }
  std::cout << std::endl;

  return time; 
}

void Sort::sort(vector<int>& arr, int ini, int fin) {
  if (small(arr, ini, fin)) {
    SolveSmall(arr);
  } else {
    int med = Divide(arr, ini, fin);
    sort(arr, ini, med - Minus());
    sort(arr, med + Plus(), fin);
    Combine(arr, ini, med, fin);
  }
}

// MERGESORT

bool MergeSort::small(vector<int>& arr, int ini, int fin) {
  return ini >= fin;
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

int MergeSort::Minus() {
  return 0;
}

int MergeSort::Plus() {
  return 1;
}

// QUICKSORT

bool QuickSort::small(vector<int>& arr, int ini, int fin) {
  return ini >= fin;
}

void QuickSort::SolveSmall(vector<int>& arr) {
  // Do nothing since the array is already sorted.
  return;
}

int QuickSort::Divide(vector<int>& arr, int ini, int fin) {
  int pivot{arr[fin]}, pivotIndex{0};
  int count{0}, leftIndex{ini}, rightIndex{fin};

  for (int i{ini}; i < fin; i++) { // How many values are lower than the chosen pivot?
    if (arr[i] <= pivot) {
      count++;
    }
  }

  pivotIndex = ini + count; // Store new pivot pos
  swap(arr[pivotIndex], arr[fin]);  // Place pivot value in that position

  while (leftIndex < pivotIndex && rightIndex > pivotIndex) { // Until all values are on the correct side
    while (arr[leftIndex] <= pivot) {
      leftIndex++;
    }
    while (arr[rightIndex] > pivot) {
      rightIndex--;
    }
    if (leftIndex < pivotIndex && rightIndex > pivotIndex) { // Swap bigger element to right, smaller to left
      swap(arr[leftIndex], arr[rightIndex]);
    }
  }

  return pivotIndex;
}

void QuickSort::Combine(vector<int>& arr, int ini, int med, int fin) {
  // We don't combine in Quicksort
  return;
}

int QuickSort::Minus() {
  return 1;
}

int QuickSort::Plus() {
  return 1;
}