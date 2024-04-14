/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 07: Parallel Machine Sscheduling Problem with Dependent Setup Times
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    02.apr.2024
 * @brief:   Program that solves titular problem. Here we define the GvnsSolution class
 */

#include "gvnssolution.h"

/**
 * @desc GVNS template, specific functionality in other methods
 * @returns {int} Resulting TCT value of optimal grouping
*/
int GvnsSolution::evaluate() {
  int counter{0}, min{INT_MAX};
  int k{1};
  srand(time(0)); // Seed for random number
  buildT();

  do {
    int caseMin{INT_MAX}, newVal{INT_MAX};
    construct();
    std::vector<std::vector<int>> S{S_};
    while (k <= kMax_) {
      std::vector<std::vector<int>> S1 = shake(S, k);
      std::vector<std::vector<int>> S2 = vnd(S1);
      newVal = getGlobalTCT(S2);
      if (newVal < caseMin) { // Best sol for current iteration
        if (newVal < min) { // Best sol found so far
          min = newVal;
        }
        caseMin = newVal;
        S = S2;
        k = 1;
      } else {
        k++;
      }
    }
    k = 1;
    counter++;
  } while (counter < 100);

  // printS();
  return min;
}

/**
 * @desc Constructive methods for GRASP
 * @param {std::vector<int>&} used Helps keeps track of what tasks ahve already been assigned
*/
int GvnsSolution::construct() {
  std::vector<int> used; // Stores used tasks in an easier format, so we don't repeat these
  setupS(used);
  do {
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
    int index = randomInt(int(candidates.size()) - 1);
    S_[canMachines[index]].push_back(canTasks[index]);
    used.push_back(canTasks[index]);
  } while (int(used.size()) < tareas_);

  return getGlobalTCT(S_);
}

/**
 * @desc Swaps two random tasks between a group of machines, k times
 * @param {std::vector<std::vector<int>>} S Original group of machines
 * @param {int} k Times we wants to swap elements
 * @returns {std::vector<std::vector<int>>} Shaken group of machines
*/
std::vector<std::vector<int>> GvnsSolution::shake(std::vector<std::vector<int>> S, int k) {
  int counter{0};
  while (counter < k) {
    int startMachine = randomInt(maquinas_ - 1);
    int destMachine = randomInt(maquinas_ - 1);
    int startTask = randomInt(int(S[startMachine].size() - 1));
    int destTask = randomInt(int(S[destMachine].size() - 1));
    int temp = S[startMachine][startTask];
    S[startMachine][startTask] = S[destMachine][destTask];
    S[destMachine][destTask] = temp;
    counter++;
  }
  return S;
}

/**
 * @desc Calculates the local optimal of a group of machines
 * @param {std::vector<std::vector<int>>} S Original group of machines
 * @returns {std::vector<std::vector<int>>} Optimized grouping after being passed through all local optimization methods
*/
std::vector<std::vector<int>> GvnsSolution::vnd(std::vector<std::vector<int>> S) {
  int newVal{INT_MAX}, min{INT_MAX}, counter{0};
  do {
    newVal = internalInsertion(S);
    if (newVal < min) {
      min = newVal;
      continue;
    }
    newVal = externalInsertion(S);
    if (newVal < min) {
      min = newVal;
      continue;
    }
    newVal = internalInterchange(S);
    if (newVal < min) {
      min = newVal;
      continue;
    }
    newVal = externalInterchange(S);
    if (newVal < min) {
      min = newVal;
      continue;
    }
    counter++;
  } while (counter < 1);
  return S;
}

/**
 * @desc Calculates and returns the total time value of the TCT taking into account all machines
 * @return {int} Temporal value of the TCT post-evaluation
*/
int GvnsSolution::getGlobalTCT(std::vector<std::vector<int>> S) {
  int sum{0};
  for (int i{0}; i < int(S.size()); ++i) {
    sum += getMachineTCT(S[i]);
  }
  return sum;
}

/**
 * @desc Calculates the TCT value of a single machine
 * @return {int} Temporal value of the machine's TCT post-evaluation
*/
int GvnsSolution::getMachineTCT(std::vector<int> tasks) {
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
bool GvnsSolution::inVector(std::vector<int> vect, int val) {
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
void GvnsSolution::setupS(std::vector<int>& used) {
  S_ = {};
  S_.resize(maquinas_);
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
 * @desc Returns the index of the biggest element in an array
 * @param {std::vector<int>} arr Array to check for biggest element in
 * @return {int} Index of biggest element
*/
int GvnsSolution::indexOfBiggest(std::vector<int> arr) {
  int max{0}, maxIndex{0};
  for (int i{0}; i < int(arr.size()); ++i) {
    if (arr[i] > max) {
      max = arr[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}

int GvnsSolution::indexOfSmallest(std::vector<int> arr) {
  int min{INT_MAX}, minIndex{0};
  for (int i{0}; i < int(arr.size()); ++i) {
    if (arr[i] < min) {
      min = arr[i];
      minIndex = i;
    }
  }
  return minIndex;
}

/**
 * @desc Generates a random number between 0 and a specified amount
 * @param {int} max Highets number that can be generated
 * @return {int} Randomly generated number
*/
int GvnsSolution::randomInt(int max) {
  return rand() % (max + 1);
}

int GvnsSolution::getCandidateSize() {
  return candidateSize_;
}

int GvnsSolution::getKMax() {
  return kMax_;
}