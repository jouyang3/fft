CC=clang
CFLAGS=-I. -g -Wall
DEPS=fft.h
OBJ=main.c fft.o

clean:
	rm -f main; rm -f *.o; rm -f *.temp;

%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main:$(OBJ)
	$(CC) $(CFLAGS) -o main $^ -v;

