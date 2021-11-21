CC=gcc
JSON_C_DIR=/usr/local
LDFLAGS += -L$(JSON_C_DIR)/lib -ljson-c -lzmq
CFLAGS += -I$(JSON_C_DIR)/include/json-c 

client: client.c
	${CC} -o client client.c ${LDFLAGS} ${CFLAGS}

server: server.c
	${CC} -o server server.c ${LDFLAGS} ${CFLAGS}

clean:
	rm *.o
