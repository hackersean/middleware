socklib=socklib.h socklib.cpp 
all: $(socklib) serve.cpp client.cpp
	g++ $(socklib)  serve.cpp -o serve
	g++ $(socklib)  client.cpp -o client

serve:$(socklib) serve.cpp
	g++ $(socklib)  serve.cpp -o serve

client:$(socklib) client.cpp
	g++ $(socklib)  client.cpp -o client
