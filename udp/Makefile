
.PHONY:all
all:cli svr

cli:client.c
	gcc -o $@ $^ 

svr:server.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -rf svr cli

