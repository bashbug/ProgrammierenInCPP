CXX = g++ -Wall -g
OBJECTS = TemplatedString.o
PROG = TemplatedString
HEADERS = $(wildcard *.h)

all: compile checkstyle test

compile: $(PROG) $(PROG)Test

%: %.cpp $(HEADERS)
	$(CXX) -c $^

%Test: %Test.o $(OBJECTS)
	$(CXX) -o $@ $^ -lgtest -lgtest_main -lpthread

checkstyle:
	python ../cpplint.py *.h *.cpp

test: $(PROG)Test
	./$(PROG)Test

 clean:
	rm -f $(PROG)
	rm -f $(PROG)Test
	rm -f *.o
