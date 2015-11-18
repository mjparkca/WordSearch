all:
	gcc `pkg-config --cflags gtk+-3.0` -g -o viewer main.c \
		`pkg-config --libs gtk+-3.0`
clean:
	rm -f viewer
new:
	make clean
	make
