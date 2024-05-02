
src=$(wildcard *.c)
exe=x

all: run

test: $(exe)
	@rm test
	@cp test.txt test
	@./$(exe) test

run: $(exe)
	@./$(exe)

$(exe): $(src)
	@gcc -o $(exe) $(src)

