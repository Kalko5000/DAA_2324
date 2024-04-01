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
    int minMachine{0}, minDest{-1};
    for (int i{1}; i < maquinas_; ++i) {  // Pick machine with the lowest total cost
      if (getMachineTCT(S_[i]) < getMachineTCT(S_[minMachine])) {
        minMachine = i;
      }
    }
    for (int j{0}; j < tareas_; ++j) {  // Pick lowest cost to transition to a task from machine with lowest total cost
      if (minDest == -1) {
        if (!inVector(used, j)) {
          minDest = j;
        }
        continue;
      } 
      int task = S_[minMachine][int(S_[minMachine].size() - 1)];  // Final task in machine with lowest total cost
      if (t_[task + 1][j] < t_[task + 1][minDest]) { // We use t to detect which tasks will have a lower overall cost
        if (!inVector(used, j)) {                    
          minDest = j;
        }
      }
    }
    S_[minMachine].push_back(minDest);
    used.push_back(minDest);
  } while (int(used.size()) < tareas_);
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

/**
 * @desc Returns the cost of running all currently assigned tasks on a machine
 * @param {std::vector<int>} tasks List of tasks to run
 * @return {int} Total cost of running all tasks
*/
int VorazScheduling::costOfArc(std::vector<int> tasks) {
  int sum{0}, previous{0};
  for (int i{0}; i < int(tasks.size()); ++i) {
    sum += t_[previous][tasks[i]];
    previous = tasks[i];
  }
  return sum;
}

/**
 * @desc Builds the t matrix comprized of Pi + Sij
*/
void VorazScheduling::buildT() {
  t_.resize(tareas_ + 1);
  for (int i{0}; i < tareas_ + 1; ++i) {
    for (int j{0}; j < tareas_; ++j) {
      t_[i].push_back(procesamiento_[j] + setup_[i][j + 1]);
    }
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