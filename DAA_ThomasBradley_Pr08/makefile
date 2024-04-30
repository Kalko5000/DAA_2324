# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Diseño y Análisis de Algoritmos
#
# PRACTICA 07: Parallel Machine Scheduling Problem with Dependent Setup Times
# Author:      Thomas Edward Bradley
# Email:       alu0101408248@ull.edu.es
# Date:        02.apr.2023
# Brief:       A makefile used to compile the files in "DAA_ThomasEdwardBradley_p07"

CXX = g++
CXXFLAGS = -std=c++14 -Wall
LDFLAGS =

all: diversity

diversity: solution.cc vorazsolution.cc graspsolution.cc main.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

clean :
	rm -rf *.o diversity ../doc
	rm -rf *~ basura b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;