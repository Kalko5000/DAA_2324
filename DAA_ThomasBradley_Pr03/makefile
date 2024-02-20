
# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Diseño y Análisis de Algoritmos
#
# PRACTICA 02: Simulador de la máquina RAM
# Author:      Thomas Edward Bradley
# Email:       alu0101408248@ull.edu.es
# Date:        20.feb.2024
# Brief:       A makefile used to compile the files in "DAA_ThomasEdwardBradley_p02"

CXX = g++
CXXFLAGS = -std=c++14 -Wall
LDFLAGS =

all: simulador

simulador: instruction.cc context.cc ram.cc main.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

clean :
	rm -rf *.o simulador ../doc
	rm -rf *~ basura b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;