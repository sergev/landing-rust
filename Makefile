CXX             = c++ -std=c++11 -g
CXXFLAGS        = -O -Wall -Werror
LDFLAGS         =
LIBS            = -lpthread

OBJ             = main.o landing.o
TEST_OBJ        = test.o landing.o interact.o catch/catch.o
OPT_OBJ         = optimize.o landing.o interact.o catch/catch.o

all:            landing tests optimize

landing:        $(OBJ)
		$(CXX) $(LDFLAGS) $(OBJ) $(LIBS) -o $@

tests:          $(TEST_OBJ)
		$(CXX) $(LDFLAGS) $(TEST_OBJ) $(LIBS) -o $@

optimize:       $(OPT_OBJ)
		$(CXX) $(LDFLAGS) $(OPT_OBJ) $(LIBS) -o $@

lunar:          lunar.c
		$(CC) $(LDFLAGS) $(CXXFLAGS) $< -o $@

clean:
		rm -f *.o landing tests optimize lunar

test:           tests
		./tests -s -r compact

opt:           optimize
		./optimize -s -r compact
###
