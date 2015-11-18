all: wordsearch

wordsearch: searchWord.o Board.o CharList.o CharNode.o
	gcc -o wordsearch main.c searchWord.o Board.o CharList.o CharNode.o

searchWord.o:
Board.o:
CharList.o:
CharNode.o:

clean:
	rm -f ../bin/*

new:
	make clean
	make
