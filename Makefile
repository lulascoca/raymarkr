all:
	g++ ./src/main.cpp -o ./build/raymarkr -lSDL2main -lSDL2

test:
	g++ ./src/main.cpp -o ./build/raymarkr -lSDL2main -lSDL2  && ./build/raymarkr

