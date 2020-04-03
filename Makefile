PREFIX?=/usr/X11R6
CFLAGS?=-Os -pedantic -Wall
DESTDIR?=/usr

all:
		$(CC) $(CFLAGS) -I$(PREFIX)/include stowm.c -L$(PREFIX)/lib -lX11 -o stowm

clean:
		rm -f stowm

install:
		cp stowm $(DESTDIR)/bin/stowm

uninstall:
		rm $(DESTDIR)/bin/stowm
