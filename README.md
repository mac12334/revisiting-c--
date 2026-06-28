I have done very little in c++ and SDL in the past. Due to a disconnect in my brain in me trying to make a Group like object in SDL.
I come from python/pygame and I wanted to branch out. This is my attempt to understand c++ and SDL in respect to pygame and python.

Current projects -
    - Hello SDL -> A quick example of using SDL to make a window, mostly taken from the wiki. I did comment the translations of the code compared to pygame code to show my understanding
    - Hello eventloop -> A little longer example used to show a standard game event loop with user input and a moving square. I also used an FPS constrainer to ensure that the program doesn't run too fast.
    - Hello images -> using the SDL2_image library to load images from png format to texture format. In this test I learned how to use the image library, move an image, and debug a compiler error. I also got an idea of how to animate a texture in SDL by using the drawing rectangle in the argument for drawing. The compiler error I had was one that stumped me for a bit, it said "undefined refrence to 'IMG_Init'". The fix was to include the image library in the linking process for the MakeFile.