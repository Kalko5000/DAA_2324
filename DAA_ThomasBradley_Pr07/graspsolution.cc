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
 * @brief:   Program that solves titular problem. Here we define the GraspSolution class
 */

#include "graspsolution.h"

/**
 * @desc GRASP template, specific functionality in other methods
*/
int GraspSolution::evaluate() {
  int newVal{INT_MAX}, counter{0}, min{INT_MAX};
  srand(time(0)); // Seed for random number
  buildT();

  do {
    construct();
    newVal = firstProcessing();  // Swap out final element to end
    if (newVal < min) min = newVal;
    newVal = secondProcessing();  // Swap out first element to start
    if (newVal < min) min = newVal;
    newVal = thirdProcessing();  // Swap out final element to start
    if (newVal < min) min = newVal;
    newVal = fourthProcessing();  // Swap out first element to end
    if (newVal < min) min = newVal;
    newVal = fifthProcessing();  // Swap out every element for every element
    if (newVal < min) min = newVal;
    counter++;
    // std::cout << "Test" << std::endl;
  } while (counter < 10);

  // printS();

  return min;
}

/**
 * @desc Constructive methods for GRASP
 * @param {std::vector<int>&} used Helps keeps track of what tasks ahve already been assigned
*/
int GraspSolution::construct() {
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

  return getGlobalTCT();
}

/**
 * @desc Removes the final element from a machine and adds it to the end of another
 * @returns {int} TCT of the lowest resulting Solution
*/
int GraspSolution::firstProcessing() {
  int base{getGlobalTCT()}, min{base};
  for (int i{0}; i < maquinas_; ++i) {
    for (int j{0}; j < maquinas_; ++j) {
      if (i == j) continue;
      int takeAwayI = getMachineTCT(S_[i]);
      int takeAwayJ = getMachineTCT(S_[j]);
      std::vector<int> removedI = S_[i];
      removedI.pop_back();
      int addI = getMachineTCT(removedI);
      std::vector<int> addedJ = S_[j];
      addedJ.push_back(S_[i][int(S_[i].size() - 1)]);
      int addJ = getMachineTCT(addedJ);
      int result = base - takeAwayI - takeAwayJ + addI + addJ;
      if (result < min) min = result;
    }
  }
  return min;
}

/**
 * @desc Removes the first element from a machine and adds it to the start of another
 * @returns {int} TCT of the lowest resulting Solution
*/
int GraspSolution::secondProcessing() {
  int base{getGlobalTCT()}, min{base};
  for (int i{0}; i < maquinas_; ++i) {
    for (int j{0}; j < maquinas_; ++j) {
      if (i == j) continue;
      int takeAwayI = getMachineTCT(S_[i]);
      int takeAwayJ = getMachineTCT(S_[j]);
      std::vector<int> removedI = S_[i];
      removedI.erase(removedI.begin());
      int addI = getMachineTCT(removedI);
      std::vector<int> addedJ = S_[j];
      addedJ.insert(addedJ.begin(), S_[i][0]);
      int addJ = getMachineTCT(addedJ);
      int result = base - takeAwayI - takeAwayJ + addI + addJ;
      if (result < min) min = result;
    }
  }
  return min;
}

/**
 * @desc Removes the final element from a machine and adds it to the start of another
 * @returns {int} TCT of the lowest resulting Solution
*/
int GraspSolution::thirdProcessing() {
  int base{getGlobalTCT()}, min{base};
  for (int i{0}; i < maquinas_; ++i) {
    for (int j{0}; j < maquinas_; ++j) {
      if (i == j) continue;
      int takeAwayI = getMachineTCT(S_[i]);
      int takeAwayJ = getMachineTCT(S_[j]);
      std::vector<int> removedI = S_[i];
      removedI.pop_back();
      int addI = getMachineTCT(removedI);
      std::vector<int> addedJ = S_[j];
      addedJ.insert(addedJ.begin(), S_[i][int(S_[i].size() - 1)]);
      int addJ = getMachineTCT(addedJ);
      int result = base - takeAwayI - takeAwayJ + addI + addJ;
      if (result < min) min = result;
    }
  }
  return min;
}

/**
 * @desc Removes the first element from a machine and adds it to the end of another
 * @returns {int} TCT of the lowest resulting Solution
*/
int GraspSolution::fourthProcessing() {
  int base{getGlobalTCT()}, min{base};
  for (int i{0}; i < maquinas_; ++i) {
    for (int j{0}; j < maquinas_; ++j) {
      if (i == j) continue;
      int takeAwayI = getMachineTCT(S_[i]);
      int takeAwayJ = getMachineTCT(S_[j]);
      std::vector<int> removedI = S_[i];
      removedI.erase(removedI.begin());
      int addI = getMachineTCT(removedI);
      std::vector<int> addedJ = S_[j];
      addedJ.push_back(S_[i][0]);
      int addJ = getMachineTCT(addedJ);
      int result = base - takeAwayI - takeAwayJ + addI + addJ;
      if (result < min) min = result;
    }
  }
  return min;
}

/**
 * @desc Checks all elements in the place of all others
 * @returns {int} TCT of the lowest resulting Solution
*/
int GraspSolution::fifthProcessing() {
  int base{getGlobalTCT()}, min{base};
  for (int i{0}; i < maquinas_; ++i) {  // Machine to take from
    for (int j{0}; j < maquinas_; ++j) {  // Machine to recieve
      for (int k{0}; k < int(S_[i].size()); ++k) {  // Tasks locationg to give from giver
        for (int n{0}; n < int(S_[j].size()); ++n) {  // Place to receive task for receiver
          if (k == n && i == j) continue;
          int takeAwayI = getMachineTCT(S_[i]);
          int takeAwayJ = getMachineTCT(S_[j]);
          std::vector<int> removedI = S_[i];
          removedI.erase(removedI.begin() + k);
          int addI = getMachineTCT(removedI);
          std::vector<int> addedJ = S_[j];
          addedJ.insert(addedJ.begin() + n, S_[i][k]);
          int addJ = getMachineTCT(addedJ);
          int result = base - takeAwayI - takeAwayJ + addI + addJ;
          if (result < min) min = result;
        }
      }
    }
  }
  return min;
}

/**
 * @desc Calculates and returns the total time value of the TCT taking into account all machines
 * @return {int} Temporal value of the TCT post-evaluation
*/
int GraspSolution::getGlobalTCT() {
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
int GraspSolution::getMachineTCT(std::vector<int> tasks) {
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
bool GraspSolution::inVector(std::vector<int> vect, int val) {
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
void GraspSolution::setupS(std::vector<int>& used) {
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
int GraspSolution::indexOfBiggest(std::vector<int> arr) {
  int max{0}, maxIndex{0};
  for (int i{0}; i < int(arr.size()); ++i) {
    if (arr[i] > max) {
      max = arr[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}

int GraspSolution::indexOfSmallest(std::vector<int> arr) {
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
int GraspSolution::randomInt(int max) {
  return rand() % (max + 1);
}