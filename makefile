G=g++ -W
socklib=socklib.h socklib.cpp 
strplay=strplay.h strplay.cpp
osock=socklib.o 
ostr=strplay.o
all: $(socklib) serve.cpp client.cpp
	$(G) -c $(socklib)
	$(G) -c $(strplay)

	$(G) $(osock) $(ostr) serve.cpp -o serve
	$(G) $(osock) $(ostr) client.cpp -o client

serve:$(socklib) $(strplay) serve.cpp
	$(G) $(socklib) -c $(osock)
	$(G) $(strplay) -c $(ostr)

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
