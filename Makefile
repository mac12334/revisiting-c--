
hello_sdl: hello_sdl_src/main.cpp
	g++ hello_sdl_src/main.cpp -lSDL2 -o bin/hello_sdl
eventloop: hello_eventloop_src/main.cpp
	g++ hello_eventloop_src/main.cpp -lSDL2 -o bin/hello_eventloop
images: hello_images/main.cpp
	g++ hello_images/main.cpp -lSDL2 -lSDL2_image -o bin/hello_images
fonts: hello_fonts/main.cpp
	g++ hello_fonts/main.cpp -lSDL2 -lSDL2_ttf -o bin/hello_fonts
anime: hello_animation/main.cpp
	g++ hello_animation/main.cpp -lSDL2 -lSDL2_image -o bin/hello_animation
	./bin/hello_animation