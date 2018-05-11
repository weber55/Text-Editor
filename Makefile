all: p2

p2.o: p2.cpp
	g++ -Wall -std=c++14 -c -lncurses -g -O0 -pedantic-errors p2.cpp

p2: p2.o
	g++ -Wall -lncurses -g -o p2 p2.o

1730ed: 1730ed.o Textfile.o
	g++ -Wall -lncurses -g -o 1730ed 1730ed.o Textfile.o

1730ed.o: 1730ed.cpp Textfile.h
	g++ -Wall -std=c++14 -c -lncurses -g -O0 -pedantic-errors 1730ed.cpp

Textfile.o: Textfile.cpp Textfile.h
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c Textfile.cpp

clean:
	rm -f 1730ed
	rm -f 1730ed.o
	rm -f Textfile.o