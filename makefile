G=g++ -W
socklib=socklib.h socklib.cpp 
all: $(socklib) serve.cpp client.cpp
	$(G) $(socklib)  serve.cpp -o serve
	$(G) $(socklib)  client.cpp -o client

serve:$(socklib) serve.cpp
	$(G) $(socklib)  serve.cpp -o serve

client:$(socklib) client.cpp
	$(G) $(socklib)  client.cpp -o client
