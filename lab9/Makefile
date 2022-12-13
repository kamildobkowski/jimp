all:
	gcc -Wall --pedantic src/*.c -o bin/gauss -lm

test: all
	bin/gauss dane/A dane/b

tests: all
	@echo "\nTest 1:"
	bin/gauss dane/tests/A22 dane/tests/B21_1
	@echo "\nTest 2:"
	bin/gauss dane/tests/A22 dane/tests/B21_2
	@echo "\nTest 3:"
	bin/gauss dane/tests/A44 dane/tests/B41_1
	@echo "\nTest 4:"
	bin/gauss dane/tests/A44 dane/tests/B41_2

.PHONY: test tests