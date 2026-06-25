
hello_sdl: hello_sdl_src/main.cpp
	g++ hello_sdl_src/main.cpp -lSDL2 -o bin/hello_sdl
eventloop: hello_eventloop_src/main.cpp
	g++ hello_eventloop_src/main.cpp -lSDL2 -o bin/hello_eventloop