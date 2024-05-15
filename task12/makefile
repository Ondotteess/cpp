CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++11
SANITIZE_FLAGS := -fsanitize=address -fsanitize=undefined

SRCS := $(wildcard *.cpp)
BINS := $(patsubst %.cpp,%,$(SRCS))

.PHONY: all clean

all: $(BINS)

%: %.cpp
        $(CXX) $(CXXFLAGS) $(SANITIZE_FLAGS) $< -o $@

clean:
    	rm -f $(BINS)