all:httpserver

httpserver:httpserver.c
	gcc httpserver.c -o httpserver