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
  int counter{0};
  float newVal{0}, min{0};
  srand(time(0)); // Seed for random number

  do {  // Local Optimal Search method implementations can be found in the base class -> Solution
    if (useGrasp_) {
      graspBuild(m);
    } else {
      greedyBuild(m);
    }
    std::vector<int> S = tabuSearch(S_);  // Can swap out to localSearch
    newVal = getTotalDistance(S);
    if (newVal > min) {
      min = newVal;
      bestS = S;
    }
    counter++;
  } while (counter < 10);

  S_ = bestS;
  return min;
}

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
    center = getCenterOfSolution(); // Update center based off points in solution
    count++;
  } while (count < m);

  return;
}

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
    center = getCenterOfSolution(); // Update center based off points in solution
    count++;
  } while (count < m);

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
std::vector<float> PodaSolution::getCenterOfSolution() {
  std::vector<float> result;
  for (int i{0}; i < dimension_; ++i) {
    float currentSum{0.0};
    int count = 0;
    for (int j{0}; j < size_; ++j) {
      if (S_[j] == 1) { // Only use points in solution
        currentSum += puntos_[j][i];
        count++;
      }
    }  
    result.push_back(currentSum / count);
  }
  return result;
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