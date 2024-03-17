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

TSP::TSP(std::string nombre_fichero) {
  value_ = 0;
  time_ = 0;
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
  for(int i{0}; i < int(nodes_.size()); ++i) {
  for(int j{0}; j < int(nodes_[i].size()); ++j) {
    std::cout << nodes_[i][j] << " ";
  }
  std::cout << std::endl;
}
}

void TSP::buildNodes(int size) {
  nodes_.resize(size);
  for(int i{0}; i < int(nodes_.size()); ++i) {
    nodes_[i].resize(size);
  }
}

/*
for(int i{0}; i < int(nodes_.size()); ++i) {
  for(int j{0}; j < int(nodes_[i].size()); ++j) {
    std::cout << nodes_[i][j] << " ";
  }
  std::cout << std::endl;
}
*/