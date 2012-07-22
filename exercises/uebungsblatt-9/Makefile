CXX = g++ -Wall -g
OBJECTS = AnagramFinder.o
PROG = AnagramFinder
HEADERS = $(wildcard *.h)

all: compile checkstyle test

compile: $(PROG)Main $(PROG)Test

%.o: %.cpp $(HEADERS)
	$(CXX) -c $<

%Main: $(PROG)Main.o $(OBJECTS)
	$(CXX) -o $@ $^

%Test: %Test.o $(OBJECTS)
	$(CXX) -o $@ $^ -lgtest -lgtest_main -lpthread

checkstyle:
	python ../cpplint.py *.h *.cpp

test: $(PROG)Test
	./$(PROG)Test

 clean:
	rm -f $(PROG)Main
	rm -f $(PROG)Test
	rm -f *.o
