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
 * @brief:   Algoritmos de Divide y Vencerás. Aqui esta la definición de la clase HanoiSolver
 */

#include "hanoisolver.h"

template<class key>
HanoiSolver<key>::HanoiSolver(int size) {
  gameState.push_back({});
  for (int i{0}; i < size; i++) {
    gameState[0].push_back(size - i);
  }
  gameState.push_back({});
  gameState.push_back({});
  movements = {};
}

/**
 * @desc Detects wether an array is small enough to evaluate yet
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at array
 * @param {int} fin Ending value where we stop looking at array
 * @return {bool} True if is small enough
*/
template<class key>
bool HanoiSolver<key>::small(vector<key>& arr, int ini, int fin, int level) {
  int n = arr[0] - level;
  return n == 0; // 0 instead of 1 since we've decreased the size
}

/**
 * @desc Solvers the order of an array for small enough sizes
 * @param {vector<int>&} arr Array to evaluate
*/
template<class key>
void HanoiSolver<key>::SolveSmall(vector<key>& arr, key value, int ini, int fin, int level) {
  int temp = gameState[ini-1][gameState[ini-1].size() - 1];
  gameState[ini-1].pop_back();
  gameState[fin-1].push_back(temp);
  movements.push_back({arr[0] - level + 1, ini, fin});
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
int HanoiSolver<key>::Divide(vector<key>& arr, int ini, int fin) {
  if ((ini == 1 && fin == 2) || (ini == 2 && fin == 1)) {
    return 3;
  } else if ((ini == 1 && fin == 3) || (ini == 3 && fin == 1)) {
    return 2;
  } else {
    return 1;
  }
}

/**
 * @desc Combines two different halves of array into one
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at the first part of array
 * @param {int} med Middle value where we stop looking at first half and start looking at second half of array
 * @param {int} fin Ending value where we stop looking at second part of array
*/
template<class key>
void HanoiSolver<key>::Combine(vector<key>& arr, int ini, int med, int fin) {
  return;
}

template<class key>
void HanoiSolver<key>::action(vector<key>& arr, int ini, int fin, int level) {
  int value = gameState[ini-1][gameState[ini-1].size() - 1];
  gameState[ini-1].pop_back();
  gameState[fin-1].push_back(value);
  movements.push_back({arr[0] - level + 1, ini, fin});
  return;
}

/**
 * @desc Quantity to subtract from med in first recursive call to sort()
 * @return {int} Amount to subtract
*/
template<class key>
int HanoiSolver<key>::Minus() {
  return 0;
}

/**
 * @desc Quantity to add onto med in second recursive call to sort()
 * @return {int} Amount to add
*/
template<class key>
int HanoiSolver<key>::Plus() {
  return 0;
}

/**
 * @desc Returns values a, b and c for a HanoiSolver recurrence formula
 * @return {std::vector<string>} Vector with values a, b and c
*/
template<class key>
vector<string> HanoiSolver<key>::values() {
  const string valueA = "";
  const string valueB = "n/2";
  const string valueC = "1";
  return {valueA, valueB, valueC};
}

template<class key>
void HanoiSolver<key>::printExtraResult() {
  for (int i{0}; i < int(movements.size()); ++i) {
    std::cout << "Moved value " << movements[i][0] << " from " << movements[i][1] << " to " << movements[i][2] << std::endl;
  }
  std::cout << std::endl;
}

// DECLARACIONES
template class HanoiSolver<int>;