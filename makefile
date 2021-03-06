G=g++ -w -lpthread
socklib=socklib.h socklib.cpp config.h 
strplay=strplay.h strplay.cpp config.h
osock=socklib.o 
ostr=strplay.o
all: $(socklib) serve.cpp client.cpp
	$(G) -c $(socklib)
	$(G) -c $(strplay)

	$(G) $(osock) $(ostr) serve.cpp -o serve
	$(G) $(osock) $(ostr) client.cpp -o client

serve:$(socklib) $(strplay) serve.cpp
	$(G) -c $(socklib)
	$(G) -c $(strplay)

	$(G) $(osock) $(ostr) serve.cpp -o serve

client:$(socklib) client.cpp
	$(G) -c $(socklib)
	$(G) -c $(strplay)
	
	$(G) $(osock) $(ostr)  client.cpp -o client

middle:$(socklib)
	$(G) -c $(socklib)
	$(G) -c $(strplay)

header:$(socklib.h)
	$(G) socklib.h socklib.cpp
	$(G) strplay.h strplay.cpp

clean:
	rm -rf *.o *.gch serve client 
