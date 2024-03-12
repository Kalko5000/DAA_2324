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
 * @brief:   Algoritmos de Divide y Vencerás. Aqui esta la definición de la clase Sort
 */

#include "solution.h"

/**
 * @desc Recursive template for sorting arrays, specifics to be filled by subclasses
 * @param {vector<int>&} arr Array to be ordered
 * @param {int} ini Starting position of array to look at
 * @param {int} fin Ending position of array to look at
*/
template<class key>
void Solution<key>::solve(vector<key>& arr, int ini, int fin, key value, int level) {
  level++;
  if (level_ < level) level_ = level; // Depth

  if (small(arr, ini, fin, level)) {
    SolveSmall(arr, value, ini, fin, level);
  } else {
    int med = Divide(arr, ini, fin);
    if (arr[med] > value || value == -1) {
      solve(arr, ini, med - Minus(), value, level);
    }
    action(arr, ini, fin, level);
    if (arr[med] < value || value == -1) {
      solve(arr, med + Plus(), fin, value, level);
    }
    if (arr[med] == value || value == -1) {
      Combine(arr, ini, med, fin);
    }
  }
}

/**
 * @desc Return a string with the recurrence formula for an algorithm, dependant
 *       on subclasses
 * @return {string} String with formula
*/
template<class key>
string Solution<key>::recurrence() {
  std::vector<string> constants = values();
  return "T(n) = " + constants[0] + "T(" + constants[1] + ") + " + constants[2];
}

/**
 * @desc Returns max depth level that the algorithm reached
 * @return {int} Max depth level
*/
template<class key>
int Solution<key>::getLevel() {
  return level_;
}

// DECLARACIONES 
template class Solution<int>;