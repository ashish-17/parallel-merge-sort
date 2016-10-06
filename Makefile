CC = gcc
CFLAGS = -O3 -Wall -I. -lpthread
RM = rm -f

DEPS = utils.h seqMS.h parallelMS.h
OBJ = seqMS.o parallelMS.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(OBJ) *.0 main
