CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g 
GTEST_LIBS = -lgtest -lgtest_main -lpthread
INCLUDES = -I./src -I.

TARGET = list_tests
TESTS = ./tests/list_tests.cc

all: $(TARGET)

$(TARGET): $(TESTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TESTS) -o $(TARGET) $(GTEST_LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)