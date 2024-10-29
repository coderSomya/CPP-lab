# Variables
CXX = g++
CXXFLAGS = -std=c++17
TARGET = output
SRC = custom_serializer.cpp

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean target
clean:
	rm -f $(TARGET)

# Run the project
run: all
	./$(TARGET)
