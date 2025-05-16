# Compilateur et options
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g

# Nom de l'exécutable
TARGET := mon_programme

# Tous les fichiers .cpp du dossier courant
SRCS := $(wildcard *.cpp)

# Remplacement .cpp -> .o
OBJS := $(SRCS:.cpp=.o)

# Règle principale
all: $(TARGET)

# Générer l'exécutable à partir des .o
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation de chaque .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
