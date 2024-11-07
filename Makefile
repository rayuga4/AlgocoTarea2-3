CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lpthread

bruteForce: bruteForce.o
	$(CC) $(CFLAGS) -o bruteForce bruteForce.o $(LDFLAGS)

bruteForce.o: bruteForce.cpp
	$(CC) $(CFLAGS) -c -o bruteForce.o bruteForce.cpp 

dp: dp.o
	$(CC) $(CFLAGS) -o dp dp.o $(LDFLAGS)

dp.o: dp.cpp
	$(CC) $(CFLAGS) -c -o dp.o dp.cpp

clean:
	rm -f bruteForce bruteForce.o dp dp.o

runBF: bruteForce
	./bruteForce

runDP: dp
	./dp