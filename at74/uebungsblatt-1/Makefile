all: compile checkstyle test

compile:
	g++ -o PrimMain PrimMain.cpp

checkstyle:
	python ../cpplint.py *.cpp

test:
	g++ -o PrimTest PrimTest.cpp -lgtest -lpthread
	./PrimTest

clean:
	rm -f PrimMain
	rm -f PrimTest
