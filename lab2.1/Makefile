CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
TARGET = steam_db
SOURCES = main.cpp game.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = game.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) games_db.bin

run: $(TARGET)
	./$(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

.PHONY: all clean run debug
