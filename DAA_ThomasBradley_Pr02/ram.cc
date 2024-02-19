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
 * @brief:   Diseño y funcionamiento de una maquina RAM. Aqui esta la definición de la clase Instruction
 */

#include "ram.h"

/**
 * @constructor
*/
Ram::Ram(std::string nombre_ram) { 
  programa.resize(1);
  registros.resize(10);
  instrucciones = 0;
  for (int i{0}; i < int(registros.size()); i++) {
    registros[i] = 0;
  }

  int tamaño{0};
  std::ifstream fichero_ram;
  fichero_ram.open(nombre_ram);
  if (fichero_ram.is_open()) { 
    while (!fichero_ram.eof()) {
      std::string entrada{""};
      std::string etiqueta{""};
      std::string operando{""};
      fichero_ram >> entrada; 
      if (entrada == "#") { // Es un comentario, ignorar linea
        std::getline(fichero_ram, entrada);
      } else if (entrada[entrada.size() - 1] == ':') { // Es un bloque, que se necesita almacenar en un posicion separada
        programa.resize(tamaño + 2);
        tamaño++;
        std::pair<std::string, int> temp_pair{entrada, tamaño};
        bloques.push_back(temp_pair);
      } else if (entrada == "HALT" || entrada == "halt") { // Halt, to tomar entrada ademas
        addProgram("halt", "");
      } else { 
        if (entrada[0] == 'J' || entrada[0] == 'j') { // Salto, siguiente entrada sera una etiqueta
          fichero_ram >> etiqueta;
          if (entrada == "JUMP" || entrada == "jump") {
            addProgram("jump", etiqueta);
          } else if (entrada == "JZERO" || entrada == "jzero") {
            addProgram("jzero", etiqueta);
          } else if (entrada == "JGTZ" || entrada == "jgtz") {
            addProgram("jgtz", etiqueta);
          }
        } else { // Comando con operando 
          fichero_ram >> operando;
          if (entrada == "LOAD" || entrada == "load") {
            addProgram("load", operando);
          } else if (entrada == "STORE" || entrada == "store") {
            addProgram("store", operando);
          } else if (entrada == "ADD" || entrada == "add") {
            addProgram("add", operando);
          } else if (entrada == "SUB" || entrada == "sub") {
            addProgram("sub", operando);
          } else if (entrada == "MULT" || entrada == "mult" || entrada == "MUL" || entrada == "mul") {
            addProgram("mult", operando);
          } else if (entrada == "DIV" || entrada == "div") {
            addProgram("div", operando);
          } else if (entrada == "READ" || entrada == "read") {
            addProgram("read", operando);
          } else if (entrada == "WRITE" || entrada == "write") {
            addProgram("write", operando);
          } 
        } 
      }
    } 
  } else { // Fichero .ram no se pudo abrir
    std::cerr << "Error al abrir fichero .ram" << std::endl;
    exit(1);
  }
}

/**
 * @desc Método que ejecuta el programa previamente cargado en memoria (en el constructor)
 * @param {std::string} nombre_in Nombre del fichero de la cinta de entrada
 * @param {std::string} nombre_out Nombre del fichero de la cinta de salida
*/
void Ram::run(std::string nombre_in, std::string nombre_out) {
  std::ifstream fichero_in;
  std::ofstream fichero_out;
  fichero_in.open(nombre_in);
  fichero_out.open(nombre_out);
  Context *steps;
  steps = new Context(new Registro());

  if (fichero_in.is_open() && fichero_out.is_open()) {
    for(int i{0}; i < int(programa.size()); i++) {
      for(int j{0}; j < int(programa[i].size()); j++) {
        instrucciones++;
        if (programa[i][j].second[0] == '=') { // Averiguar tipo de operando
          steps->setContext(new Constant());
        } else if (programa[i][j].second[0] == '*') {
          steps->setContext(new RegistroContenido());
        } else {
          steps->setContext(new Registro());
        }

        std::string instruction{programa[i][j].first};
        if (instruction == "load") { // Instrucción a realizar con el tipo de operando establecido previamente
          steps->ContextLoad(registros, programa[i][j].second);
        } else if (instruction == "store") {
          steps->ContextStore(registros, programa[i][j].second);
        } else if (instruction == "add") {
          steps->ContextAdd(registros, programa[i][j].second);
        } else if (instruction == "sub") {
          steps->ContextSub(registros, programa[i][j].second);
        } else if (instruction == "mult") {
          steps->ContextMult(registros, programa[i][j].second);
        } else if (instruction == "div") {
          steps->ContextDiv(registros, programa[i][j].second);
        } else if (instruction == "read") {
          steps->ContextRead(registros, fichero_in, programa[i][j].second);
        } else if (instruction == "write") {
          steps->ContextWrite(registros, fichero_out, programa[i][j].second);
        } else if (instruction == "jump") {
          steps->ContextJump(bloques, programa[i][j].second, i);
          break;
        } else if (instruction == "jzero") {
          steps->ContextJzero(bloques, programa[i][j].second, i, registros[0]);
          if (registros[0] == 0) { // CHANGE ME
            break;
          }
        } else if (instruction == "jgtz") {
          steps->ContextJgtz(bloques, programa[i][j].second, i, registros[0]);
          if (registros[0] > 0) { // CHANGE ME
            break;
          }
        } else {
          return;
        }
        // DESCOMENTE LAS SIGUIENTES LINEAS PARA VER LA EJECUCION DE INSTRUCCIONES EN LA TERMINAL
        // std::cout << programa[i][j].first << " " << programa[i][j].second << std::endl;
      }
      // std::cout << "-" << std::endl;
    }
  } else { // Fichero .in o .out no se pudo abrir
    std::cerr << "Error al abrir las cintas" << std::endl;
    exit(1);
  }
  return;
}

