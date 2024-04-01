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
 * @brief:   Program that solves titular problem. Here we define the GraspScheduling class
 */

#include "graspscheduling.h"

/**
 * @desc Constructive Greedy algorithm for a parallel machine scheduling problem
*/
void GraspScheduling::evaluate() {
  std::vector<int> used; // Stores used tasks in an easier format, so we don't repeat these
  srand(time(0)); // Seed for random number
  buildT();
  setupS(used);

  do {
    construct(used);
  } while (int(used.size()) < tareas_);
}

/**
 * @desc
 * @param {std::vector<int>&}
*/
void GraspScheduling::construct(std::vector<int>& used) {
  std::vector<int> candidates = {}, canMachines = {}, canTasks = {};
  for (int i{0}; i < maquinas_; ++i) {
    for (int j{0}; j < tareas_; ++j) {
      std::vector<int> temp = S_[i];
      temp.push_back(j);  // Resulting Machine queue if we added the task j
      if (int(candidates.size()) < candidateSize_) {  // We still need to initialize minimum values
        if (!inVector(used, j)) {
          canMachines.push_back(i);
          canTasks.push_back(j);
          candidates.push_back(getMachineTCT(temp));
        }
        continue;
      } 
      int highestIndex = indexOfBiggest(candidates);
      int newTCT = getMachineTCT(temp); // Get value of TCT with new workflow
      if (newTCT < candidates[highestIndex]) { // Check if value of new Workflow is cheaper than previous minimum TCT
        if (!inVector(used, j)) {                    
          canMachines[highestIndex] = i;
          canTasks[highestIndex] = j;
          candidates[highestIndex] = newTCT;
        }
      }
    }
  }
  int index = randomInt(candidateSize_ - 1);
  S_[canMachines[index]].push_back(canTasks[index]);
  used.push_back(canTasks[index]);
}

/**
 * @desc Calculates and returns the total time value of the TCT taking into account all machines
 * @return {int} Temporal value of the TCT post-evaluation
*/
int GraspScheduling::getGlobalTCT() {
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
int GraspScheduling::getMachineTCT(std::vector<int> tasks) {
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
bool GraspScheduling::inVector(std::vector<int> vect, int val) {
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
void GraspScheduling::setupS(std::vector<int>& used) {
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
 * @desc Builds the t matrix comprized of Pi + Sij
*/
void GraspScheduling::buildT() {
  t_.resize(tareas_ + 1);
  for (int i{0}; i < tareas_ + 1; ++i) {
    for (int j{0}; j < tareas_; ++j) {
      t_[i].push_back(procesamiento_[j] + setup_[i][j + 1]);
    }
  }
}

/**
 * @desc
 * @param {std::vector<int>} arr
*/
int GraspScheduling::indexOfBiggest(std::vector<int> arr) {
  int max{0}, maxIndex{0};
  for (int i{0}; i < int(arr.size()); ++i) {
    if (arr[i] > max) {
      max = arr[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}

/**
 * @desc
 * @param {int}
*/
int GraspScheduling::randomInt(int max) {
  return rand() % (max + 1);
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