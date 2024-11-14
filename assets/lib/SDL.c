#include "constants.h"

/* Basic SDL functions */

SDL_Rect srcClip = {0, 0, 0, 0};
SDL_Rect destClip = {0, 0, 100, 100};

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

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    app->surface = SDL_GetWindowSurface(app->window);
}

void load_player(Player *player, SDL_Surface *image) {
    if (image == NULL) {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(ERROR);
    }

    SDL_BlitSurface(image, &srcClip, player->image, &destClip);
    SDL_FreeSurface(image);
}

void load_images(App *app, Player *player) {
    for (int i = 0; i < All; i++) {
        SDL_Surface *image = SDL_LoadBMP(PATHS[i]);

        if (i == PlayerImage) {
            load_player(player, image);
            SDL_BlitSurface(player->image, &srcClip, app->surface, &destClip);
        } else {
            if (image == NULL) {
                printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
                SDL_DestroyWindow(app->window);
                SDL_Quit();
                exit(ERROR);
            }

            SDL_BlitSurface(image, NULL, app->images[i], NULL);
            SDL_FreeSurface(image);
        }
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