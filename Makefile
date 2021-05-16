CC=g++
CFLAGS=-c -Wall
EXECUTABLE=bin/simple_computer
SOURSES=src/main.cpp src/mySimpleComputer.cpp src/myBigChars.cpp src/myTerm.cpp src/printConsole.cpp src/myReadkey.cpp src/timer.cpp
OBJECTS=build/main.out build/mySimpleComputer.out build/myBigChars.out build/myTerm.out build/printConsole.out build/myReadkey.out build/timer.out
all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
build/%.out: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf build/*.out
	rm -rf bin/*
start:
	./bin/simple_computer
