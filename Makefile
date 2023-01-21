## Configuration
DESTDIR     =
PREFIX      =/usr/local
CC          =cc
CFLAGS      =-Wall -g
HEADERS     =urlencode.h urlencode-share.h
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
## -- manpages --
install: install-man3
install-man3:
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./urlencode.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- manpages --
## -- license --
install: install-license
install-license: LICENSE
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-urlencode
	cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-urlencode
## -- license --
