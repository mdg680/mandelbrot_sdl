#ifndef _DRAW_UTILS_H
#define _DRAW_UTILS_H

#include <SDL3/SDL.h>

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint32 *const target_pixel = (Uint32 *)((Uint8 *)surface->pixels 
                                         + y * surface->pitch 
                                         + x * sizeof(Uint32));
    *target_pixel = pixel;
    // Uint32 *pixels = (Uint32 *)surface->pixels;
    // pixels[x + y * surface->w] = pixel;
}

#endif // _DRAW_UTILS_H
