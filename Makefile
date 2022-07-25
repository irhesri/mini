all:
	gcc *.c
san:
	gcc *.c -fsanitize=address