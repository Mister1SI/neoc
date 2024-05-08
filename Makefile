
SRC=$(wildcard src/*.c)
EXE=x
CFLAGS="-Ih"

all: run

test: $(EXE)
	@rm test
	@cp test.txt test
	@./$(EXE) test

run: $(EXE)
	@./$(EXE)

$(EXE): $(SRC)
	@gcc -o $(EXE) $(SRC)

