#include "assets/lib/SDL.c"

App app;

int main() {
    init_SDL(app);
    white_screen(app);
    render(app);

    delay(2000);

    close_SDL(app);

    return EXIT_SUCCESS;
}