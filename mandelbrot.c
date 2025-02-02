#include "mandelbrot.h"
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <stdio.h>
#include <complex.h>

// notes
// https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set

static float* x_dimension = NULL;
static float* y_dimension = NULL;

float *linspace(float start, float end, int n)
{
    float* array = (float*)calloc(n, sizeof(float));
    float step = (end - start) / (n - 1);
    for (int i = 0; i < n; i++)
    {
        array[i] = start + i * step;
    }
    return array;
}

int* linspace_int(int start, int end, int n)
{
    int* array = (int*)calloc(n, sizeof(int));
    int step = (end - start) / (n - 1);
    for (int i = 0; i < n; i++)
    {
        array[i] = start + i * step;
    }
    return array;
}

SDL_Surface* generate_mandelbrot_surface(int max_iter, scale_tuple *x_scale, scale_tuple *y_scale, int screen_width, int screen_height)
{
    x_dimension = linspace(x_scale->start, x_scale->end, screen_width);
    y_dimension = linspace(y_scale->start, y_scale->end, screen_height);

    SDL_Surface *surface = SDL_CreateSurface(screen_width, screen_height, SDL_PIXELFORMAT_RGBA32);
    int bound = 2;
    int i = 0;

    // following this algorithm: https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
    int max_iteration_result = 0;
    SDL_LockSurface(surface);
    SDL_PixelFormatDetails details;
    Uint32 *pixels = (Uint32 *)surface->pixels;

    for(int py = 0; py < screen_height; py++) {
        for(int px = 0; px < screen_width; px++) {

            float x = 0;
            float y = 0;
            int iteration = 0;
            while ((x * x + y * y <= 2 * 2) && (iteration < max_iter)) {
                float xtemp = x * x - y * y + x_dimension[px];
                y = 2 * x * y + y_dimension[py];
                x = xtemp;
                iteration++;


                //pixels[px + py * screen_width] = SDL_MapRGB(&details, NULL, 255, 0, 0);
                // if (iteration > max_iteration_result) {
                //     max_iteration_result = iteration;
                // }
            }
            pixels[px + py * screen_width] = SDL_MapRGB(&details, NULL, iteration, iteration, iteration);
        }
    }
    SDL_UnlockSurface(surface);
    // printf("max iteration: %d\n", max_iteration_result);
    return surface;
}

int* mandelbrot_set(
    int max_iter, 
    scale_tuple *x_scale, scale_tuple *y_scale, 
    int screen_width, int screen_height)
{
    x_dimension = linspace(x_scale->start, x_scale->end, screen_width);
    y_dimension = linspace(y_scale->start, y_scale->end, screen_height);

    int *iterationsArray = (int*)calloc(screen_width * screen_height, sizeof(int));
    int bound = 2;
    int i = 0;

    // following this algorithm: https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
    int max_iteration_result = 0;
    for(int py = 0; py < screen_height; py++) {
        for(int px = 0; px < screen_width; px++) {

            float x = 0;
            float y = 0;
            int iteration = 0;
            while ((x * x + y * y <= 2 * 2) && (iteration < max_iter)) {
                float xtemp = x * x - y * y + x_dimension[px];
                y = 2 * x * y + y_dimension[py];
                x = xtemp;
                iteration++;
                if (iteration > max_iteration_result) {
                    max_iteration_result = iteration;
                }
            }
            iterationsArray[px + py * screen_width] = iteration;
        }
    }
    printf("max iteration: %d\n", max_iteration_result);
    return iterationsArray;
}


