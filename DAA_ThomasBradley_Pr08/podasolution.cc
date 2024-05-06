/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 08: B&B - Maximum Diversity Problem
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    07.may.2024
 * @brief:   Program that solves titular problem. Here we define the PodaSolution class
 */

#include "podasolution.h"

/**
 * @desc Evaluates the MDP problem using a Grasp algorithm 
 * @param {int} m Number of points to include in solution
 * @returns {float} Resulting distance from found solution
*/
float PodaSolution::evaluate(int m) {
  std::vector<int> bestS{S_};
  srand(time(0)); // Seed for random number

  if (useGrasp_) {
    graspBuild(m);
  } else {
    greedyBuild(m);
  }
  cota_ = getTotalDistance(S_);
  // std::cout << cota_ << " ";
  nodos_generados_ = 1;
  widthSearch({}, m, 0);
  // depthSearch({}, m, 0);
  // std::cout << cota_ << std::endl;

  return cota_;
}

/**
 * @desc Build an inciial solution using a GRASP algorithm
 * @param {int} m Number of points allowed in solution
*/
void PodaSolution::graspBuild(int m) {
  int count{0};
  setupS();
  std::vector<float> center = getCenter();

  do {
    std::vector<int> candidatesIndex = {};
    std::vector<float> candidatesDistance = {};
    for (int i{0}; i < size_; ++i) {
      if (S_[i] == 1) continue;
      if (int(candidatesIndex.size()) < candidateSize_) { // List not filled yet
        candidatesIndex.push_back(i);
        candidatesDistance.push_back(distanceTo(puntos_[i], center));
        continue;
      }
      int highestIndex = indexOfBiggest(candidatesDistance);
      float newDistance = distanceTo(puntos_[i], center);
      if (newDistance > candidatesDistance[highestIndex]) { // Update if distance from center is greater (maximize)
        candidatesIndex[highestIndex] = i;
        candidatesDistance[highestIndex] = newDistance;
      }
    }
    int index = randomInt(int(candidatesIndex.size()) - 1);
    S_[candidatesIndex[index]] = 1;
    center = getCenterOfSolution(S_); // Update center based off points in solution
    count++;
  } while (count < m);

  return;
}

/**
 * @desc Build an inciial solution using a Greedy algorithm
 * @param {int} m Number of points allowed in solution
*/
void PodaSolution::greedyBuild(int m) {
  int count{0};
  setupS();
  std::vector<float> center = getCenter();

  do {
    float farthestPointDistance = 0.0;
    int farthestPointIndex = -1;
    for (int i{0}; i < size_; ++i) {
      if (S_[i] == 1) continue;
      if (farthestPointIndex == -1) { // Index not setup yet
        farthestPointIndex = i;
        farthestPointDistance = distanceTo(puntos_[i], center);
        continue;
      }
      float newDistance = distanceTo(puntos_[i], center);
      if (newDistance > farthestPointDistance) { // Update if distance from center is greater (maximize)
        farthestPointIndex = i;
        farthestPointDistance = newDistance;
      }
    }
    S_[farthestPointIndex] = 1;
    center = getCenterOfSolution(S_); // Update center based off points in solution
    count++;
  } while (count < m);

  return;
}

/**
 * @desc Uses a branching strategy that involves visiting the node with the highest upper quote
 * @param {std::vector<int>} S Partial solution to evaluate
 * @param {int} m Number of points allowed in solution
 * @param {int} pointCount Number of points in current partial solution
*/
void PodaSolution::widthSearch(std::vector<int> S, int m, int pointCount) {
  if (int(S.size()) == size_ || pointCount == m) { // A valid solution has been reached
    while (int(S.size()) < size_) { // If all points added, fill in extra slots
      S.push_back(0);
    }
    float newVal = getTotalDistance(S);
    if (newVal > getTotalDistance(S_)) {
      cota_ = newVal;
      S_ = S;
    }
    return;
  }

  std::vector<int> push0{S}, push1{S};
  push0.push_back(0);
  push1.push_back(1);
  float val0{getUpperQuota(push0, m, pointCount)}, val1{getUpperQuota(push1, m, pointCount + 1)};
  nodos_generados_ += 2;
  // std::cout << val0 << " and " << val1 << " bigger than " << cota_ << std::endl;

  if (val0 >= val1 && val0 > cota_) { // Evaluate adding a 0 first
    widthSearch(push0, m, pointCount);
    if (val1 > cota_) {
      widthSearch(push1, m, pointCount + 1);
    }
  } else if (val1 > cota_) {  // EValuate adding a 1 first
    widthSearch(push1, m, pointCount + 1);
    if (val0 > cota_) {
      widthSearch(push0, m, pointCount);
    }
  }

  // ENABLE ONLY THE FOLLOWING TO EXPLORE ALL NODES
  // widthSearch(push0, m, pointCount);
  // widthSearch(push1, m, pointCount + 1);
  
  return;
}

