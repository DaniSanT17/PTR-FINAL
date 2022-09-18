
PRJ=$(shell basename "$(CURDIR)")

sources = $(filter-out $(srcdir)/main.c, $(wildcard $(srcdir)/*.c))
includes= $(wildcard $(incdir)/*.h)
objects = $(patsubst $(srcdir)/%.c, $(objdir)/%.o, $(sources))

srcdir=./src
incdir=./inc
objdir=./obj

CC=gcc
CFLAGS=-Wall  -O3 -I $(incdir) 
LDLIBS=-ggdb -lm -lpthread -lstdc++

all: $(PRJ)

showvars:
	@echo $(PRJ)
	@echo Dirs: $(incdir) $(srcdir) $(objdir) $(libdir)
	@echo Sources:  $(sources)
	@echo Objects:  $(objects)
	@echo Includes: $(includes)
	@echo CC: $(CC)
	@echo LIBS: $(LDLIBS)

$(PRJ): $(srcdir)/main.c $(objects) $(includes)
	$(CC) $(CFLAGS) -o $(PRJ) $(srcdir)/main.c $(includes) $(objects) $(LDLIBS) -lm

$(objdir)/%.o: $(srcdir)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean run

clean:
	@rm -rf $(PRJ) $(objdir)/*.o $(srcdir)/*~

run:
	@./$(PRJ) "$(ARGS)" 
	@./$(PRJ) > dados.txt
