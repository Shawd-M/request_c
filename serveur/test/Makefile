CC=gcc
CFLAGS=-I/usr/local/include
LDFLAGS=-L/usr/local/lib -lcriterion
HEAD_TARGET=test_my_head
DELETE_TARGET=test_my_delete
SOCKET_TARGET=test_my_socket
POST_TARGET=test_my_post
PUT_TARGET=test_my_put

all: $(HEAD_TARGET) $(DELETE_TARGET) $(SOCKET_TARGET) $(POST_TARGET) $(PUT_TARGET)

$(SOCKET_TARGET): test_my_socket.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(SOCKET_TARGET) test_my_socket.c

$(HEAD_TARGET): test_my_head.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(HEAD_TARGET) test_my_head.c

$(DELETE_TARGET): test_my_delete.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(DELETE_TARGET) test_my_delete.c

$(POST_TARGET): test_my_post.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(POST_TARGET) test_my_post.c

$(PUT_TARGET): test_my_put.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PUT_TARGET) test_my_put.c

run: $(HEAD_TARGET) $(DELETE_TARGET)
	./$(SOCKET_TARGET)
	./$(DELETE_TARGET)
	./$(POST_TARGET)
	./$(PUT_TARGET)
	./$(HEAD_TARGET)

clean:
	rm 	$(SOCKET_TARGET) $(DELETE_TARGET) $(POST_TARGET) $(PUT_TARGET) $(HEAD_TARGET)
