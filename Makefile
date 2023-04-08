SRC_FILES = $(wildcard src/*.cpp)
OBJ_FILES := $(subst src,build,$(SRC_FILES))
OBJ_FILES := $(subst .cpp,.o,$(OBJ_FILES))

.PHONY: run test clean

build/out: $(OBJ_FILES)
	g++ $^ -o $@ -lSDL2
build/%.o: src/%.cpp
	g++ -c $^ -o $@
run:
	./build/out
clean:
	rm build/*
test:
	echo $(SRC_FILES)
	echo $(OBJ_FILES)