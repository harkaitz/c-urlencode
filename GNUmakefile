PROJECT =c-urlencode
VERSION =1.0.0
DESTDIR =
PREFIX  =/usr/local
CC      =gcc -pedantic-errors -std=c99 -Wall
HEADERS =urlencode.h
PROGRAMS=urlencode$(EXE)
##
all: $(PROGRAMS)
install: $(PROGRAMS)
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(PREFIX)/include/str
	cp urlencode$(EXE) $(DESTDIR)$(PREFIX)/bin
	cp $(HEADERS) $(DESTDIR)$(PREFIX)/include/str
urlencode$(EXE): tools/urlencode.c $(HEADERS)
	$(CC) -o $@ tools/urlencode.c $(CFLAGS)
clean:
	rm -f tools/urlencode$(EXE)
## -- BLOCK:license --
install: install-license
install-license: 
	@mkdir -p $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
	cp LICENSE  $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
## -- BLOCK:license --
## -- BLOCK:man --
install: install-man
install-man:
	@mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./urlencode.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- BLOCK:man --
