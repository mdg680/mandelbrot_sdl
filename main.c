#define SDL_MAIN_USE_CALLBACKS 1 /* see: https://wiki.libsdl.org/SDL3/README/main-functions */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <complex.h>

#include "mandelbrot.h"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint64 last_time = 0;

/* Window dimensions */
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1200
#define FRAME_RATE 60

#define MAX_ITER 255

static scale_tuple x_scale = { -2.0f, 0.5f };
static scale_tuple y_scale = { -1.2f, 1.2f };

// static scale_tuple x_scale = { -1.0f, 0.25f };
// static scale_tuple y_scale = { -0.6f, 0.6f };

static int* current_mandelbrot = NULL;
static int* pallette = NULL;
SDL_Texture* texture = NULL;

static SDL_Surface *mandelbrot_surface = NULL;

/* Initialises application, runs once at startup */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Mandelbrot set explorer using SDL3", "0.1", "com.monoper.mandelbrot");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Mandelbrot SDL3", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    pallette = linspace_int(0, 255, MAX_ITER); // TODO: SDL_SetRenderDrawColor has a float version, which can expand color resolution, should upgrade at a later stage
    current_mandelbrot = mandelbrot_set(MAX_ITER, &x_scale, &y_scale, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_Surface* mandelbrot_surface = generate_mandelbrot_surface(MAX_ITER, &x_scale, &y_scale, WINDOW_WIDTH, WINDOW_HEIGHT);
    texture = SDL_CreateTextureFromSurface(renderer, mandelbrot_surface);


    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    const Uint64 now = SDL_GetTicks();
    const float elapsed = ((float) (now - last_time)) / 1000.0f;  /* seconds since last iteration */
    int i;

    last_time = now;
    float mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    // current_mandelbrot = mandelbrot_set(50, &x_scale, &y_scale, WINDOW_WIDTH, WINDOW_HEIGHT);
    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */
    SDL_RenderTexture(renderer, texture, 0, 0);
    int max_color = 0;
    //SDL_DestroyTexture(texture);
    // for (int y = 0; y < WINDOW_HEIGHT; y++) {
    //     for (int x = 0; x < WINDOW_WIDTH; x++) {
    //         int i = current_mandelbrot[x + y * WINDOW_WIDTH];
    //         if (i < MAX_ITER) {
    //             int c = pallette[i];
    //             if (c > max_color) { max_color = c; }
    //             SDL_SetRenderDrawColor(renderer, c - c/2, c - c/2, c, SDL_ALPHA_OPAQUE);
    //         } else {
    //             SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    //         }
    //         SDL_RenderPoint(renderer, x, y);
    //     }
    // }
    char mouse_position[50];
    sprintf(mouse_position, "(x: %d, y: %d)", (int)mouse_x, (int)mouse_y);
    //printf(mouse_position);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 10, 10, mouse_position);
    int last_ticks = SDL_GetTicks();

    SDL_RenderPresent(renderer);  /* put it all on the screen! */

    while(true) {
        int current_ticks = SDL_GetTicks();
        int elapsed_ticks = current_ticks - last_ticks;
        if (elapsed_ticks >= 1000 / FRAME_RATE) {
            break;
        }
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}