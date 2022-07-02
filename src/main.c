#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "laby.h"


int main(int argc,char *argv[]) {

    printf("\033[0;31m");

    int choix=1;

    while (choix != 0)
    {

    printf("\n");
    printf("		********************** Welcome! *********************\n");
    printf("		*                     MAZE GAME                     *\n");
    printf("		*  1.Enter Game                                     *\n");
    printf("		*  2.Settings                                       *\n");
    printf("		*  3.Quit                                           *\n");
    printf("		*                                                   *\n");
    printf("		*****************************************************\n");
    printf("\n");
    printf("		Please choose one from 1-3:\n");
		printf("\033[0m");
		printf("		");
    scanf("%d", &choix);


    switch (choix){
      case 1:
        printf("Enter Game:\n");


        // printf("\e[?25l");

         int width = 9;
				 int height = 9;
         char *maze;


				 /*S'assure qu'on donne bien le niveau du labyrinthe voulu et si voulu la solution avec*/
				 if(argc != 2 && argc != 3) {
			      printf("Usage: maze <level> [s]\n");
			      exit(EXIT_FAILURE);
			   }

				 if(argc == 3 && argv[2][0] != 's') {
						printf("error: invalid argument\n");
						exit(EXIT_FAILURE);
				 }

				 /*Associe une valeur à width et height en fonction du niveau*/
				 argument(atoi(argv[1]),&width,&height);





         /* Allocate the maze array. */
         maze = (char *)malloc(width * height * sizeof(char));
         if(maze == NULL) {
            printf("error: not enough memory\n");
            exit(EXIT_FAILURE);
         }

         /* Generate and display the maze. */
         GenerateMaze(maze, width, height);
         // ShowMaze(maze, width, height);




         /* Resolve le labyrinthe si demandé */
         if(argc == 3) {
            SolveMaze(maze, width, height);
         }

         moove(maze,width,height);

				 printf("\033[0;32m");
				 printf("		Bien jouer ! Voulez vous passer au niveau suivant ?\n");
				 printf("\033[0m");

         /* Clean up. */
         free(maze);


        choix = 0;
      break;
      case 2:
        printf("Enter Settings:\n");
        choix = 0;
      break;
      case 3:
        printf("You quit !\n");
        choix = 0;
      break;

    }
  }
  printf("\e[?25h");
  exit(EXIT_SUCCESS);

}