all: compile checkstyle test

compile: PrimMain PrimTest

Prim.o: Prim.cpp
	g++ -Wall -c Prim.cpp

PrimMain.o: PrimMain.cpp Prim.h
	g++ -Wall -c PrimMain.cpp

PrimTest.o: PrimTest.cpp Prim.h
	g++ -Wall -c PrimTest.cpp

PrimMain: PrimMain.o Prim.o
	g++ -Wall -o PrimMain PrimMain.o Prim.o

PrimTest: PrimTest.o Prim.o
	g++ -Wall -o PrimTest PrimTest.o Prim.o -lgtest -lpthread

checkstyle:
	python ../cpplint.py *.h *.cpp

test: PrimTest
	./PrimTest

clean:
	rm -f PrimMain
	rm -f PrimTest
	rm -f *.o
