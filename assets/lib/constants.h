#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define FPS 60
#define PATHS "assets/images/characters/Hipster/kungfou.bmp"

typedef enum {
    PlayerImage,
    Zombie,
    Monster,
    All
} Images;

typedef struct {
    SDL_Window *window;
    SDL_Surface *surface;

    SDL_Surface *images[All];
} App;

typedef struct {
    int x, y;
    int w, h;
    int dx, dy;
    SDL_Surface *image;
} Player;