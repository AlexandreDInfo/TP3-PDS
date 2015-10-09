tail2 : reset
	gcc -Wall -Werror -ansi -pedantic -D_XOPEN_SOURCE=500 -g tail2.c -o tail2
reset:
	rm tail | true
	rm tail2 | true