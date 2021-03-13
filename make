default: prog

prog:
	g++  -o prog -std=c++11

clean:
	rm -rf *.o prog