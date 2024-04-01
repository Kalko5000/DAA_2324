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
  buildT();
  setupS(used);

  do {
    int minMachine{0}, minDest{-1}, minTCT{INT_MAX};
    for (int i{0}; i < maquinas_; ++i) {
      for (int j{0}; j < tareas_; ++j) {
        std::vector<int> temp = S_[i];
        temp.push_back(j);  // Resulting Machine queue if we added the task j
        if (minDest == -1) {  // We still need to initialize minimum values
          if (!inVector(used, j)) {
            minMachine = i;
            minDest = j;
            minTCT = getMachineTCT(temp);
          }
          continue;
        } 
        int newTCT = getMachineTCT(temp); // Get value of TCT with new workflow
        if (newTCT < minTCT) { // Check if value of new Workflow is cheaper than previous minimum TCT
          if (!inVector(used, j)) {                    
            minMachine = i;
            minDest = j;
            minTCT = newTCT;
          }
        }
      }
    }
    S_[minMachine].push_back(minDest);
    used.push_back(minDest);
  } while (int(used.size()) < tareas_);

  // PrintS();
}

/**
 * @desc Calculates and returns the total time value of the TCT taking into account all machines
 * @return {int} Temporal value of the TCT post-evaluation
*/
int VorazScheduling::getGlobalTCT() {
  int sum{0};
  for (int i{0}; i < int(S_.size()); ++i) {
    sum += getMachineTCT(S_[i]);
  }
  return sum;
}

/**
 * @desc Calculates the TCT value of a single machine
 * @return {int} Temporal value of the machine's TCT post-evaluation
*/
int VorazScheduling::getMachineTCT(std::vector<int> tasks) {
  int sum{0}, previous{0};
  for (int i{0}; i < int(tasks.size()); ++i) {
    sum += (t_[previous][tasks[i]] * (tasks.size() - i));
    previous = tasks[i];
  }
  return sum;
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
 * @desc Sets up S with values of the 4 tasks with the lowest initial setup time
 * @param {std::vector<int>&} used Vector of parameters already used that we need to update
 *                                 as we go along
*/
void VorazScheduling::setupS(std::vector<int>& used) {
  for (int i{0}; i < maquinas_; ++i) {
    int minIndex{0};
    for (int j{0}; j < int(t_[0].size()); ++j) {
      if (t_[0][j] < t_[0][minIndex] || minIndex == 0) {
        if (!inVector(used, j)) { // Used stores indexes of tasks in procesamiento_ so -1
          minIndex = j;
        }
      }
    }
    S_[i].push_back(minIndex);
    used.push_back(minIndex);
  }
}