#pragma once

#include <SDL2/SDL_image.h>
#include <string>
#include <exception>

class SDLImageWrapperException: std::exception
{
public:
    explicit SDLImageWrapperException(std::string message);
    char const *what() { return m_message.c_str(); }

private:
    std::string m_message;
};

class SDLImageWrapper
{
public:
    SDLImageWrapper();
    SDLImageWrapper(SDL_Renderer *renderer, std::string const &image_name, int x, int y);
    ~SDLImageWrapper();

    void open_image(SDL_Renderer *renderer, const std::string &image_name, int x, int y);
    void render_image();

    void set_renderer(SDL_Renderer *renderer) { m_renderer = renderer; }

    SDL_Renderer const *get_renderer() const { return m_renderer; } 
    SDL_Renderer *get_renderer() { return m_renderer; }

    void set_position(int new_x, int new_y);
    void move(int add_x, int add_y);

    int &get_x() { return m_image_location.x; }
    int const &get_x() const { return m_image_location.x; }

    int &get_y() { return m_image_location.y; }
    int const &get_y() const { return m_image_location.y; }

    int &get_width() { return m_image_location.w; }
    int const &get_width() const { return m_image_location.w; }

    int &get_height() { return m_image_location.h; }
    int const &get_height() const { return m_image_location.h; }

private:
    SDL_Renderer *m_renderer;
    SDL_Texture *m_image;
    SDL_Rect m_image_location;
};