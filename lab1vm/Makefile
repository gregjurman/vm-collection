CC=gcc
CFLAGS=-I../common/include -I.
DEPS =
ODIR = .objs


$(ODIR)/%.o: %.c $(DEPS)
	if test ! -d $(ODIR); \
	then mkdir $(ODIR); \
	fi
	$(CC) -c -o $@ $< $(CFLAGS)

_OBJ = inspect.o main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJ))

lab1vm: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core lab1vm

.PHONY: mrproper

mrproper: clean
	rm -rf $(ODIR)
