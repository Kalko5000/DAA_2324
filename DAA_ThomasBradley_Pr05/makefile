
# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Diseño y Análisis de Algoritmos
#
# PRACTICA 05: Algoritmos de Divide y Vencerás
# Author:      Thomas Edward Bradley
# Email:       alu0101408248@ull.edu.es
# Date:        12.mar.2024
# Brief:       A makefile used to compile the files in "DAA_ThomasEdwardBradley_p05"

CXX = g++
CXXFLAGS = -std=c++14 -Wall
LDFLAGS =

all: dyv

dyv: solution.cc hanoisolver.cc binary.cc quick.cc merge.cc main.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

clean :
	rm -rf *.o dyv ../doc
	rm -rf *~ basura b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;