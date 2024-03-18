/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 06: Problema del Viajante de Comercio (TSP)
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    19.mar.2024
 * @brief:   Random TSP problem generator
 * @example: ./generator
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

/**
 * @desc Generates a random integer within a specified range
 * @param {int} min Minimum value of random number
 * @param {int} max Maximum value of random number
*/
int generateRandom(int min, int max) {
  return min + rand() % (max - min + 1);
}

/**
 * @desc Generates a TSP file
 * @param {std::string} filename Name and directory of the output file
 * @param {int} numNodes Total number of nodes in the TSP
 * @param {int} minValue Minimum value of an edge between two nodes
 * @param {int} maxValue Maximum value of an edge between two nodes
*/
void generateTSPFile(std::string filename, int numNodes, int minValue, int maxValue) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to create file." << std::endl;
    return;
  }
  file << numNodes << std::endl;
  srand(time(0)); // Seed for random number

  for (char i = 'A'; i < 'A' + numNodes; ++i) { // Left Char in file
    for (char j = i + 1; j < 'A' + numNodes; ++j) { // Right Char in file
      int value = generateRandom(minValue, maxValue);
      file << i << " " << j << " " << value << std::endl;
    }
  }

  file.close();
  std::cout << "File '" << filename << "' generated successfully." << std::endl;
}

int main() {
  generateTSPFile("../grafos/3_nodos.txt", 3, 5, 50);
  return 0;
}