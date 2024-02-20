/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 02: Simulador de la máquina RAM
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    20.feb.2024
 * @brief:   Diseño y funcionamiento de una maquina RAM. Aqui esta la declaracion de la clase Ram
 */

#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cstring>
#include "context.h"

class Ram {
 public:
  Ram(std::string nombre_ram);
  void run(std::string nombre_in, std::string nombre_out);
  void runDebug(std::string nombre_in, std::string nombre_out);
  int getInstrucciones();
  void printRegistros();
  void printFile(std::string file_name, int pos);
  void printStep(std::string nombre_in, int output_pos, std::ofstream& output_file);
  void addProgram(std::string entrada, std::string operando);
 private:
  std::vector<std::vector<std::pair<std::string, std::string>>> programa; // Donde se garda el programa
  std::vector<std::pair<std::string, int>> bloques; // Donde se guarda la posicion de las etiquetas en "programa"
  std::vector<int> registros;
  int instrucciones;
};