/**
 * @desc Método que ejecuta el programa previamente cargado en memoria (en el constructor) mostrando por pantalla su ejecución
 * @param {std::string} nombre_in Nombre del fichero de la cinta de entrada
 * @param {std::string} nombre_out Nombre del fichero de la cinta de salida
*/
void Ram::runDebug(std::string nombre_in, std::string nombre_out) {
  std::ifstream fichero_in;
  std::ofstream fichero_out;
  fichero_in.open(nombre_in);
  fichero_out.open(nombre_out);
  Context *steps;
  int input_pos{0};
  steps = new Context(new Registro());

  if (fichero_in.is_open() && fichero_out.is_open()) {
    for(int i{0}; i < int(programa.size()); i++) {
      for(int j{0}; j < int(programa[i].size()); j++) {
        instrucciones++;
        if (programa[i][j].second[0] == '=') { // Averiguar tipo de operando
          steps->setContext(new Constant());
        } else if (programa[i][j].second[0] == '*') {
          steps->setContext(new RegistroContenido());
        } else {
          steps->setContext(new Registro());
        }

        std::cout << programa[i][j].first << " " << programa[i][j].second << std::endl;

        std::string instruction{programa[i][j].first};
        if (instruction == "load") { // Instrucción a realizar con el tipo de operando establecido previamente
          steps->ContextLoad(registros, programa[i][j].second);
        } else if (instruction == "store") {
          steps->ContextStore(registros, programa[i][j].second);
        } else if (instruction == "add") {
          steps->ContextAdd(registros, programa[i][j].second);
        } else if (instruction == "sub") {
          steps->ContextSub(registros, programa[i][j].second);
        } else if (instruction == "mult") {
          steps->ContextMult(registros, programa[i][j].second);
        } else if (instruction == "div") {
          steps->ContextDiv(registros, programa[i][j].second);
        } else if (instruction == "read") {
          steps->ContextRead(registros, fichero_in, programa[i][j].second);
          input_pos++;
        } else if (instruction == "write") {
          steps->ContextWrite(registros, fichero_out, programa[i][j].second);
        } else if (instruction == "jump") {
          steps->ContextJump(bloques, programa[i][j].second, i);
          printStep(nombre_in, input_pos, fichero_out);
          break;
        } else if (instruction == "jzero") {
          steps->ContextJzero(bloques, programa[i][j].second, i, registros[0]);
          if (registros[0] == 0) { // CHANGE ME
            printStep(nombre_in, input_pos, fichero_out);
            break;
          }
        } else if (instruction == "jgtz") {
          steps->ContextJgtz(bloques, programa[i][j].second, i, registros[0]);
          if (registros[0] > 0) { // CHANGE ME
            printStep(nombre_in, input_pos, fichero_out);
            break;
          }
        } else {
          return;
        }
     
        printStep(nombre_in, input_pos, fichero_out);
      }
    }
  } else { // Fichero .in o .out no se pudo abrir
    std::cerr << "Error al abrir las cintas" << std::endl;
    exit(1);
  }
  return;
}

/**
 * @desc Devuelve el numero de instrucciones ejecutadas
*/
int Ram::getInstrucciones() {
  return instrucciones;
}

/**
 * @desc Imprime el valor de todos los registros de la maquina
*/
void Ram::printRegistros() {
  for (int i{0}; i < int(registros.size()); i++) {
    std::cout << "R" << i << "(" << registros[i] << ") ";
  }
  std::cout << std::endl;
}

/**
 * @desc Imprime los contenidos de un fichero
 * @param {std::string} file_name Nombre del fichero
 * @param {int} pos Posición numerico actual en el que se encuentra el ifstream
*/
void Ram::printFile(std::string file_name, int pos) {
  std::ifstream fichero;
  fichero.open(file_name);
  if (fichero.is_open()) {
    int counter{0};
    while (!fichero.eof()) {
      if (counter == pos) {
        std::cout << ".";
      }
      std::string temp;
      fichero >> temp;
      std::cout << " " << temp;
      counter++;
    }
    std::cout << std::endl;
  } else {
    std::cerr << "Error al abrir las cintas" << std::endl;
    exit(1);
  }
}

void Ram::printStep(std::string nombre_in, int input_pos, std::ofstream& output_file) {
  printRegistros(); // Sentencias que imprimen el estado de la maquina en cada turno
  std::cout << "Fichero Entrada y posición actual:";
  printFile(nombre_in, input_pos);
  std::cout << "Posición actual fichero de salida: " << output_file.tellp() << std::endl;
  std::cout << std::endl;
}

/**
 * @desc Añade una instruccion al vector que contiene el resto del programa
 * @param {std::string} entrada Palabra clave de la instruccion
 * @param {std::string} operando Numero del operando con su tipo por delante
*/
void Ram::addProgram(std::string entrada, std::string operando) {
  std::pair<std::string, std::string> temp{entrada, operando};
  programa[programa.size() - 1].push_back(temp);
}