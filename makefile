CC=g++
CFLAGS= -std=c++11 -w
objects = libevent_server.o main.o worker_thread.o
all:$(objects)
	g++   -o libevent_server $(objects)  -std=c++11 -levent -pthread
$(objects): %.o: %.cpp 
	$(CC) -c -g $(CFLAGS) $< -o $@
clean:
	rm -f *.o libevent_server
