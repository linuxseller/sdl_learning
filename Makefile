CFLAGS=-Wall -Wextra -Werror -pedantic
CLIBS=-L. -I. `sdl2-config --cflags --libs` `pkg-config --libs SDL2_image`
OUTFILE=sdl
CC=cc
all: compile
compile: 
	mkdir -p build
	$(CC) $(CFLAGS) src/main.c -o build/$(OUTFILE) $(CLIBS)
run: compile
	./build/$(OUTFILE)
clean:
	rm -v build/*
