CFLAGS: -Wall -Werror -Wextra -pedantic -std=c++20

all: final

final: main.o greetings.o
	g++ $(CLFAGS) main.o greetings.o -o final

greetings: greetings.cpp
	g++ $(CFLAGS) -c greetings.cpp

main: main.cpp
	g++ $(CFLAGS) -c main.cpp

clean: 
	rm -f *.o final