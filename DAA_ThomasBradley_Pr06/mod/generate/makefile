# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Diseño y Análisis de Algoritmos
#
# PRACTICA 06: Problema del Viajante de Comercio (TSP)
# Author:      Thomas Edward Bradley
# Email:       alu0101408248@ull.edu.es
# Date:        21.mar.2023
# Brief:       A makefile used to compile the files in "DAA_ThomasEdwardBradley_p06/generate"

CXX = g++
CXXFLAGS = -std=c++14 -Wall
LDFLAGS =

all: generate

generate: main.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

clean :
	rm -rf *.o generate ../doc
	rm -rf *~ basura b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;