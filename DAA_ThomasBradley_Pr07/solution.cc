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
 * @brief:   Program that solves titular problem. Here we define the Solution class
 */

#include "solution.h"

/**
 * @constructor
 * @desc Builds the values needed to evaluate a parallel machine scheduling problem given a
 *       file with the declaration of these
 * @param {std::string} nombre_fichero Name of the file containing the problem definition
*/
Solution::Solution(std::string nombre_fichero) {
  std::ifstream fichero;
  fichero.open(nombre_fichero);
  if (fichero.is_open()) { 
    int value{0};
    fichero >> new char >> tareas_;
    fichero >> new char >> maquinas_;
    fichero >> new char;
    for (int i{0}; i < tareas_; ++i) {
      fichero >> value;
      procesamiento_.push_back(value);
    }
    fichero >> new char;
    setup_.resize(tareas_ + 1);
    for (int i{0}; i <= tareas_; ++i) {
      for (int j{0}; j <= tareas_; ++j) {
        fichero >> value;
        setup_[i].push_back(value);
      }
    }
    S_.resize(maquinas_);
  } else { // Fichero no se pudo abrir
    std::cerr << "Error al abrir fichero" << std::endl;
    exit(1);
  }
  fichero.close();
}

/**
 * @desc Builds the t matrix comprized of Pi + Sij
*/
void Solution::buildT() {
  t_.resize(tareas_ + 1);
  for (int i{0}; i < tareas_ + 1; ++i) {
    for (int j{0}; j < tareas_; ++j) {
      t_[i].push_back(procesamiento_[j] + setup_[i][j + 1]);
    }
  }
}

