CXX := g++
CXXFLAGS := -Wall -std=c++17 -g

TARGET := AirWatcher

SRC_DIR := src
BUILD_DIR := build

# Fichiers sources
SRCS := $(filter-out $(SRC_DIR)/test.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Fichiers pour test
TEST_SRCS := $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

all: $(TARGET)

# Création du dossier build si nécessaire
$(BUILD_DIR):
	mkdir -p $@

# Cible principale (sans linker le dossier build)
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation des .o dans build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation de l'exécutable de test
test: $(TEST_OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -DTEST -I $(SRC_DIR) $^ -o $@

# Nettoyage
clean:
	rm -rf $(BUILD_DIR)/* $(TARGET) test

.PHONY: all clean test
