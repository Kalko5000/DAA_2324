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
 * @brief:   Diseño y funcionamiento de una maquina RAM
 */

// g++ --std=c++14 -o simulador instruction.cc context.cc ram.cc main.cc
// ./simulador tests/test1.ram tapes/numbers.in tapes/numbers.out 0

#include <iostream>
#include <fstream>
#include <string>
#include "ram.h"

/**
 * @desc Texto de ayuda para el correcto funcionamiento del código
*/
const void kHelpText() {
  std::cout << "simulador [1] [2] [3] [4]" << std::endl << std::endl;
  std::cout << "[1] = programa ram de entrada (.ram)" << std::endl;
  std::cout << "[2] = cinta de entrada (.in)" << std::endl;
  std::cout << "[3] = cinta de salida (.out)" << std::endl;
  std::cout << "[4] = 0,1,2 para elegir el modo debug" << std::endl;
  std::cout << "Se ejecutara el programa .ram leyendo los valores de .in y" << std::endl;
  std::cout << "escribiendo en el .out, de acuerdo con el numero debug" << std::endl;
}

/**
 * @desc Texto de como usar el programa y como encontrar más información sobre ella
*/
const void kFuncText() {
  std::cout << "Modo de empleo: simulador [PROGRAMA RAM] [INPUT TAPE] [OUTPUT TAPE] [DEBUG]" << std::endl;
  std::cout << "Pruebe 'ram --help' para más información" << std::endl;
}

/**
 * @desc Analiza los valores pasados por la linea de comandos
 * @param {int} kArgc número de comandos pasados
 * @param {int} argv[] array con el texto pasado por linea de comandos
*/
void Usage(const int kArgc, char* argv[]) {
  if (kArgc == 2) {
    if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
      kHelpText();
      exit(0);
    }
  } else if (kArgc != 5) {
    kFuncText();
    exit(1);
  } 
}

int main(int argc, char* argv []) {
  Usage(argc, argv);
  std::ifstream fichero_ram;
  std::ifstream fichero_entrada;
  std::ofstream fichero_salida;  
  std::string nombre_ram{argv[1]}, nombre_entrada{argv[2]}, nombre_salida{argv[3]};
  int modo_debug{std::stoi(argv[4])};
  
  Ram maquina_ram(nombre_ram);
  if (modo_debug == 2) {
    maquina_ram.runDebug(nombre_entrada, nombre_salida);
    std::cout << "Numero de Instrucciones: " << maquina_ram.getInstrucciones() << std::endl;
  } else {
    maquina_ram.run(nombre_entrada, nombre_salida);
    if (modo_debug == 1) {
      std::cout << "Numero de Instrucciones: " << maquina_ram.getInstrucciones() << std::endl;
    }
  }

  return 0;
}