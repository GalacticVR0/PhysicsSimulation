TARGET := main.exe
CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra
LDLIBS ?= -lSDL3

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Pattern rule to compile each .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	$(RM) $(OBJS) $(TARGET)