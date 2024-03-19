/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 06: Problema del Viajante de Comercio (TSP)
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    21.mar.2023
 * @brief:   Framework para algoritmos de Programación Dinámica. Aqui se define la clase base TSP
 */

#include "tsp.h"

/**
 * @constructor
 * @desc Builds a matrix for our TSP problem from the definition of such stored in a file
 * @param {std::string} nombre_fichero Name of the fiel containing the problem definition
*/
TSP::TSP(std::string nombre_fichero) {
  value_ = 0;
  time_ = 0;
  path_ = {};
  std::ifstream fichero;
  fichero.open(nombre_fichero);
  if (fichero.is_open()) { 
    int size{0}; // Adjusting size of nodes vector
    fichero >> size;
    buildNodes(size);
    for(int i{0}; i < int(nodes_.size()); ++i) { // Saving all distances in a vector, assuming A = 0;
      for(int j{i}; j < int(nodes_[i].size()); ++j) {
        if(i == j) {
          nodes_[i][j] = 0;
          continue;
        }
        fichero >> new char >> new char;
        int cost{0};
        fichero >> cost;
        nodes_[i][j] = cost;
        nodes_[j][i] = cost;
      }
    } 
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
void TSP::buildNodes(int size) {
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