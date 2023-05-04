# File:   Makefile
# Author: James Claridge, Vedang Gaikwad
# Date:   20 Oct 2021
# Descr:  Makefile for game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.

game.o: game.c ../../drivers/avr/system.h ../../utils/pacer.h ../../drivers/avr/pio.h ../../drivers/avr/timer.h game_display.h game_mechanics.h block.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../utils/pacer.h ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/timer.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o : ../../drivers/ledmat.c ../../drivers/ledmat.h ../../drivers/avr/system.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

block.o: block.c block.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o : ../../drivers/navswitch.c ../../drivers/navswitch.h ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/avr/delay.h
	$(CC) -c $(CFLAGS) $< -o $@

game_display.o : game_display.c game_display.h ../../drivers/avr/system.h ../../utils/pacer.h ../../utils/tinygl.h ../../fonts/font5x7_1.h ../../utils/font.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

game_mechanics.o : game_mechanics.c game_mechanics.h ../../drivers/avr/system.h block.h
	$(CC) -c $(CFLAGS) $< -o $@





# Link: create ELF output file from object files.

game.out: game.o system.o pio.o pacer.o timer.o ledmat.o navswitch.o game_display.o tinygl.o display.o font.o block.o game_mechanics.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start
