CC = g++
CFLAGS = -Wall -O2 -Iinclude
OBJS = build/AES.o build/Base64.o

ccrypt: $(OBJS)
	g++ -o ccrypt $(OBJS)

test: $(OBJS) build/main.o
	g++ -o main build/main.o $(OBJS)

build/main.o: src/main.c
	$(CC) -c $(CFLAGS) src/main.c -o build/main.o

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf build/*.o build/ccrypt
