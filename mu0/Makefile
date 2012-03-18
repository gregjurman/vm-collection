CC=gcc
CFLAGS=-I../common/include -I./include
DEPS =
ODIR = .objs

_OBJ = memory.o main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJ))

mu0: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)


$(ODIR)/%.o: %.c $(DEPS)
	if test ! -d $(ODIR); \
	then mkdir $(ODIR); \
	fi
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core.* mu0

.PHONY: mrproper

mrproper: clean
	rm -rf $(ODIR)
