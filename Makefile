CC = g++
CCFLAGS = -O3 -Wall -Wextra -pedantic -std=c++17 -I DNest4/code
INCLUDE = -I include/ -I DNest4/code
LINK = -L DNest4/code

default:
	make noexamples -C DNest4/code
	$(CC) $(CCFLAGS) $(INCLUDE) -c src/MyModel.cpp
	$(CC) $(CCFLAGS) $(INCLUDE) -c src/main.cpp
	$(CC) $(LINK) -o main *.o -ldnest4 -lpthread
	rm -f *.o

