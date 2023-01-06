all:
	gcc -Wall --pedantic src/*.c -o bin/a.out -lm

matrix.o: matrix.h


.PHONY: clean run

clean:
	-rm *.o libge.a

run:
	bin/a.out