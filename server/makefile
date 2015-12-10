all:

test: test.cpp
	g++ -c test.cpp

server: server-o
	g++ -std=c++11 server.o -o server -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lmysqlcppconn

server-o: server.cpp
	g++  -std=c++11 server.cpp -I ../include/rapidjson/ -c

client: client-o
	g++ demoClient.o -o client -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

client-o: demoClient.cpp
	g++ -c demoClient.cpp

clean:
	rm *.o client server
