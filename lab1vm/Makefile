CC=gcc
CFLAGS=-I.
DEPS =
ODIR = .objs


$(ODIR)/%.o: %.c $(DEPS)
	mkdir $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

vm-a: $(ODIR)/main.o
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core vm-a

.PHONY: mrproper

mrproper: clean
	rm -rf $(ODIR)
