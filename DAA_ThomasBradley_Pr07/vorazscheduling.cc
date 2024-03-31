/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 07: Parallel Machine Scheduling Problem with Dependent Setup Times
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    02.apr.2024
 * @brief:   Program that solves titular problem. Here we define the VorazScheduling class
 */

#include "vorazscheduling.h"

/**
 * @desc Constructive Greedy algorithm for a parallel machine scheduling problem
*/
void VorazScheduling::evaluate() {
  std::vector<int> used; // Stores used tasks in an easier format, so we don't repeat these
  setupS(used);

  do {
    int minMachine{-1}, minDest{-1};
    for (int i{0}; i < maquinas_; ++i) {
      for (int j{0}; j < tareas_; ++j) {
        if (minMachine == -1 || minDest == -1) {
          if (!inVector(used, j)) {
            minMachine = i;
            minDest = j;
          }
          continue;
        } 
        int task = S_[i][int(S_[i].size() - 1)];  // Task to check if leap is optimal 
        int minTask = S_[minMachine][int(S_[minMachine].size() - 1)]; // Lowest cost task to leap from found so far
        if (setup_[task + 1][j + 1] < setup_[minTask + 1][minDest + 1]) { // Here we need to evaluate the TCT, also
          if (!inVector(used, j)) {                                       // +1 because setup is (n+1)x(n+1)
            minMachine = i;
            minDest = j;
          }
        }
      }
    }
    S_[minMachine].push_back(minDest);
    used.push_back(minDest);
  } while (int(used.size()) < tareas_);
}

/**
 * @desc Calculates and returns the total time value of the TCT with the solution previously calculated
 * @return {int} Temporal value of the TCT post-evaluation
*/
int VorazScheduling::getTCT() {
  return 0;
}

/**
 * @desc Checks if a value is found in a vector
 * @param {std::vector<int>} vect Vector to search for value in
 * @param {int} val Value to look for
 * @return {bool} Returns true if is found
*/
bool VorazScheduling::inVector(std::vector<int> vect, int val) {
  bool valid{false};
  for (int n{0}; n < int(vect.size()); ++n) {
    if (val == vect[n]) {
      valid = true;
      break;
    }
  }
  return valid;
}

/**
 * @desc Sets up S with values of the 4 taks with the lowest initial setup time
 * @param {std::vector<int>&} used Vector of parameters already used that we need to update
 *                                 as we go along
*/
void VorazScheduling::setupS(std::vector<int>& used) {
  for (int i{0}; i < maquinas_; ++i) {
    int minIndex{0};
    for (int j{1}; j < int(setup_[0].size()); ++j) {
      if (setup_[0][j] < setup_[0][minIndex] || minIndex == 0) {
        if (!inVector(used, j - 1)) { // Used stores indexes of tasks in procesamiento_ so -1
          minIndex = j;
        }
      }
    }
    S_[i].push_back(minIndex - 1);
    used.push_back(minIndex - 1);
  }
}

/* CODE TO SHOW VALUES OF S
for (int i{0}; i < int(S_.size()); ++i) {
    for (int j{0}; j < int(S_[i].size()); ++j) {
      std::cout << S_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
*/