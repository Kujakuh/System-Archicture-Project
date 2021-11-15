# Makefile

VPATH := src:inc
CFLAGS += -Iinc -Wall -g

Wifi_collector: main.o wc_base.o dym_struct_arr.o
	gcc -o $@ $^ $(CFLAGS)

files: main.c wc_base.c dym_struct_arr.c
	gcc -c $^

clear:
	rm *.o Wifi_collector
