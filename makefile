INCLUDE =-I./include 
LIB=-L./lib -luv -lrt

all:
	g++ -lpthread -o hello hello.cpp $(INCLUDE) $(LIB)

clean:
	rm -rf hello