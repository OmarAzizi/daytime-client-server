CC = gcc

client:
	$(CC) client.c -o daytime_client

server: common.o server.o
	$(CC) common.o server.o -o daytime_server

server.o:
	$(CC) -c server.c -o server.o

common.o:
	$(CC) -c common.c -o common.o

clean:
	rm *.o
