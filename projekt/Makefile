CXX = g++ -g -Wall
MAIN_BINARIES = $(basename $(wildcard *Main.cpp))
TEST_BINARIES = $(basename $(wildcard *Test.cpp))
HEADERS = $(wildcard *.h)
OBJECTS = $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp,$(wildcard *.cpp))))

.PRECIOUS: %.o

all: compile checkstyle test

compile: $(MAIN_BINARIES) $(TEST_BINARIES)

checkstyle:
	python ../cpplint.py *.h *.cpp

test: $(TEST_BINARIES)
	for T in $(TEST_BINARIES); do ./$$T; done

clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o

%Main: %Main.o $(OBJECTS)
	$(CXX) -o $@ $^

%Test: %Test.o $(OBJECTS)
	$(CXX) -o $@ $^ -lgtest -lgtest_main -lpthread

%.o: %.cpp $(HEADERS)
	$(CXX) -c $<
