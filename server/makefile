all:

test: test.cpp
	g++ -c test.cpp

server: server-o
	g++ server.o -o server -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lmysqlcppconn -std=c++11

server-o: server.cpp
	g++ server.cpp -I ../include/rapidjson/ -c -std=c++11

client: client-o
	g++ demoClient.o -o client -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

client-o: demoClient.cpp
	g++ -c demoClient.cpp

clean:
	rm *.o client server