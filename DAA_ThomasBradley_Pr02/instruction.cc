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
 * @brief:   Diseño y funcionamiento de una maquina RAM. Aqui esta la definición de la clase Instruction
 */

#include "instruction.h"

// CONSTANT

void Constant::Load(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[0] = std::stoi(op);
}

void Constant::Store(std::vector<int>& registros, std::string op) {
  std::cerr << "No se puede hacer Store con una constante" << std::endl;
  exit(1);
}

void Constant::Add(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[0] += std::stoi(op);
}

void Constant::Sub(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[0] -= std::stoi(op);
}

void Constant::Mult(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[0] *= std::stoi(op);
}

void Constant::Div(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[0] /= std::stoi(op);
}

void Constant::Read(std::vector<int>& registros, std::ifstream& nombre_in, std::string op) {
  std::cerr << "No se puede hacer Read con una constante" << std::endl;
  exit(1);
}

void Constant::Write(std::vector<int>& registros, std::ofstream& nombre_out, std::string op) {
  op.erase(0, 1);
  nombre_out << stoi(op);
}

void Constant::Jump(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter) {
  for (int i{0}; i < int(bloques.size()); i++) {
    if (bloques[i].first == comparar + ':') {
      counter = bloques[i].second - 1;
      break;
    }
  }
}

void Constant::Jzero(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0) {
  if (r0 != 0) {
    return;
  }
  for (int i{0}; i < int(bloques.size()); i++) {
    if (bloques[i].first == comparar + ':') {
      counter = bloques[i].second - 1;
      break;
    }
  }
}

void Constant::Jgtz(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0) {
  if (r0 <= 0) {
    return;
  }
  for (int i{0}; i < int(bloques.size()); i++) {
    if (bloques[i].first == comparar + ':') {
      counter = bloques[i].second - 1;
      break;
    }
  }
}

// REGISTRO

void Registro::Load(std::vector<int>& registros, std::string op) {
  registros[0] = registros[std::stoi(op)];
}

void Registro::Store(std::vector<int>& registros, std::string op) {
  registros[std::stoi(op)] = registros[0];
}

void Registro::Add(std::vector<int>& registros, std::string op) {
  registros[0] += registros[std::stoi(op)];
}

void Registro::Sub(std::vector<int>& registros, std::string op) {
  registros[0] -= registros[std::stoi(op)];
}

void Registro::Mult(std::vector<int>& registros, std::string op) {
  registros[0] *= registros[std::stoi(op)];
}

void Registro::Div(std::vector<int>& registros, std::string op) {
  registros[0] /= registros[std::stoi(op)];
}

void Registro::Read(std::vector<int>& registros, std::ifstream& nombre_in, std::string op) {
  int temp{0};
  nombre_in >> temp;
  registros[std::stoi(op)] = temp;
}

void Registro::Write(std::vector<int>& registros, std::ofstream& nombre_out, std::string op) {
  if (std::stoi(op) == 0) {
    std::cerr << "No se puede hacer Write con el registro 0" << std::endl;
    exit(1);
  }
  nombre_out << registros[std::stoi(op)];
}

void Registro::Jump(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter) {
  for (int i{0}; i < int(bloques.size()); i++) {
    if (bloques[i].first == comparar + ':') {
      counter = bloques[i].second - 1;
      break;
    }
  }
}

void Registro::Jzero(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0) {
  if (r0 == 0) {
    for (int i{0}; i < int(bloques.size()); i++) {
      if (bloques[i].first == comparar + ':') {
        counter = bloques[i].second - 1;
        break;
      }
    }
  } else {
    return;
  }
}

void Registro::Jgtz(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0) {
  if (r0 <= 0) {
    return;
  }
  for (int i{0}; i < int(bloques.size()); i++) {
    if (bloques[i].first == comparar + ':') {
      counter = bloques[i].second - 1;
      break;
    }
  }
}

// REGISTRO CONTENIDO

void RegistroContenido::Load(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[0] = registros[registros[std::stoi(op)]];
}

void RegistroContenido::Store(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[registros[std::stoi(op)]] = registros[0];
}

void RegistroContenido::Add(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[0] += registros[registros[std::stoi(op)]];
}

void RegistroContenido::Sub(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[0] -= registros[registros[std::stoi(op)]];
}

void RegistroContenido::Mult(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[0] *= registros[registros[std::stoi(op)]];
}

void RegistroContenido::Div(std::vector<int>& registros, std::string op) {
  op.erase(0, 1);
  registros[0] /= registros[registros[std::stoi(op)]];
}

void RegistroContenido::Read(std::vector<int>& registros, std::ifstream& nombre_in, std::string op) {
  int temp{0};
  nombre_in >> temp;
  op.erase(0, 1);
  registros[registros[std::stoi(op)]] = temp;
}

void RegistroContenido::Write(std::vector<int>& registros, std::ofstream& nombre_out, std::string op) {
  op.erase(0, 1);
  if (registros[std::stoi(op)] == 0) {
    std::cerr << "No se puede hacer Write con el registro 0" << std::endl;
    exit(1);
  }
  nombre_out << registros[registros[std::stoi(op)]];
}

void RegistroContenido::Jump(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter) {
  for (int i{0}; i < int(bloques.size()); i++) {
    if (bloques[i].first == comparar + ':') {
      counter = bloques[i].second - 1;
      break;
    }
  }
}

void RegistroContenido::Jzero(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0) {
  if (r0 == 0) {
    for (int i{0}; i < int(bloques.size()); i++) {
      if (bloques[i].first == comparar + ':') {
        counter = bloques[i].second - 1;
        break;
      }
    }
  } else {
    return;
  }
}

void RegistroContenido::Jgtz(std::vector<std::pair<std::string, int>>& bloques, std::string comparar, int& counter, int& r0) {
  if (r0 <= 0) {
    return;
  }
  for (int i{0}; i < int(bloques.size()); i++) {
    if (bloques[i].first == comparar + ':') {
      counter = bloques[i].second - 1;
      break;
    }
  } 
}