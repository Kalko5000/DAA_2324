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
 */

// g++ --std=c++14 -o strategy DAA_ThomasBradley_Pr01.cc
// ./strategy 

#include <iostream>

class Strategy {
  public: 
	  virtual void AlgorithmInterface(int v[]) = 0;
};

class ReadRow : public Strategy  {
  void AlgorithmInterface(int array[]) {}
};

class ReadColumn : public Strategy  {
  void AlgorithmInterface(int array[]) {}
};

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

    void ContextInterface(int v[]) {
      _strategy -> AlgorithmInterface(v);
    }

};

int main () {
  std::cout << "Hi!" << std::endl;

  Context *context;
  context = new Context(new ReadRow());
  context->ContextInterface(new int[1, 2]);
  context->setContext(new ReadColumn());
  context->ContextInterface(new int[1, 2]);
}