all:

sfml-test: test.o
	g++ test.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

test: test.cpp
	g++ -c test.cpp

demo: demo-o
	g++ demoServer.o -o demoServer -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

demo-o: demoServer.cpp
	g++ demoServer.cpp -I ../include/rapidjson/ -c

demoC: demoC-o
	g++ demoClient.o -o demoClient -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

demoC-o: demoClient.cpp
	g++ -c demoClient.cpp

chat: chat.o
	g++ chat.o -o chat -lsfml-network

chat-o: chat.cpp
	g++ -c chat.cpp

clean: