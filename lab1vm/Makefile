CC=gcc
CFLAGS=-I../common/include -I./include
DEPS =
ODIR = .objs

_OBJ = inspect.o args.o main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJ))

lab1vm: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)


$(ODIR)/%.o: src/%.c $(DEPS)
	if test ! -d $(ODIR); \
	then mkdir $(ODIR); \
	fi
	$(CC) -c -o $@ $< $(CFLAGS) -DNO_ARGPHEADER


_TOBJ = inspect.o args.o
TOBJS = $(patsubst %,$(ODIR)/%,$(_TOBJ))

$(ODIR)/main.o: main.c $(TOBJS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core lab1vm

.PHONY: mrproper

mrproper: clean
	rm -rf $(ODIR)
