CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2 # -g -DDEBUG
INCLUDES = -lm -lgmp -Isrc

all: x25519

x25519: src/montgomery.c src/x25519.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

test-montgomery: src/montgomery.c tests/montgomery.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

tests: test-montgomery
	./test-montgomery

clean:
	rm -f TODO
