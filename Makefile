all:
	@gcc -o main *.c
zip: all
	zip poker.zip *.c *.h Makefile
run:
	@./main
