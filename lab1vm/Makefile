CC=gcc
CFLAGS=-I../common/include -I./include
DEPS =
ODIR = .objs


$(ODIR)/%.o: src/%.c $(DEPS)
	if test ! -d $(ODIR); \
	then mkdir $(ODIR); \
	fi
	$(CC) -c -o $@ $< $(CFLAGS) -DNO_ARGPHEADER

_OBJ = inspect.o args.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/main.o: main.c $(OBJS)
	$(CC) -c -o $@ $< $(CFLAGS)

lab1vm: .objs/main.o $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core lab1vm

.PHONY: mrproper

mrproper: clean
	rm -rf $(ODIR)
