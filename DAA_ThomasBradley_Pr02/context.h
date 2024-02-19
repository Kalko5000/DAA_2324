/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 02: Simulador de la máquina RAM
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    12.feb.2023
 * @brief:   Diseño y funcionamiento de una maquina RAM. Aqui esta la declaracion de la clase Context
 */

#include <iostream>
#include <fstream>
#include <string>
#include "instruction.h"

class Context {
 public:
  Context(Instruction *instruction);
  void setContext(Instruction *instruction);
  void ContextLoad(std::vector<int>& registros, std::string op);
  void ContextStore(std::vector<int>& registros, std::string op);
  void ContextAdd(std::vector<int>& registros, std::string op);
  void ContextSub(std::vector<int>& registros, std::string op);
  void ContextMult(std::vector<int>& registros, std::string op);
  void ContextDiv(std::vector<int>& registros, std::string op);
  void ContextRead(std::vector<int>& registros, std::ifstream& mobre_in, std::string op);
  void ContextWrite(std::vector<int>& registros, std::ofstream& mobre_out, std::string op);
  void ContextJump(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter);
  void ContextJzero(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0);
  void ContextJgtz(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0);
 private:
	Instruction *_instruction;
};