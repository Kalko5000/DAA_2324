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

#include "sort.h"

/**
 * @desc Prints the name of the algorithm, how long it took to complete and the ordered array
 * @param {vector<int>} arr Array to be ordered
 * @param {string} name Name of the algorithm
 * @return {int} Time it took (in nanoseconds) to complete the ordering
*/
int Sort::print(vector<int> arr , string name, bool showArray) {
  auto start = high_resolution_clock::now();
  sort(arr, 0, arr.size()-1, 0);
  auto end = high_resolution_clock::now();
  float time = duration_cast<nanoseconds>(end - start).count();

  std::cout << name << "(ns: " << time << ")";
  if (showArray) {
    std::cout << ": ";
    for(int j{0}; j < int(arr.size()); ++j) {
      std::cout << arr[j] << " ";
    }
  }
  std::cout << std::endl;

  return time; 
}

/**
 * @desc Recursive template for sorting arrays, specifics to be filled by subclasses
 * @param {vector<int>&} arr Array to be ordered
 * @param {int} ini Starting position of array to look at
 * @param {int} fin Ending position of array to look at
*/
void Sort::sort(vector<int>& arr, int ini, int fin, int level) {
  level++;
  if (level_ < level) level_ = level;
  if (small(arr, ini, fin)) {
    SolveSmall(arr);
  } else {
    int med = Divide(arr, ini, fin);
    sort(arr, ini, med - Minus(), level);
    sort(arr, med + Plus(), fin, level);
    Combine(arr, ini, med, fin);
  }
}

/**
 * @desc Return a string with the recurrence formula for an algorithm, dependant
 *       on subclasses
 * @return {string} String with formula
*/
string Sort::recurrence() {
  std::vector<string> constants = values();
  return "T(n) = " + constants[0] + "T(" + constants[1] + ") + " + constants[2];
}

int Sort::getLevel() {
  return level_;
}