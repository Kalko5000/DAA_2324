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

// MERGESORT

/**
 * @desc Detects wether an array is small enough to evaluate yet
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at array
 * @param {int} fin Ending value where we stop looking at array
 * @return {bool} True if is small enough
*/
bool MergeSort::small(vector<int>& arr, int ini, int fin) {
  return ini >= fin;
}

/**
 * @desc Solvers the order of an array for small enough sizes
 * @param {vector<int>&} arr Array to evaluate
*/
void MergeSort::SolveSmall(vector<int>& arr) {
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
int MergeSort::Divide(vector<int>& arr, int ini, int fin) {
  return (ini + fin) / 2;
}

/**
 * @desc Combines two different halves of array into one
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at the first part of array
 * @param {int} med Middle value where we stop looking at first half and start looking at second half of array
 * @param {int} fin Ending value where we stop looking at second part of array
*/
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

/**
 * @desc Quantity to subtract from med in first recursive call to sort()
 * @return {int} Amount to subtract
*/
int MergeSort::Minus() {
  return 0;
}

/**
 * @desc Quantity to add onto med in second recursive call to sort()
 * @return {int} Amount to add
*/
int MergeSort::Plus() {
  return 1;
}

/**
 * @desc Returns values a, b and c for a MergeSort recurrence formula
 * @return {std::vector<string>} Vector with values a, b and c
*/
std::vector<string> MergeSort::values() {
  const string valueA = "2";
  const string valueB = "n/2";
  const string valueC = "O(n)";
  return {valueA, valueB, valueC};
}

// QUICKSORT

/**
 * @desc Detects wether an array is small enough to evaluate yet
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at array
 * @param {int} fin Ending value where we stop looking at array
 * @return {bool} True if is small enough
*/
bool QuickSort::small(vector<int>& arr, int ini, int fin) {
  return ini >= fin;
}

/**
 * @desc Solvers the order of an array for small enough sizes
 * @param {vector<int>&} arr Array to evaluate
*/
void QuickSort::SolveSmall(vector<int>& arr) {
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

/**
 * @desc Combines two different halves of array into one
 * @param {vector<int>&} arr Array to evaluate
 * @param {int} ini Inicial value where we begin looking at the first part of array
 * @param {int} med Middle value where we stop looking at first half and start looking at second half of array
 * @param {int} fin Ending value where we stop looking at second part of array
*/
void QuickSort::Combine(vector<int>& arr, int ini, int med, int fin) {
  // We don't combine in Quicksort
  return;
}

/**
 * @desc Quantity to subtract from med in first recursive call to sort()
 * @return {int} Amount to subtract
*/
int QuickSort::Minus() {
  return 1;
}

/**
 * @desc Quantity to add onto med in second recursive call to sort()
 * @return {int} Amount to add
*/
int QuickSort::Plus() {
  return 1;
}

/**
 * @desc Returns values a, b and c for a QuickSort recurrence formula
 * @return {std::vector<string>} Vector with values a, b and c
*/
std::vector<string> QuickSort::values() {
  const string valueA = "T(i) + ";
  const string valueB = "n-i-1";
  const string valueC = "cn";
  return {valueA, valueB, valueC};
}