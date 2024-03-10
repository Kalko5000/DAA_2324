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
 * @brief:   Algoritmos de Divide y Vencerás. Aqui esta la definición de la clase MergeSort
 */

#include "merge.h"

/**
 * @desc Detects wether an array is small enough to evaluate yet
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at array
 * @param {int} fin Ending value where we stop looking at array
 * @return {bool} True if is small enough
*/
template<class key>
bool MergeSort<key>::small(vector<key>& arr, int ini, int fin) {
  return ini >= fin;
}

/**
 * @desc Solvers the order of an array for small enough sizes
 * @param {vector<int>&} arr Array to evaluate
*/
template<class key>
void MergeSort<key>::SolveSmall(vector<key>& arr) {
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
int MergeSort<key>::Divide(vector<key>& arr, int ini, int fin) {
  return (ini + fin) / 2;
}

/**
 * @desc Combines two different halves of array into one
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at the first part of array
 * @param {int} med Middle value where we stop looking at first half and start looking at second half of array
 * @param {int} fin Ending value where we stop looking at second part of array
*/
template<class key>
void MergeSort<key>::Combine(vector<key>& arr, int ini, int med, int fin) { // Fix
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

/**
 * @desc Quantity to subtract from med in first recursive call to sort()
 * @return {int} Amount to subtract
*/
template<class key>
int MergeSort<key>::Minus() {
  return 0;
}

/**
 * @desc Quantity to add onto med in second recursive call to sort()
 * @return {int} Amount to add
*/
template<class key>
int MergeSort<key>::Plus() {
  return 1;
}

/**
 * @desc Returns values a, b and c for a MergeSort recurrence formula
 * @return {std::vector<string>} Vector with values a, b and c
*/
template<class key>
vector<string> MergeSort<key>::values() {
  const string valueA = "2";
  const string valueB = "n/2";
  const string valueC = "O(n)";
  return {valueA, valueB, valueC};
}

// DECLARACIONES
template class MergeSort<int>;