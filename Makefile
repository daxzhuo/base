CC=clang++
CFLAGS=-std=c++11

test: test.cc
	$(CC) $(CFLAGS) test.cc -o $@

.PHONY: clean

clean:
	rm -f test
