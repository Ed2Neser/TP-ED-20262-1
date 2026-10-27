SHELL := cmd.exe

CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -pedantic -O2
CPPFLAGS ?= -Iinclude
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp,obj/%.o,$(SOURCES))
OUTPUT := bin/TP.exe

.PHONY: all run clean

all: $(OUTPUT)

run: all
	$(OUTPUT)

bin obj:
	if not exist $@ mkdir $@

$(OUTPUT): $(OBJECTS) | bin
	$(CXX) $(OBJECTS) -o $(OUTPUT)

obj/%.o: src/%.cpp | obj
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	if exist bin\TP.exe del /Q bin\TP.exe
	if exist obj\*.o del /Q obj\*.o
