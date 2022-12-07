IDIR =./include
CC=cc
CFLAGS=-I$(IDIR)

ODIR=./out
LDIR =./lib
SDIR=./source
TDIR=./testSourceFile

# LIBS=-lm # Można dodać dla math.c

LIBS=-ggdb

_DEPS = alex.h fun_stack.h parser.h printAlex.h storage.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o alex.o fun_stack.o parser.o printAlex.o storage.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = test.o alex.o fun_stack.o parser.o printAlex.o storage.o
TEST = $(patsubst %,$(ODIR)/%,$(_TEST))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


# $(LDIR)/test.out: $(TEST)
# 	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(LDIR)/a.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: init clean test

init:
	mkdir -p lib out

clean:
	rm -f $(ODIR)/*.o
	rm -f $(LDIR)/*.out 

test: 
	./$(TDIR)/tests.sh $(TDIR)

test-repair:
	sed -i -e 's/\r$$//' $(TDIR)/tests.sh
	

