CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g

TARGET := AirWatcher

# Pour AirWatcher : tous les .cpp sauf test.cpp
SRCS := $(filter-out test.cpp, $(wildcard *.cpp))
OBJS := $(SRCS:.cpp=.o)

# Pour test : tous les .cpp sauf main.cpp, mais avec test.cpp inclus
TEST_SRCS := $(filter-out main.cpp, $(wildcard *.cpp))
TEST_OBJS := $(TEST_SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -DTEST -I . $^ -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) test

.PHONY: all clean test
