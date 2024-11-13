#include "assets/lib/SDL.c"

App app;
Player player;

int main() {
    init_SDL(&app);

    white_screen(&app);
    load_player(&app, "assets/images/characters/Hipster/kungfou.bmp");
    render(&app);

    SDL_Event e;
    bool quit = false;

    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
        }
        render(&app);
    }

    close_SDL(&app);

    return EXIT_SUCCESS;
}