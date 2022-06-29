#include	<SDL.h>
#include	<stdio.h>

int	main(int	argv, char	**argc)
{
	SDL_version nb;
	SDL_VERSION(&nb);

	printf("%d.%d.%d\n",nb.major,nb.minor,nb.patch);

	return(0);
}
