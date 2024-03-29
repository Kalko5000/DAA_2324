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

#include "./context.cc"

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
  srand(time(0)); // Random Seed, to generate random numbers later
  time_t start, end; // To calculate how much time we take for each multiplication call
  Usage(argc, argv); // Check we have the right parameters
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