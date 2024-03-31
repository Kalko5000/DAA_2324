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
 * @brief:   Program that solves titular problem. Here we define the VorazScheduling class
 */

#include "vorazscheduling.h"

/**
 * @desc Constructive Greedy algorithm for a parallel machine scheduling problem
*/
void VorazScheduling::evaluate() {
  std::vector<std::vector<int>> S(maquinas_); // Stores de indexes of the tasks
  std::vector<int> used; // Stores used tasks in an easier format
  for (int i{0}; i < maquinas_; ++i) {
    int minIndex = 0;
    for (int j{0}; j < int(procesamiento_.size()); ++j) {
      if (procesamiento_[j] < procesamiento_[minIndex]) {
        bool valid{true};
        for (int n{0}; n < int(used.size()); ++n) {
          if (j == used[n]) {
            valid = false;
            break;
          }
        }
        if (valid) {
          minIndex = j;
        }
      }
    }
    S[i].push_back(minIndex);
    used.push_back(minIndex);
  }

  do {
    int minMachine{-1}, minDest{-1};
    for (int i{0}; i < maquinas_; ++i) {
      for (int j{0}; j < tareas_; ++j) {
        if (minMachine == -1 || minDest == -1) {
          bool valid{true};
          for (int n{0}; n < int(used.size()); ++n) {
            if (j == used[n]) {
              valid = false;
              break;
            }
          }
          if (valid) {
            minMachine = i;
            minDest = j;
          }
          continue;
        } 
        int task = S[i][int(S[i].size() - 1)];
        int minTask = S[minMachine][int(S[minMachine].size() - 1)];
        if (setup_[task + 1][j + 1] < setup_[minTask + 1][minDest + 1]) {
          bool valid{true};
          for (int n{0}; n < int(used.size()); ++n) {
            if (j == used[n]) {
              valid = false;
              break;
            }
          }
          if (valid) {
            minMachine = i;
            minDest = j;
          }
        }
      }
    }
    S[minMachine].push_back(minDest);
    used.push_back(minDest);
  } while (int(used.size()) < tareas_);


  for (int i{0}; i < int(S.size()); ++i) {
    for (int j{0}; j < int(S[i].size()); ++j) {
      std::cout << S[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

/* CODE TO SHOW VALUES OF S
for (int i{0}; i < S.size(); ++i) {
    for (int j{0}; j < S[0].size(); ++j) {
      std::cout << S[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
*/