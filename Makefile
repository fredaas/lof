CC=gcc
CFLAGS=-std=c99 -Wall -O2 -Wno-switch

all : clean generate

generate : generate.c
	$(CC) -o $@ $^ $(CFLAGS)

run :
	./generate < film-list.txt

clean :
	rm -f generate

server :
	php -S localhost:8080

