CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror
CFLAGS += -I../include
LDFLAGS = 

all:
	rm -rf test
	gcc $(CFLAGS) $(LDFLAGS) src/*.c -o test
	./test
