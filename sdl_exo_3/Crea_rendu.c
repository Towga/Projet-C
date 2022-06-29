#include    <SDL.h>
#include    <stdlib.h>
#include    <stdio.h>

void    Sdl_ExitWithError(const char    *message);

int main(int    argv, char **argc)
{
    SDL_Window  *window = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Sdl_ExitWithError("CAHRGEMENT DE sdl");
    }
    window = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if( window == NULL)
    {
        Sdl_ExitWithError("creation de la fenetre");
        
        exit(EXIT_FAILURE);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void    Sdl_ExitWithError(const char    *message)
{
    SDL_Log("Erreur: %s > %s\n", message,SDL_GetError());
    SDL_Quit();

    exit(EXIT_FAILURE);
}