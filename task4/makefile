CXX := g++
CXXFLAGS := -std=c++11
SANITIZE_FLAGS := -fsanitize=address -fsanitize=undefined

SRCS := $(wildcard *.cpp)

OBJS := $(patsubst %.cpp,%.o,$(SRCS))

TARGET := exec

all: $(TARGET)

$(TARGET): $(OBJS)
        $(CXX) $(CXXFLAGS) $(SANITIZE_FLAGS) $^ -o $@

%.o: %.cpp
        $(CXX) $(CXXFLAGS) $(SANITIZE_FLAGS) -c $< -o $@

clean:
        rm -f $(OBJS) $(TARGET)

.PHONY: all clean
