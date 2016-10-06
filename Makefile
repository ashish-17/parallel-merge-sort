CC = gcc
CFLAGS = -O0 -Wall -I.
RM = rm -f

DEPS = utils.h seqMS.h
OBJ = seqMS.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(OBJ) *.0 main
