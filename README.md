# SDL Image Wrapper
SDLImageWrapper is a C++ wrapper around `SDL_Texture` for ease of rendering in SDL2.

## Quick Start

### Build

You will need SDL2 and SDL2_image to build and use this library. This library contains only a header and a source file. Simply include the header file and add the source file to the list of files to be built.

For example, if you have clang++ installed:

```clang++ -o program main.cpp other_file.cpp `sdl2-config --cflags --libs` -lSDL2_image```

In `other_file.cpp`:

```c
#include "sdl-image-wrapper.hpp"

...
```

Of course, if you were using a build system generator like CMake you can just add the source file to the list of files for a target.

### Usage

When using SDLImageWrapper you must ensure that SDL2 is initialized and that also SDL2_image is initialized. The constructor and `open_image()` will throw an `SDLImageWrapperException` if an error occurred. If a call to `render_image()` results in an error, an `SDLImageWrapperException` will also be thrown.

```c
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sdl-image-wrapper.hpp"

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return -1;

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
        return -1;

    SDL_Window *window = SDL_CreateWindow("A simple window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    1280, 720);

    SDL_Renderer *renderer = SDL_CreateRenderer(window);

    try
        SDLImageWrapper image(renderer, "test_image.png", 0, 0);
    catch(SDLImageWrapperException &image_exception)
        std::cout << sdl_exception.what() << "\n";

    /* Get width and height of image */
    std::cout << "Width: " << image.get_width() << "\n";
    std::cout << "Height: " << image.get_height() << "\n";

    /* Flip the image because we can */
    image.flip(SDL::FlipType::Horizontal)

    /* Other options includue SDL::FlipType::None and SDL::FlipType::Vertical */

    SDL_Event event;
    bool keep_window_open = true;
    int x_position = 0;
    while(SDL_PollEvent(&event) || keep_window_open)
    {
        if(event.type == SDL_QUIT)
            keep_window_open = false;
        
        /* Animate the image's position across the x-axis */
        image.set_position(i, 0);

        /* Rotate the image an i'th degree every frame */
        image.rotate(i);

        /* Render the image to the screen */
        try
            image.render_image();
        catch(SDLImageWrapperException &image_exception)
            std::cout << sdl_exception.what() << "\n";

        i++;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
```

