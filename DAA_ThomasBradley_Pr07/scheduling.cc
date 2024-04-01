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
 * @desc Builds the values needed to evaluate a parallel machine scheduling problem given a
 *       file with the declaration of these
 * @param {std::string} nombre_fichero Name of the file containing the problem definition
*/
Scheduling::Scheduling(std::string nombre_fichero) {
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
void Scheduling::buildT() {
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
void Scheduling::printS() {
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
int Scheduling::getTasks() {
  return tareas_;
}

/**
 * @desc Returns the number of machines
 * @return {int} Number of machines
*/
int Scheduling::getMachines() {
  return maquinas_;
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