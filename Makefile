all: pwrsum.asm
	g++ main.cpp -o main -lstdc++fs
	g++ controlsum.cpp -o controlsum

clean:
	-rm *.out
	-rm *.o
	-rm *~