CC=gcc
CFLAGS=-I../common/include -I.
DEPS =
ODIR = .objs


$(ODIR)/%.o: %.c $(DEPS)
	if test -d $(ODIR); \
	then rm -rf $(ODIR)/*; \
	else mkdir $(ODIR); \
	fi
	$(CC) -c -o $@ $< $(CFLAGS)

mu0: $(ODIR)/main.o
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core.* mu0

.PHONY: mrproper

mrproper: clean
	rm -rf $(ODIR)
