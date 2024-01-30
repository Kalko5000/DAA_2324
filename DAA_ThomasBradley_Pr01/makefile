# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Diseño y Análisis de Algoritmos
#
# PRACTICA 01: Análisis de complejidad
# Author:      Thomas Edward Bradley
# Email:       alu0101408248@ull.edu.es
# Date:        30.jan.2024
# Brief:       A makefile used to compile the files in "DAA_ThomasBradley_Pr01"

CXX = g++
CXXFLAGS = -std=c++14 -Wall
LDFLAGS =

all: strategy

strategy: strategy.cc context.cc main.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

clean :
	rm -rf *.o strategy ../doc
	rm -rf *~ basura b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;