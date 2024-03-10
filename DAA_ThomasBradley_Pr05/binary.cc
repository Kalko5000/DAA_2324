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
 * @brief:   Algoritmos de Divide y Vencerás. Aqui esta la definición de la clase BinarySearch
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
bool BinarySearch<key>::small(vector<key>& arr, int ini, int fin) {
  return ini > fin;
}

/**
 * @desc Solvers the order of an array for small enough sizes
 * @param {vector<int>&} arr Array to evaluate
*/
template<class key>
void BinarySearch<key>::SolveSmall(vector<key>& arr, key value) {
  // Value doesn't exist in array
  foundPos = -1;
  searchValue = value;
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
int BinarySearch<key>::Divide(vector<key>& arr, int ini, int fin) {
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
void BinarySearch<key>::Combine(vector<key>& arr, int ini, int med, int fin) {
  // Value has been found
  foundPos = med;
  searchValue = arr[med];
  return;
}

/**
 * @desc Quantity to subtract from med in first recursive call to sort()
 * @return {int} Amount to subtract
*/
template<class key>
int BinarySearch<key>::Minus() {
  return 1;
}

/**
 * @desc Quantity to add onto med in second recursive call to sort()
 * @return {int} Amount to add
*/
template<class key>
int BinarySearch<key>::Plus() {
  return 1;
}

/**
 * @desc Returns values a, b and c for a BinarySearch recurrence formula
 * @return {std::vector<string>} Vector with values a, b and c
*/
template<class key>
vector<string> BinarySearch<key>::values() {
  const string valueA = "T(i) + ";
  const string valueB = "n-i-1";
  const string valueC = "cn";
  return {valueA, valueB, valueC};
}

template<class key>
void BinarySearch<key>::printExtraResult() {
  if (foundPos == -1) {
    std::cout << "Value " << searchValue << " was not found in array" << std::endl;
  } else {
    std::cout << "Value " << searchValue << " was found in position " << foundPos << std::endl;
  }
  std::cout << std::endl;
}

// DECLARACIONES
template class BinarySearch<int>;