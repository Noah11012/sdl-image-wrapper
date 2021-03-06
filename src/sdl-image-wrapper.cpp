#include "sdl-image-wrapper.hpp"

SDLImageWrapperException::SDLImageWrapperException(std::string message): m_message(std::move(message))
{

}

SDLImageWrapper::SDLImageWrapper(): m_renderer(nullptr),
                                    m_image(nullptr),
                                    m_degrees(0.0),
                                    m_flip_type(FlipType::None),
                                    m_image_location{0, 0, 0, 0}
{

}

SDLImageWrapper::SDLImageWrapper(SDL_Renderer *renderer, std::string const &image_name, int x, int y): m_renderer(renderer),
                                                                                                       m_image(nullptr),
                                                                                                       m_degrees(0.0),
                                                                                                       m_flip_type(FlipType::None),
                                                                                                       m_image_location{0, 0, 0, 0}
{
    SDL_Surface *image_surface = IMG_Load(image_name.c_str());

    if(!image_surface)
    {
        throw SDLImageWrapperException(std::string("Failed to load image ") + image_name + "\n"
                                       "SDL2 Error: " + SDL_GetError() + "\n");
    }

    m_image = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);

    m_image_location.x = x;
    m_image_location.y = y;

    SDL_QueryTexture(m_image, nullptr, nullptr, &m_image_location.w, &m_image_location.h);
}

SDLImageWrapper::~SDLImageWrapper()
{    
    if(m_image)
        SDL_DestroyTexture(m_image);
}

void SDLImageWrapper::set_position(int new_x, int new_y)
{
    m_image_location.x = new_x;
    m_image_location.y = new_y;
}

void SDLImageWrapper::move(int add_x, int add_y)
{
    m_image_location.x += add_x;
    m_image_location.y += add_y;
}

void SDLImageWrapper::rotate(double degrees)
{
    if(m_degrees + degrees > 360.0)
        m_degrees = 0;
    
    m_degrees += degrees;
}

void SDLImageWrapper::flip(FlipType flip_type)
{
    m_flip_type = flip_type;
}

void SDLImageWrapper::open_image(SDL_Renderer *renderer, const std::string &image_name, int x, int y)
{
    SDL_Surface *image_surface = IMG_Load(image_name.c_str());

    if(!image_surface)
    {
        throw SDLImageWrapperException(std::string("Failed to load image") + image_name + "\n"
                                       "SDL2 Error: " + SDL_GetError() + "\n");
    }

    m_image = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);

    m_image_location.x = x;
    m_image_location.y = y;

    m_renderer = renderer;

    SDL_QueryTexture(m_image, nullptr, nullptr, &m_image_location.w, &m_image_location.h);
}

void SDLImageWrapper::render_image()
{
    if(SDL_RenderCopyEx(m_renderer, m_image, nullptr, &m_image_location, m_degrees, nullptr, static_cast<SDL_RendererFlip>(m_flip_type)) != 0)
        throw SDLImageWrapperException(std::string("Could not render SDL_Texture") + "\n"
                                                    "SDL2 Error: " + SDL_GetError() + "\n");
}