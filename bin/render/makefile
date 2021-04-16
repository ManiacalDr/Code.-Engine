default: prog

prog: main.cpp renderer.o shaderLoader.o scene.o sprite.o
	g++ main.cpp renderer.o shaderLoader.o sprite.o scene.o -o prog -std=c++11 -lglfw3 -lglew32 -lglu32 -lgdi32 -lopengl32 -lfreetype -I drivers\OpenGL\include -L drivers\OpenGL\lib
	rm -rf *.o

renderer.o: renderer.cpp
	g++ renderer.cpp -c -std=c++11 -I drivers\OpenGL\include

shaderLoader.o: shaderLoader.cpp
	g++ shaderLoader.cpp -c -I drivers\OpenGL\include

scene.o: scene.cpp sprite.o
	g++ scene.cpp -c -I drivers\OpenGL\include

sprite.o: sprite.cpp
	g++ sprite.cpp -c -I drivers\OpenGL\include

clean:
	rm -rf *.o prog