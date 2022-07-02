#include    <SDL.h>
#include    <stdlib.h>
#include    <stdio.h>

void    Sdl_ExitWithError(const char    *message);

int main(int    argv, char **argc)
{
    SDL_Window  *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect rectangle;

    rectangle.x = 300;
    rectangle.y = 300;
    rectangle.h = 200;
    rectangle.w = 120;


    if(SDL_Init(SDL_INIT_VIDEO) != 0) Sdl_ExitWithError("CAHRGEMENT DE sdl");

    if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0) Sdl_ExitWithError("Fenetre et rendu");

    if(SDL_SetRenderDrawColor(renderer, 112, 168, 237,SDL_ALPHA_OPAQUE) != 0)Sdl_ExitWithError("COuleur");

    if(SDL_RenderDrawPoint(renderer, 100, 450) != 0)Sdl_ExitWithError("impossible de dessiner le point");

    if(SDL_RenderDrawLine(renderer, 50, 50, 500, 500) != 0)Sdl_ExitWithError("impossible de dessiner la ligne");
    SDL_RenderPresent(renderer);

    if(SDL_RenderDrawRect(renderer, &rectangle) != 0)Sdl_ExitWithError("impossible de dessiner le point");
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void    Sdl_ExitWithError(const char    *message)
{
    SDL_Log("Erreur: %s > %s\n", message,SDL_GetError());
    SDL_Quit();

    exit(EXIT_FAILURE);
}
//    if(SDL_RenderClear(renderer) != 0)Sdl_ExitWithError("Clear rendu echouer");