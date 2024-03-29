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
 * @brief:   Algoritmos de Divide y Vencerás. Aqui esta la definición de la clase QuickSort
 */

#include "quick.h"

/**
 * @desc Detects wether an array is small enough to evaluate yet
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at array
 * @param {int} fin Ending value where we stop looking at array
 * @return {bool} True if is small enough
*/
template<class key>
bool QuickSort<key>::small(vector<key>& arr, int ini, int fin, int level) {
  return ini >= fin;
}

/**
 * @desc Solvers the order of an array for small enough sizes
 * @param {vector<int>&} arr Array to evaluate
*/
template<class key>
void QuickSort<key>::SolveSmall(vector<key>& arr, key value, int ini, int fin, int level) {
  // Do nothing since the array is already sorted.
  return;
}

/**
 * @desc Splits the array into two halves
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at array
 * @param {int} fin Ending value where we stop looking at array
 * @return {int} Middle position that separates left from right side of array
*/
template<class key>
int QuickSort<key>::Divide(vector<key>& arr, int ini, int fin) {
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

/**
 * @desc Combines two different halves of array into one
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at the first part of array
 * @param {int} med Middle value where we stop looking at first half and start looking at second half of array
 * @param {int} fin Ending value where we stop looking at second part of array
*/
template<class key>
void QuickSort<key>::Combine(vector<key>& arr, int ini, int med, int fin) {
  // We don't combine in Quicksort
  return;
}

template<class key>
void QuickSort<key>::action(vector<key>& arr, int ini, int med, int level) {
  return;
}

/**
 * @desc Quantity to subtract from med in first recursive call to sort()
 * @return {int} Amount to subtract
*/
template<class key>
int QuickSort<key>::Minus() {
  return 1;
}

/**
 * @desc Quantity to add onto med in second recursive call to sort()
 * @return {int} Amount to add
*/
template<class key>
int QuickSort<key>::Plus() {
  return 1;
}

/**
 * @desc Returns values a, b and c for a QuickSort recurrence formula
 * @return {std::vector<string>} Vector with values a, b and c
*/
template<class key>
vector<string> QuickSort<key>::values() {
  const string valueA = "T(i) + ";
  const string valueB = "n-i-1";
  const string valueC = "cn";
  return {valueA, valueB, valueC};
}

template<class key>
void QuickSort<key>::printExtraResult() {
  return;
}

// DECLARACIONES
template class QuickSort<int>;