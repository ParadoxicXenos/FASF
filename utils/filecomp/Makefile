exec = comp.out
sources = $(wildcard *.c)
objects = $(sources:.c=.o)
flags = -g


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c %.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./comp.out /usr/local/bin/fasf

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o