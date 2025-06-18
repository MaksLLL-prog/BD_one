CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17 -O3 -march=native

LDFLAGS = -lm

TARGET = polynomial_roots

SRC = polynomial_roots.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

debug: $(SRC)
	$(CXX) $(CXXFLAGS) -g -o $(TARGET)_debug $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(TARGET)_debug

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run debug