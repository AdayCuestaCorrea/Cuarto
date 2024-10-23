# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Diseño y Análisis de Algoritmos
#
# @author Aday Cuesta Correa alu0101483887@ull.edu.es
# @date 16 October 2024
# 

CXX = g++	  # The C++ compiler command
CXXFLAGS = -std=c++20 -g	 # The C++ compiler options (C++20, preserve debug symbols)
LDFLAGS =						             # The linker options (if any)

# Automatically find all .cc files in current directory and subdirectories
SRCS = $(shell find . -name "*.cc")
# Generate corresponding .o object file names
OBJS = $(SRCS:.cc=.o)

# The all target builds all of the programs handled by the makefile. 
all: PushDownAutomata

PushDownAutomata: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Pattern rule for building .o from .cc
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Indicate that the all and clean targets do not
# correspond to actual files.
.PHONY: all clean debug

# The clean target removes all of the executable files
# and object files produced by the build process
# We can use it for additional housekeeping purposes
clean :
	find . -name '*.o' -delete
	rm -f PushDownAutomata doc
	rm -rf *~ basura b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;

# The debug target adds the -DTRAZA flag for debugging information
traza: CXXFLAGS += -DTRAZA
traza: clean all