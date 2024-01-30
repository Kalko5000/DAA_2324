/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * PRACTICA 01: Análisis de complejidad
 * @author:  Thomas Edward Bradley
 * @email:   alu0101408248@ull.edu.es
 * @date:    30.jan.2024
 * @brief:   Multiplicación de matrices siguiendo principios SOLID y usando el patrón estrategia
 *           Aqui se tiene la implementación de la clase Context
 */

// g++ --std=c++14 -o strategy DAA_ThomasBradley_Pr01.cc
// ./strategy 6

#include "./strategy.cc"

class Context {
  private:
	  Strategy *_strategy;
  public:
    // Constructor
    Context(Strategy *strategy) {
      _strategy = strategy;
    }
    
    void setContext(Strategy *strategy) {
      _strategy = strategy;
    }

    void multiply(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2) {
      _strategy -> printProduct(matrix1, matrix2);
    }

};