/**
 * @desc Uses a branching strategy that involves visiting the deepest node still over the lower quota
 * @param {std::vector<int>} S Partial solution to evaluate
 * @param {int} m Number of points allowed in solution
 * @param {int} pointCount Number of points in current partial solution
*/
void PodaSolution::depthSearch(std::vector<int> S, int m, int pointCount) {
  if (int(S.size()) == size_ || pointCount == m) { // A valid solution has been reached
    while (int(S.size()) < size_) { // If all points added, fill in extra slots
      S.push_back(0);
    }
    float newVal = getTotalDistance(S);
    if (newVal > getTotalDistance(S_)) {
      cota_ = newVal;
      S_ = S;
    }
    return;
  }

  // First case to evaluate
  std::vector<int> push0{S};
  push0.push_back(0);
  float val0{getUpperQuota(push0, m, pointCount)};
  if (val0 > cota_) {
    nodos_generados_++;
    widthSearch(push0, m, pointCount);
  }
  
  // Second case to evaluate
  std::vector<int> push1{S};
  push1.push_back(1);
  float val1{getUpperQuota(push1, m, pointCount + 1)};
  if (val1 > cota_) {
    nodos_generados_++;
    widthSearch(push1, m, pointCount + 1);
  }

  return;
}

/**
 * @desc Gets the center position of our group of points
 * @returns {std::vector<float>} Coordinates to the center position of the grouping
*/
std::vector<float> PodaSolution::getCenter() {
  std::vector<float> result;
  for (int i{0}; i < dimension_; ++i) {
    float currentSum{0.0};
    for (int j{0}; j < size_; ++j) {
      currentSum += puntos_[j][i];
    }  
    result.push_back(currentSum / size_);
  }
  return result;
}

/**
 * @desc Gets the center position of our group of points
 * @returns {std::vector<float>} Coordinates to the center position of the grouping
*/
std::vector<float> PodaSolution::getCenterOfSolution(std::vector<int> S) {
  std::vector<float> result;
  for (int i{0}; i < dimension_; ++i) {
    float currentSum{0.0};
    int count = 0;
    for (int j{0}; j < int(S.size()); ++j) {
      if (S[j] == 1) { // Only use points in solution
        currentSum += puntos_[j][i];
        count++;
      }
    }  
    result.push_back(currentSum / count);
  }
  return result;
}

/**
 * @desc Calculates the upper quota of a partial solution
 * @param {std::vector<int>} S Partial solution to evaluate
 * @param {int} m Number of points allowed in solution
 * @param {int} pointCount Number of points in current partial solution
*/
float PodaSolution::getUpperQuota(std::vector<int> S, int m, int pointCount) {
  int initialSize = S.size();
  if ((size_ - initialSize) < (m - pointCount)) return 0.0; // Not enough space to place remaining points
  
  while (int(S.size()) < size_) {
    S.push_back(0);
  }

  std::vector<float> center = {};
  if (pointCount == 0) {  // Nothing in solution, get center of all points
    center = getCenter();
  } else {  // Values in solution, get center point of solution
    center = getCenterOfSolution(S);
  }

  while (pointCount < m) {
    float farthestPointDistance = 0.0;
    int farthestPointIndex = -1;
    for (int i{initialSize}; i < size_; ++i) {
      if (S[i] == 1) continue;
      if (farthestPointIndex == -1) { // Index not setup yet
        farthestPointIndex = i;
        farthestPointDistance = distanceTo(puntos_[i], center);
        continue;
      }
      float newDistance = distanceTo(puntos_[i], center);
      if (newDistance > farthestPointDistance) { // Update if distance from center is greater (maximize)
        farthestPointIndex = i;
        farthestPointDistance = newDistance;
      }
    }
    S[farthestPointIndex] = 1;
    center = getCenterOfSolution(S);
    pointCount++;
  }

  return getTotalDistance(S);
}

/**
 * @desc Returns the index of the biggest element in an array
 * @param {std::vector<int>} arr Array to check for biggest element in
 * @return {int} Index of biggest element
*/
int PodaSolution::indexOfBiggest(std::vector<float> arr) {
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
 * @desc Generates a random number between 0 and a specified amount
 * @param {int} max Highets number that can be generated
 * @return {int} Randomly generated number
*/
int PodaSolution::randomInt(int max) {
  return rand() % (max + 1);
}

/**
 * @desc Getter for candidateSize_
 * @returns {int} candidateSize_
*/
int PodaSolution::getCandidateSize() {
  return candidateSize_;
}

/**
 * @desc Getter for nodos_generados_
 * @returns {int} nodos_generados_
*/
int PodaSolution::getGeneratedNodes() {
  return nodos_generados_;
}