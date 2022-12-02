IDIR =./include
CC=cc
CFLAGS=-I$(IDIR)

ODIR=./out
LDIR =./lib

LIBS=-lm

_DEPS = alex.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o alex.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = test.o alex.o
TEST = $(patsubst %,$(ODIR)/%,$(_TEST))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


lib/test.out: $(TEST)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# lib/a.out: $(OBJ)
# 	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean test-easy

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

test-easy:
	lib/test.out main.c
