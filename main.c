#include "assets/lib/SDL.c"

App app;

int main() {
    init(app);
    SDL_Delay(2000);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    return 0;
}