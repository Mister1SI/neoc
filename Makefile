
src=$(wildcard *.c)
exe=x

all: run

run: $(exe)
	@./$(exe)

$(exe): $(src)
	@gcc -o $(exe) $(src)

