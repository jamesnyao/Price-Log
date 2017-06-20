all:	price_log

price_log:	Stock.o Driver.o
	g++ -std=c++11 -o price_log Stock.o Driver.o
	
Stock.o:	Stock.cpp Stock.h
	g++ -std=c++11 -c Stock.cpp

Driver.o:	Driver.cpp
	g++ -std=c++11 -c Driver.cpp
	
clean:
	rm -vf *.o price_log