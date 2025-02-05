CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2 # -g -DDEBUG
INCLUDES = -lm -lgmp -Isrc

all: x25519

x25519: src/io.c src/montgomery.c src/x25519.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

test-montgomery: src/montgomery.c tests/montgomery.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

test-io: src/io.c tests/io.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

tests: x25519 test-montgomery test-io
	./test-montgomery
	./test-io
	./tests/x25519.sh

clean:
	rm -f TODO
