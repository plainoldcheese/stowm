PREFIX?=/usr/X11R6
CFLAGS?=-Os -pedantic -Wall

all:
		$(CC) $(CFLAGS) -I$(PREFIX)/include stowm.c -L$(PREFIX)/lib -lX11 -o stowm

clean:
		rm -f stowm

install:
		rm ~/Scripts/stowm
		cp stowm ~/Scripts/stowm
