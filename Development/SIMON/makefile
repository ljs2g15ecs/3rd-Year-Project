CC = gcc
PROG = SIMON_host
src = $(wildcard *.c)
obj = $(src:.c=.o)
CFLAGS = -D $(S)
LFLAGS = 

S = 

build: $(obj)
	$(CC) $^ -o $@

$(PROG).o : $(PROG).c FORCE
	$(CC) $(CFLAGS) -c $<
FORCE:;

%.o : %.c
	$(CC) $(CFLAGS) -c $<