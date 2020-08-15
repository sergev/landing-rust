CXX             = c++ -std=c++11 -g
CXXFLAGS        = -O -Wall -Werror
LDFLAGS         =
LIBS            = -lpthread

OBJ             = main.o landing.o
TEST_OBJ        = test.o landing.o interact.o catch/catch.o

all:            landing tests

landing:        $(OBJ)
		$(CXX) $(LDFLAGS) $(OBJ) $(LIBS) -o $@

tests:          $(TEST_OBJ)
		$(CXX) $(LDFLAGS) $(TEST_OBJ) $(LIBS) -o $@

clean:
		rm -f *.o landing tests

test:           tests
		./tests -s -r compact
###
