#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FPS 60
#define PATH_IMAGE "assets/images"
#define PATH_SOUND "assets/sounds"

typedef struct {
    SDL_Window *window;
    SDL_Surface *surface;
} App;