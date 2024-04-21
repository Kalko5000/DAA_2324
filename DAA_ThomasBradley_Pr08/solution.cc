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