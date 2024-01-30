/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 01: Análisis de complejidad
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    30.jan.2024
 * @brief:   Multiplicación de matrices siguiendo principios SOLID y usando el patrón estrategia
 *           Aqui se tiene la implementación de la clase Strategy
 */

// g++ --std=c++14 -o strategy DAA_ThomasBradley_Pr01.cc
// ./strategy 6

#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <time.h>
#include <vector>

class Strategy {
  public: 
	  virtual void printProduct(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2) = 0;
};

class ReadRow : public Strategy  {
  void printProduct(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2) {
    std::vector<std::vector<int>> result(int(matrix1.size()));
    for (int i{0}; i < int(matrix1.size()); i++) {
      for (int j{0}; j < int(matrix2[0].size()); j++) {
        int tempNum = 0;
        for (int z{0}; z < int(matrix1[0].size()); z++) {
          tempNum = tempNum + (matrix1[i][z] * matrix2[z][j]);
        }
        result[i].push_back(tempNum);
      }
    }

    std::cout << "Row Multiplication:" << std::endl;
    for (int i{0}; i < int(result.size()); i++) {
      for (int j{0}; j < int(result[0].size()); j++) {
        std::cout << result[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
};

class ReadColumn : public Strategy  {
  void printProduct(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2) {
    std::vector<std::vector<int>> result(int(matrix1.size()));
    for (int i{0}; i < int(matrix2.size()); i++) {
      for (int j{0}; j < int(matrix1[0].size()); j++) {
        int tempNum = 0;
        for (int z{0}; z < int(matrix1.size()); z++) {
          tempNum = tempNum + (matrix1[z][j] * matrix2[i][z]);
        }
        result[j].push_back(tempNum);
      }
    }

    std::cout << "Column Multiplication:" << std::endl;
    for (int i{0}; i < int(result.size()); i++) {
      for (int j{0}; j < int(result[0].size()); j++) {
        std::cout << result[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
};