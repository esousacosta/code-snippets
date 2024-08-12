CFLAGS: -Wall -Werror -Wextra -pedantic -std=c++20

all: final

# The final executable depends on both main.o and greetings.o
# to be linked together
final: main.o greetings.o
	g++ $(CLFAGS) main.o greetings.o -o final

# greetings.o depends on greetings.cpp
greetings: greetings.cpp
	g++ $(CFLAGS) -c greetings.cpp

# main.o depends on main.cpp
main: main.cpp
	g++ $(CFLAGS) -c main.cpp

clean: 
	rm -f *.o final