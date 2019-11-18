all:
	gcc sok.c -o sok `pkg-config --cflags --libs gtk+-3.0`