/**
 * @desc Prints Machines and the tasks they've been assigned
*/
void Solution::printS() {
  for (int i{0}; i < int(S_.size()); ++i) {
    std::cout << "Maquina " << i + 1 << ": ";
    for (int j{0}; j < int(S_[i].size()); ++j) {
      std::cout << S_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

/**
 * @desc Returns the number of tasks
 * @return {int} Number of tasks
*/
int Solution::getTasks() {
  return tareas_;
}

/**
 * @desc Returns the number of machines
 * @return {int} Number of machines
*/
int Solution::getMachines() {
  return maquinas_;
}

/**
 * @desc Checks inserting all tasks within a machine into different positions
 * @param {std::vector<std::vector<int>>&} Reference to grouping of machines to find local optimal for
 * @returns {int} TCT of the lowest resulting Solution
*/
int Solution::internalInsertion(std::vector<std::vector<int>>& S) {
  int min{getGlobalTCT(S_)}, prevMin{min}, bestK{0}, bestN{0}, bestI{0};
  do {
    prevMin = min;
    for (int i{0}; i < maquinas_; ++i) {  // Chosen Machine
      for (int k{0}; k < int(S[i].size()); ++k) {  // Tasks locationg to give from giver
        for (int n{0}; n < int(S[i].size()); ++n) {  // Place to receive task for receiver, to <= because we reduce size when erasing
          if (k == n) continue;
          int takeAway = getMachineTCT(S[i]);
          std::vector<int> tester = S[i];
          tester.erase(tester.begin() + k);
          tester.insert(tester.begin() + n, S[i][k]);
          int result = prevMin - takeAway + getMachineTCT(tester);
          if (result < min) {
            min = result;
            bestK = k;
            bestN = n;
            bestI = i;
          }
        }
      }
    }
    if (min < prevMin) {
      int insertVal = S[bestI][bestK];
      S[bestI].erase(S[bestI].begin() + bestK);
      S[bestI].insert(S[bestI].begin() + bestN, insertVal);
    }
  } while (min < prevMin);
  return min;
}

/**
 * @desc Checks inserting all elements into all other positions in other machines
 * @param {std::vector<std::vector<int>>&} Reference to grouping of machines to find local optimal for
 * @returns {int} TCT of the lowest resulting Solution
*/
int Solution::externalInsertion(std::vector<std::vector<int>>& S) {
  int min{getGlobalTCT(S_)}, prevMin{min}, bestK{0}, bestN{0}, bestI{0}, bestJ{0};
  do {
    prevMin = min;
    for (int i{0}; i < maquinas_; ++i) {  // Machine to take from
      for (int j{0}; j < maquinas_; ++j) {  // Machine to recieve
        if (i == j) continue;
        for (int k{0}; k < int(S[i].size()); ++k) {  // Tasks locationg to give from giver
          for (int n{0}; n <= int(S[j].size()); ++n) {  // Place to receive task for receiver
            int takeAwayI = getMachineTCT(S[i]);
            int takeAwayJ = getMachineTCT(S[j]);
            std::vector<int> removedI = S[i];
            removedI.erase(removedI.begin() + k);
            int addI = getMachineTCT(removedI);
            std::vector<int> addedJ = S[j];
            addedJ.insert(addedJ.begin() + n, S[i][k]);
            int addJ = getMachineTCT(addedJ);
            int result = prevMin - takeAwayI - takeAwayJ + addI + addJ;
            if (result < min) {
              min = result;
              bestK = k;
              bestN = n;
              bestI = i;
              bestJ = j;
            }
          }
        }
      }
    }
    if (min < prevMin) {
      int insertVal = S[bestI][bestK];
      S[bestI].erase(S[bestI].begin() + bestK);
      S[bestJ].insert(S[bestJ].begin() + bestN, insertVal);
    }
  } while (min < prevMin);
  return min;
}

/**
 * @desc Checks swapping elements of all tasks within a machine
 * @param {std::vector<std::vector<int>>&} Reference to grouping of machines to find local optimal for
 * @returns {int} TCT of the lowest resulting Solution
*/
int Solution::internalInterchange(std::vector<std::vector<int>>& S) {
  int min{getGlobalTCT(S_)}, prevMin{min}, bestK{0}, bestN{0}, bestI{0};
  do {
    prevMin = min;
    for (int i{0}; i < maquinas_; ++i) {  // Chosen Machine
      for (int k{0}; k < int(S[i].size()); ++k) {  // Tasks locationg to give from giver
        for (int n{0}; n < int(S[i].size()); ++n) {  // Place to receive task for receiver
          if (k == n) continue;
          std::vector<int> tester = S[i];
          int temp = tester[k];
          tester[k] = tester[n];
          tester[n] = temp;
          int result = prevMin - getMachineTCT(S[i]) + getMachineTCT(tester);
          if (result < min) {
            min = result;
            bestK = k;
            bestN = n;
            bestI = i;
          }
        }
      }
    }
    if (min < prevMin) {
      int temp = S[bestI][bestK];
      S[bestI][bestK] = S[bestI][bestN];
      S[bestI][bestN] = temp;
    }
  } while (min < prevMin);
  return min;
}

/**
 * @desc Checks swapping elements of all tasks between machines
 * @param {std::vector<std::vector<int>>&} Reference to grouping of machines to find local optimal for
 * @returns {int} TCT of the lowest resulting Solution
*/
int Solution::externalInterchange(std::vector<std::vector<int>>& S) {
  int min{getGlobalTCT(S_)}, prevMin{min}, bestK{0}, bestN{0}, bestI{0}, bestJ{0};
  do {
    prevMin = min;
    for (int i{0}; i < maquinas_; ++i) {  // Machine to take from
      for (int j{0}; j < maquinas_; ++j) {  // Machine to recieve
        if (i == j) continue;
        for (int k{0}; k < int(S[i].size()); ++k) {  // Tasks locationg to give from giver
          for (int n{0}; n < int(S[j].size()); ++n) {  // Place to receive task for receiver
            int takeAwayI = getMachineTCT(S[i]);
            int takeAwayJ = getMachineTCT(S[j]);
            std::vector<int> testerI = S[i];
            std::vector<int> testerJ = S[j];
            int temp = testerI[k];
            testerI[k] = testerJ[n];
            testerJ[n] = temp;
            int result = prevMin - takeAwayI - takeAwayJ + getMachineTCT(testerI) + getMachineTCT(testerJ);
            if (result < min) {
              min = result;
              bestK = k;
              bestN = n;
              bestI = i;
              bestJ = j;
            }
          }
        }
      }
    }
    if (min < prevMin) {
      int temp = S[bestI][bestK];
      S[bestI][bestK] = S[bestJ][bestN];
      S[bestJ][bestN] = temp;
    }
  } while (min < prevMin);
  return min;
}

/* CODE TO PRINT OUT STORED VALUES
std::cout << "Tareas: " << tareas_ << std::endl;
  std::cout << "Maquinas: " << maquinas_ << std::endl << std::endl;
  for (int i{0}; i < procesamiento_.size(); ++i) {
    std::cout << procesamiento_[i] << " ";
  }
  std::cout << std::endl << std::endl;
  for (int i{0}; i < setup_.size(); ++i) {
    for (int j{0}; j < setup_[0].size(); ++j) {
      std::cout << setup_[i][j] << " ";
    }
    std::cout << std::endl;
  }
*/