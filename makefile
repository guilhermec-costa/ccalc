CC = gcc
BINARY = bin/calc 
CFLAGS = -Iinclude -Wall -Wextra -std=c99 -g

SRCS = main.c ops.c
OBJS = $(SRCS:.c=.o)

all: $(BINARY) 

$(BINARY): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^


# wildcard
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJS)
