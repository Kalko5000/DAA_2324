/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 08: B&B - Maximum Diversity Problem
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    21.apr.2024
 * @brief:   Program that solves titular problem. Here we define the VorazSolution class
 */

#include "vorazsolution.h"

/**
 * @desc Evaluates the MDP problem using a Greedy algorithm 
 * @param {int} m Number of points to include in solution
 * @returns {float} Resulting distance from found solution
*/
float VorazSolution::evaluate(int m) {
  int count{0};
  setupS();
  std::vector<float> center = getCenter();

  do {
    float farthestPointDistance = FLT_MAX;
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

  // DEBUG
  // printS()

  return getTotalDistance();
}

/**
 * @desc Calculates the distance between two points
 * @param {std::vector<float>} start Initial point
 * @param {std::vector<float>} end Destination point
 * @returns {float} Resulting distance between the two
*/
float VorazSolution::distanceTo(std::vector<float> start, std::vector<float> end) {
  float totalSum = 0.0;
  for (int i{0}; i < dimension_; ++i) {
    totalSum += std::pow(end[i] - start[i], 2);
  }
  return std::sqrt(totalSum);
}

/**
 * @desc Returns the distance between all points in the solution
 * @returns {float} Resulting distance
*/
float VorazSolution::getTotalDistance() {
  std::vector<int> indexList;
  for (int i{0}; i < size_; ++i) {
    if (S_[i] == 1) indexList.push_back(i);
  }
  float totalSum = 0.0;
  for (int i{0}; i < int(indexList.size() - 1); ++i) {
    totalSum += distanceTo(puntos_[indexList[i]], puntos_[indexList[i + 1]]);
  }
  totalSum += distanceTo(puntos_[indexList[int(indexList.size() - 1)]], puntos_[indexList[0]]);
  return totalSum;
}

/**
 * @desc Gets the center position of our group of points
 * @returns {std::vector<float>} Coordinates to the center position of the grouping
*/
std::vector<float> VorazSolution::getCenter() {
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
std::vector<float> VorazSolution::getCenterOfSolution() {
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