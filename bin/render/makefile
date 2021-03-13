default: prog

prog: main.cpp renderer.o shaderLoader.o
	g++ main.cpp renderer.o shaderLoader.o -o prog -std=c++11 -lglfw3 -lglew32 -lglu32 -lgdi32 -lopengl32 -I drivers\OpenGL\include -L drivers\OpenGL\lib

renderer.o: renderer.cpp
	g++ renderer.cpp -c -std=c++11 -I drivers\OpenGL\include

shaderLoader.o: shaderLoader.cpp
	g++ shaderLoader.cpp -c -I drivers\OpenGL\include

clean:
	rm -rf *.o prog