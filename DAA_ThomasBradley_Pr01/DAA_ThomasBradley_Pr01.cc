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
// ./strategy 6

#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <time.h>
#include <vector>

class Strategy {
  public: 
	  virtual void printProduct(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2) = 0;
};

class ReadRow : public Strategy  {
  void printProduct(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2) {
    std::vector<std::vector<int>> result(int(matrix1.size()));
    for (int i{0}; i < int(matrix1.size()); i++) {
      for (int j{0}; j < int(matrix1.size()); j++) {
        int tempNum = 0;
        for (int z{0}; z < int(matrix1.size()); z++) {
          tempNum = tempNum + (matrix1[i][z] * matrix2[z][j]);
        }
        result[i].push_back(tempNum);
      }
    }

    std::cout << "Row Multiplication:" << std::endl;
    for (int i{0}; i < int(result.size()); i++) {
      for (int j{0}; j < int(result[0].size()); j++) {
        std::cout << result[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
};

class ReadColumn : public Strategy  {
  void printProduct(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2) {
    std::vector<std::vector<int>> result(int(matrix1.size()));
    for (int i{0}; i < int(matrix1.size()); i++) {
      for (int j{0}; j < int(matrix1.size()); j++) {
        int tempNum = 0;
        for (int z{0}; z < int(matrix1.size()); z++) {
          tempNum = tempNum + (matrix1[z][j] * matrix2[i][z]);
        }
        result[j].push_back(tempNum);
      }
    }

    std::cout << "Column Multiplication:" << std::endl;
    for (int i{0}; i < int(result.size()); i++) {
      for (int j{0}; j < int(result[0].size()); j++) {
        std::cout << result[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
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

    void multiply(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2) {
      _strategy -> printProduct(matrix1, matrix2);
    }

};

std::vector<std::vector<int>> randomMatrix(int size) {
  std::vector<std::vector<int>> result(size);
  for (int i{0}; i < size; i++) {
    for (int j{0}; j < size; j++) {
	    int random = 1 + (rand() % 9);
      result[i].push_back(random);
    }
  }
  return result;
}

void printMatrix(std::vector<std::vector<int>> matrix, std::string name) {
  std::cout << name << std::endl;
  for (int i{0}; i < int(matrix.size()); i++) {
    for (int j{0}; j < int(matrix[0].size()); j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

/**
 * @desc Texto de ayuda para el correcto funcionamiento del código
*/
const void kHelpText() {
  std::cout << "strategy [1] " << std::endl << std::endl;
  std::cout << "[1] = valor N para determinar tamaño NxN de matrices" << std::endl;
  std::cout << "Se empezara creando dos matrices aleatorias del tamaño elegido," << std::endl;
  std::cout << "a continuación se mostrara su podructo primero leyendo filas y" << std::endl; 
  std::cout << "luego leyendo columnas" << std::endl;
}

/**
 * @desc Texto de como usar el programa y como encontrar más información sobre ella
*/
const void kFuncText() {
  std::cout << "Modo de empleo: strategy [TAMAÑO DE MATRICES]" << std::endl;
  std::cout << "Pruebe 'strategy --help' para más información" << std::endl;
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
  } else {
    kFuncText();
    exit(1);
  } 
}

int main(int argc, char* argv []) {
  srand(time(0));
  time_t start, end; 
  Usage(argc, argv);
  int size{std::stoi(argv[1])};

  std::vector<std::vector<int>> matrix1 = randomMatrix(size);
  printMatrix(matrix1, "Matrix 1:");
  std::vector<std::vector<int>> matrix2 = randomMatrix(size);
  printMatrix(matrix2, "Matrix 2:");

  Context *context;
  start = clock();
  context = new Context(new ReadRow());
  context->multiply(matrix1, matrix2);
  end = clock();
  std::cout << "Time taken for row product: " << std::fixed << double(end - start) / double(CLOCKS_PER_SEC);
  std::cout << std::endl << std::endl;

  start = clock();
  context->setContext(new ReadColumn());
  context->multiply(matrix1, matrix2);
  end = clock();
  std::cout << "Time taken for column product: " << std::fixed << double(end - start) / double(CLOCKS_PER_SEC);
  std::cout << std::endl;

  delete context;
  return 0;
}