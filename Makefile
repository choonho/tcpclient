CC=gcc
CFLAGS=-g

build: tcpclient.o
	$(CC) -o tcpclient tcpclient.o -lpthread $(CFLAGS)

.PHONY: test
test:
	./tcpclient http://localhost/index.html 1000

test:
.PHONY: clean
clean:
	rm -f *.o
