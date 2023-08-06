PROJECT=c-urlencode
VERSION=1.0.0
all:
install:

## Configuration
DESTDIR =
PREFIX  =/usr/local
CC      =cc
CFLAGS  =-Wall -g
HEADERS =urlencode.h

##
all: tools/urlencode$(EXE)
install: tools/urlencode$(EXE)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp tools/urlencode$(EXE) $(DESTDIR)$(PREFIX)/bin
	mkdir -p $(DESTDIR)$(PREFIX)/include/str
	cp $(HEADERS) $(DESTDIR)$(PREFIX)/include/str
tools/urlencode$(EXE): tools/urlencode.c $(HEADERS)
	$(CC) -o $@ tools/urlencode.c $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LIBS)
clean:
	rm -f tools/urlencode$(EXE)
## -- BLOCK:license --
install: install-license
install-license: 
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
	cp LICENSE README.md $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
update: update-license
update-license:
	ssnip README.md
## -- BLOCK:license --
## -- BLOCK:man --
update: update-man
update-man:
	make-h-man update
install: install-man
install-man:
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./urlencode.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- BLOCK:man --
