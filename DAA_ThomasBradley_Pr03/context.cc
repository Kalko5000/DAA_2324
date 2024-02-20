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
 * @brief:   Diseño y funcionamiento de una maquina RAM. Aqui esta la definición de la clase Context
 */

#include "context.h"

Context::Context(Instruction *instruction) {
  _instruction = instruction;
} 

void Context::setContext(Instruction *instruction) {
  _instruction = instruction;
}

void Context::ContextLoad(std::vector<int>& registros, std::string op) {
  _instruction->Load(registros, op);
}

void Context::ContextStore(std::vector<int>& registros, std::string op) {
  _instruction->Store(registros, op);
}

void Context::ContextAdd(std::vector<int>& registros, std::string op) {
  _instruction->Add(registros, op);
}

void Context::ContextSub(std::vector<int>& registros, std::string op) {
  _instruction->Sub(registros, op);
}

void Context::ContextMult(std::vector<int>& registros, std::string op) {
  _instruction->Mult(registros, op);
}

void Context::ContextDiv(std::vector<int>& registros, std::string op) {
  _instruction->Div(registros, op);
}

void Context::ContextRead(std::vector<int>& registros, std::ifstream& nombre_in, std::string op) {
  _instruction->Read(registros, nombre_in, op);
}

void Context::ContextWrite(std::vector<int>& registros, std::ofstream& nombre_out, std::string op) {
  _instruction->Write(registros, nombre_out, op);
}

void Context::ContextJump(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter) {
  _instruction->Jump(bloques, comparar, counter);
}

void Context::ContextJzero(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0) {
  _instruction->Jzero(bloques, comparar, counter, r0);
}

void Context::ContextJgtz(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0) {
  _instruction->Jgtz(bloques, comparar, counter, r0);
}

void Context::ContextAdv(std::vector<int>& registros, std::string op) {
  _instruction->Adv(registros, op);
}