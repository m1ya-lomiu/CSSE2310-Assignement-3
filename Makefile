CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
DEBUG = -g
TARGETS = hub player

.DEFAULT: all
.PHONY: all debug clean

all: $(TARGETS)

debug: CFLAGS += $(DEBUG)
debug: clean $(TARGETS)

hub: hub.c
	$(CC) $(CFLAGS) hub.c -o hub

player: player.c
	$(CC) $(CFLAGS) player.c -o player

clean:
	rm -f $(TARGETS) *.o