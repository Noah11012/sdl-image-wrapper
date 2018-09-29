#include <iostream>
#include <SDL2/SDL.h>
#include "../src/sdl-image-wrapper.hpp"

int main()
{
    SDL_Window *window = SDL_CreateWindow("SDL Image Wrapper",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          1280, 720, 0);

    if(!window)
        return -1;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    if(!renderer)
        return -1;

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        return -1;

    try
    {
        SDLImageWrapper image(renderer, "../test/background.png", 0, 0);
        SDL_Event event;
        bool keep_open = true;
        while(SDL_PollEvent(&event) != 0 || keep_open)
        {
            if(event.type == SDL_QUIT)
                break;
            
            SDL_RenderClear(renderer);
            image.render_image();
            SDL_RenderPresent(renderer);
        }
    } catch(SDLImageWrapperException &image_exception)
    {
        std::cout << image_exception.what() << "\n";
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}