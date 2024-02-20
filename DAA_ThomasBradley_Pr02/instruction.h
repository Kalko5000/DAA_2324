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
 * @brief:   Diseño y funcionamiento de una maquina RAM. Aqui esta la declaracion de la clase Instruction y la clase Context
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Instruction {
 public:
  virtual void Load(std::vector<int>& registros, std::string op) = 0;
  virtual void Store(std::vector<int>& registros, std::string op) = 0;
  virtual void Add(std::vector<int>& registros, std::string op) = 0;
  virtual void Sub(std::vector<int>& registros, std::string op) = 0;
  virtual void Mult(std::vector<int>& registros, std::string op) = 0;
  virtual void Div(std::vector<int>& registros, std::string op) = 0;
  virtual void Read(std::vector<int>& registros, std::ifstream& nombre_in, std::string op) = 0;
  virtual void Write(std::vector<int>& registros, std::ofstream& nombre_out, std::string op) = 0;
  virtual void Jump(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter) = 0;
  virtual void Jzero(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0) = 0;
  virtual void Jgtz(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0) = 0;
};

class Constant : public Instruction {
 public:
  void Load(std::vector<int>& registros, std::string op);
  void Store(std::vector<int>& registros, std::string op);
  void Add(std::vector<int>& registros, std::string op);
  void Sub(std::vector<int>& registros, std::string op);
  void Mult(std::vector<int>& registros, std::string op);
  void Div(std::vector<int>& registros, std::string op);
  void Read(std::vector<int>& registros, std::ifstream& nombre_in, std::string op);
  void Write(std::vector<int>& registros, std::ofstream& nombre_out, std::string op);
  void Jump(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter);
  void Jzero(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0);
  void Jgtz(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0);
};

class Registro : public Instruction {
 public:
  void Load(std::vector<int>& registros, std::string op);
  void Store(std::vector<int>& registros, std::string op);
  void Add(std::vector<int>& registros, std::string op);
  void Sub(std::vector<int>& registros, std::string op);
  void Mult(std::vector<int>& registros, std::string op);
  void Div(std::vector<int>& registros, std::string op);
  void Read(std::vector<int>& registros, std::ifstream& nombre_in, std::string op);
  void Write(std::vector<int>& registros, std::ofstream& nombre_out, std::string op);
  void Jump(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter);
  void Jzero(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0);
  void Jgtz(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0);
};

class RegistroContenido : public Instruction {
 public:
  void Load(std::vector<int>& registros, std::string op);
  void Store(std::vector<int>& registros, std::string op);
  void Add(std::vector<int>& registros, std::string op);
  void Sub(std::vector<int>& registros, std::string op);
  void Mult(std::vector<int>& registros, std::string op);
  void Div(std::vector<int>& registros, std::string op);
  void Read(std::vector<int>& registros, std::ifstream& nombre_in, std::string op);
  void Write(std::vector<int>& registros, std::ofstream& nombre_out, std::string op);
  void Jump(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter);
  void Jzero(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0);
  void Jgtz(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0);
};