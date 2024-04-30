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
 * @brief:   Program that solves titular problem. Here we define the Solution class
 */

#include "solution.h"

/**
 * @constructor
 * @desc Builds the values needed to solve a maximum diversity problem from a file
 * @param {std::string} nombre_fichero Name of the file containing the problem definition
*/
Solution::Solution(std::string nombre_fichero) {
  std::ifstream fichero;
  fichero.open(nombre_fichero);
  if (fichero.is_open()) { 
    std::string value{0};
    fichero >> size_;
    fichero >> dimension_;
    puntos_.resize(size_);
    for (int i{0}; i < int(puntos_.size()); ++i) {
      for (int j{0}; j < dimension_; ++j) {
        fichero >> value;
        puntos_[i].push_back(stringToFloat(value));
      }
    }
    setupS();
    // printS();
  } else { // Fichero no se pudo abrir
    std::cerr << "Error al abrir fichero" << std::endl;
    exit(1);
  }
  fichero.close();
}

/**
 * @desc Converts from a string using a coma to a floating point value
 * @param {std::string} word String we want to convert
 * @returns {float} Converted floating point number
*/
float Solution::stringToFloat(std::string word) {
  for (int i{0}; i < int(word.size()); ++i) {
    if (word[i] == ',') {
      word[i] = '.';
      break;
    }
  }
  return std::stof(word);
}

/**
 * @desc Calculates the distance between two points
 * @param {std::vector<float>} start Initial point
 * @param {std::vector<float>} end Destination point
 * @returns {float} Resulting distance between the two
*/
float Solution::distanceTo(std::vector<float> start, std::vector<float> end) {
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
float Solution::getTotalDistance(std::vector<int> S) {
  std::vector<int> indexList;
  for (int i{0}; i < size_; ++i) {
    if (S[i] == 1) indexList.push_back(i);
  }
  float totalSum = 0.0;
  for (int i{0}; i < int(indexList.size() - 1); ++i) {
    totalSum += distanceTo(puntos_[indexList[i]], puntos_[indexList[i + 1]]);
  }
  totalSum += distanceTo(puntos_[indexList[int(indexList.size() - 1)]], puntos_[indexList[0]]);
  return totalSum;
}

/**
 * @desc Prints all points and whether or not they are part of the solution
*/
void Solution::setupS() {
  S_.resize(size_);
  for (int i{0}; i < int(S_.size()); ++i) {
    S_[i] = 0;
  }
}

/**
 * @desc Prints all points and whether or not they are part of the solution
*/
void Solution::printS() {
  for (int i{0}; i < int(S_.size()); ++i) {
    std::cout << "Punto " << i + 1;
    if (S_[i] == 0) std::cout << " no incuido: ";
    else std::cout << " incuido: ";
    for (int j{0}; j < dimension_; ++j) {
      std::cout << puntos_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

/**
 * @desc Returns the size of the problem (number of points)
 * @return {int} Size of the problem (number of points)
*/
int Solution::getSize() {
  return size_;
}

/**
 * @desc Returns the dimension on each point
 * @return {int} Dimension on each point
*/
int Solution::getDimension() {
  return dimension_;
}

/**
 * @desc Getter for the state of the current solution
 * @returns {std::string} String showcasing which points for part of the solution (those set to 1)
*/
std::string Solution::getS() {
  std::string result{""};
  for (int i{0}; i < int(S_.size()); ++i) {
    result += std::to_string(S_[i]);
  }
  return result;
}

/**
 * @desc 
 * @param {std::vector} S
 * @returns {std::vector<int>}
*/
std::vector<int> Solution::localSearch(std::vector<int> S) {
  std::vector<int> maxSol = S;
  float maxFound = getTotalDistance(S), prevMax{maxFound};

  do {
    prevMax = maxFound;
    S = maxSol;
    for (int i{0}; i < size_; ++i) {  // First point to swap
      for (int j{0}; j < size_; ++j) {  // Second point to swap
        if (i == j || S[i] == S[j]) continue;
        std::vector<int> tempSol = S;
        int tempVal = tempSol[i];
        tempSol[i] = tempSol[j];
        tempSol[j] = tempVal;
        float result = getTotalDistance(tempSol);
        if (result > maxFound) {
          maxFound = result;
          maxSol = tempSol;
        }
      }
    }
  } while (maxFound > prevMax);

  return maxSol;
}

/**
 * @desc Tabu search that locks a movement for 3 turns after it has been done
 * @param {std::vector} S Original solution to problem
 * @returns {std::vector<int>} Imporved solutiong after passing through algorithm
*/
std::vector<int> Solution::tabuSearch(std::vector<int> S) {
  std::vector<std::pair<int, int>> swaps;
  std::vector<int> maxSol = S;
  float maxFound = getTotalDistance(S), prevMax{maxFound};

  do {
    int usedI, usedJ;
    prevMax = maxFound;
    S = maxSol;
    for (int i{0}; i < size_; ++i) {  // First point to swap
      for (int j{0}; j < size_; ++j) {  // Second point to swap
        if (i == j || S[i] == S[j]) continue;
        bool valid{true};
        if (int(swaps.size()) > 0) {  // There are locked movements
          for (int i{0}; i < int(swaps.size()); ++i) {
            if ((swaps[i].first == i && swaps[i].second == j) || (swaps[i].first == j && swaps[i].second == i)) {
              valid = false;
              break;
            }
          }
        }
        if (valid) {  // Movement has not been locked
          std::vector<int> tempSol = S;
          int tempVal = tempSol[i];
          tempSol[i] = tempSol[j];
          tempSol[j] = tempVal;
          float result = getTotalDistance(tempSol);
          if (result > maxFound) {
            maxFound = result;
            maxSol = tempSol;
            usedI = i;
            usedJ = j;
          }
        }
      }
    }
    if (int(swaps.size()) > 3) {  // Remove movement that has been locked for 3 turns
      swaps.erase(swaps.begin());
    }
    swaps.push_back(std::make_pair(usedI, usedJ));  // Add latest locked movement
  } while (maxFound > prevMax); // Stop condition is x amount of iterations, continues forward even if solution is worse

  return maxSol;
}