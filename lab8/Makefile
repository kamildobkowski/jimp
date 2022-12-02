IDIR =./include
CC=cc
CFLAGS=-I$(IDIR)

ODIR=./out
LDIR =./lib
SDIR=./source

LIBS=-lm

_DEPS = alex.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o alex.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = test.o alex.o
TEST = $(patsubst %,$(ODIR)/%,$(_TEST))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(LDIR)/test.out: $(TEST)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# $(LDIR)/a.out: $(OBJ)
#  	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: easy-init clean test-easy

easy-init:
	mkdir -p lib out

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

test-easy:
	lib/test.out main.c

