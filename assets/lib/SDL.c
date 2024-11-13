#include "constants.h"

/* Basic SDL functions */

void start_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        exit(ERROR);
    }
}

void init_SDL(App *app) {
    start_SDL();

    app->window = SDL_CreateWindow("ICOutside", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (app->window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(ERROR);
    }

    app->surface = SDL_GetWindowSurface(app->window);
}

void load_images(App *app) {
    for (int i = 0; i < All; i++) {
        SDL_Surface *image = SDL_LoadBMP(PATHS);

        if (image == NULL) {
            printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
            SDL_DestroyWindow(app->window);
            SDL_Quit();
            exit(ERROR);
        }

        SDL_BlitSurface(image, NULL, app->images + i, NULL);
        SDL_FreeSurface(image);
    }
}

void load_sound(char *path) {
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    if (SDL_LoadWAV(path, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        printf("SDL_LoadWAV Error: %s\n", SDL_GetError());
        exit(ERROR);
    }

    SDL_AudioDeviceID deviceId =
        SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0) {
        printf("SDL_OpenAudioDevice Error: %s\n", SDL_GetError());
        SDL_FreeWAV(wavBuffer);
        exit(ERROR);
    }

    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    if (success != 0) {
        printf("SDL_QueueAudio Error: %s\n", SDL_GetError());
        SDL_FreeWAV(wavBuffer);
        exit(ERROR);
    }

    SDL_PauseAudioDevice(deviceId, 0);
}

void close_SDL(App *app) {
    SDL_DestroyWindow(app->window);
    app->window = NULL;
    SDL_Quit();
}

void render(App *app) {
    SDL_UpdateWindowSurface(app->window);
}

void white_screen(App *app) {
    SDL_FillRect(app->surface, NULL,
                 SDL_MapRGB(app->surface->format, 255, 255, 255));
}

void delay(int ms) {
    SDL_Delay(ms);
}

void load_images(Player *player) {
    char *path = "assets/images/characters/Hipster/kungfou.bmp";
    SDL_Surface *image = SDL_LoadBMP(path);

    if (image == NULL) {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(ERROR);
    }

    SDL_BlitSurface(image, NULL, player->image, NULL);
    SDL_FreeSurface(image);
}