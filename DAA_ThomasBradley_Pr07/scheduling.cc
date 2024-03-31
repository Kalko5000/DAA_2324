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
 * @brief:   Program that solves titular problem. Here we define the Scheduling class
 */

#include "scheduling.h"

/**
 * @constructor
 * @desc Builds a matrix for our TSP problem from the definition of such stored in a file
 * @param {std::string} nombre_fichero Name of the fiel containing the problem definition
*/
Scheduling::Scheduling(std::string nombre_fichero) {
  value_ = 0;
  time_ = 0;
  path_ = {};
  std::ifstream fichero;
  fichero.open(nombre_fichero);
  if (fichero.is_open()) { 
    std::cout << "Reading file" << std::endl;
  } else { // Fichero no se pudo abrir
    std::cerr << "Error al abrir fichero" << std::endl;
    exit(1);
  }
  fichero.close();
}

/**
 * @desc Fills the node matrix with zeros
 * @param {int} size Size we want our node matrix to be
*/
void Scheduling::buildNodes(int size) {
  nodes_.resize(size);
  for(int i{0}; i < int(nodes_.size()); ++i) {
    nodes_[i].resize(size);
  }
}

/* CODE TO PRINT OUT VALUE MATRIX
for(int i{0}; i < int(nodes_.size()); ++i) {
      for(int j{0}; j < int(nodes_[0].size()); ++j) {
        std::cout << nodes_[i][j] << " ";
      }
    std::cout << std::endl;
    }
*/