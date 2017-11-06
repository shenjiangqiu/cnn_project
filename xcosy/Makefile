all:libxcosy.so

libxcosy.so:figue.o xcosy.o
	g++ -o libxcosy.so -L/usr/local/cuda/lib64 -lcuda -lcudart -lcublas -lcurand -I/usr/local/cuda/include  -fPIC -shared -O3 figue.o xcosy.o

figue.o:figue.cpp figue.h xcosy.h
	g++ -o figue.o -c -fPIC -std=c++11 -Wall -O3  -I/usr/local/cuda/include figue.cpp

xcosy.o:xcosy.h xcosy.cu
	nvcc xcosy.cu -o xcosy.o -c --compiler-options="-Wall -O3 -fPIC" 

clean:
	rm -rf *.o libxcosy.so ~/.lib/libxcosy.so

install:
	cp libxcosy.so ~/.lib/