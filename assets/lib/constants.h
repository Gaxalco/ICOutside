#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


typedef struct {
    SDL_Window *window;
    SDL_Surface *surface;
} App;