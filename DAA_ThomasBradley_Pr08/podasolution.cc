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
  widthSearch({}, m, 0);
  // std::cout << cota_ << std::endl;

  return cota_;
}

/**
 * @desc
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
 * @desc
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
 * @desc
*/
void PodaSolution::widthSearch(std::vector<int> S, int m, int pointCount) {
  nodos_generados_++;

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
  // std::cout << val0 << " and " << val1 << " bigger than " << cota_ << std::endl;

  if (val0 >= val1 && val0 > cota_) {
    widthSearch(push0, m, pointCount);
  } else if (val1 > cota_) {
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
 * @desc
*/
float PodaSolution::getUpperQuota(std::vector<int> S, int m, int pointCount) {
  int initialSize = S.size();
  if ((size_ - initialSize) < (m - pointCount)) return 0.0; // Not enough space to place remaining points
  
  while (int(S.size()) < size_) {
    S.push_back(0);
  }

  std::vector<float> center = getCenterOfSolution(S);
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
 * @desc
*/
int PodaSolution::getCandidateSize() {
  return candidateSize_;
}

/**
 * @desc
*/
int PodaSolution::getGeneratedNodes() {
  return nodos_generados_;
}