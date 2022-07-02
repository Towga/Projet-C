#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>


void  Exit_With_Error(const char    *message)
{
    printf("Erreur: %s \n", message);
    exit(EXIT_FAILURE);
}

char * edit_laby(char  *laby, int  width, int  height)
{
   printf("enter an array of height: %d and width: %d\n",height,width);

   laby = scanf("%c",laby);
   for (int i = 0; i < width*height; i++)
   {
      printf("%c",laby[i]);
   }
   
}

char * grille_case(char * laby, int x, int y, int width, int height) {
	if(laby == NULL || x < 0 || y < 0 || x >= width || y >= height) {
		return NULL;
	}
	return laby + (x + y * width);
}

void afficher_grille(char * laby, int width, int height) {
	int x, y;
	for(y = 0; y < height; ++y) {
		for(x = 0; x < width; ++x) {
			mvprintw(y, x, "%c", * grille_case(laby, x, y, width,height));
		}
	}
}

char * swap_grille(char * laby, int width, int height) {
	int x, y;
	for(y = 0; y < height; ++y) {
		for(x = 0; x < width; ++x) {
			if (laby[y * width + x] == 1){
				laby[y * width + x] = 'I';
			}else if ((laby[y * width + x] == 0) || (laby[y * width + x] == 3)){
				laby[y * width + x] = ' ';
			}else if (laby[y * width + x] == 2){
				laby[y * width + x] = '.';
			}else{
				laby[y * width + x] = 'x';
			}
		}
	}
	return laby;
}


/* is_valid vérifie que les coordonnées (x, y) sont valides pour un déplacement */
int is_valid(int x, int y, int height, int width, char laby[]) {
    if ((y>height)||(x>width)||(y<0)||(x<0)) return 0;
    if (laby[y * width + x] == 'I'){
      return 0;
    }else{
      return 1;
    }
}

/* is_finish vérifie que l'emplacement sur lequel se trouve les coordonnées (x, y) est une sortie */
int is_finish(int x, int y, int height, int width, char laby[]) {
  if (laby[y * width + x] == 'x'){
    return 1;
  }else{
    return 0;
  }
}


/* Affiche le laby. */
void affiche_laby(char *laby, int width, int height) {
   int x, y;
   for(y = 0; y < height; y++) {
      for(x = 0; x < width; x++) {
         switch(laby[y * width + x]) {
         case 1:  printf("II");  break;
         case 2:  printf("..");  break;
         default: printf("  ");  break;
         }
      }
      printf("\n");
   }
}

/*  creuse le laby. */
void creuse_laby(char  *laby, int  width, int  height, int x, int   y) {

   int   x1,   y1;
   int   x2,   y2;
   int   dirX, dirY;
   int   dir,  count;

   dir = rand() % 4;
   count = 0;
   while(count < 4) {
      dirX = 0; dirY = 0;
      switch(dir) {
      case 0:  dirX = 1;  break;
      case 1:  dirY = 1;  break;
      case 2:  dirX = -1; break;
      default: dirY = -1; break;
      }
      x1 = x + dirX;
      y1 = y + dirY;
      x2 = x1 + dirX;
      y2 = y1 + dirY;
      if(   x2 > 0 && x2 < width && y2 > 0 && y2 < height
         && laby[y1 * width + x1] == 1 && laby[y2 * width + x2] == 1) {
         laby[y1 * width + x1] = 0;
         laby[y2 * width + x2] = 0;
         x = x2; y = y2;
         dir = rand() % 4;
         count = 0;
      } else {
         dir = (dir + 1) % 4;
         count += 1;
      }
   }

}

/* Genere le laby . */
void Generate_laby(char  *laby, int  width, int  height) {

   int   x, y;

   /* Initialize le laby. */
   for(x = 0; x < width * height; x++) {
      laby[x] = 1;
   }
   /* creuse le laby. */
   for(y = 1; y < height; y += 2) {
      for(x = 1; x < width; x += 2) {
         creuse_laby(laby, width, height, x, y);
      }
   }
   laby[(height - 1) * width + (width - 2)] = 4;

}

/* resoudre le laby. */
void resoudrelaby(char  *laby, int  width, int  height) {

   int   dir,  count;
   int   x, y;
   int   dirX, dirY;
   bool  avancer;

   /* enleve l'entree et la sortie. */
   laby[0 * width + 1] = 1;
   laby[(height - 1) * width + (width - 2)] = 1;

   avancer = TRUE;
   dir = 0;
   count = 0;
   x = 1;
   y = 1;
   while(x != width - 2 || y != height - 2) {
      dirX = 0; dirY = 0;
      switch(dir) {
      case 0:  dirX = 1;  break;
      case 1:  dirY = 1;  break;
      case 2:  dirX = -1; break;
      default: dirY = -1; break;
      }
      if(   (avancer  && laby[(y + dirY) * width + (x + dirX)] == 0)
         || (!avancer && laby[(y + dirY) * width + (x + dirX)] == 2)) {
         laby[y * width + x] = avancer ? 2 : 3;
         x += dirX;
         y += dirY;
         avancer = TRUE;
         count = 0;
         dir = 0;
      } else {
         dir = (dir + 1) % 4;
         count += 1;
         if(count > 3) {
            avancer = FALSE;
            count = 0;
         }
      }
   }

   /* Replace l'entree et la sortie. */
   laby[(height - 2) * width + (width - 2)] = 2;
   laby[(height - 1) * width + (width - 2)] = 4;

}

int main(int   argc,char   *argv[]) {

    printf("\033[0;31m");

    int  choix=1;
    
    while (choix != 0)
    {

    printf("\n");
    printf("      ********************** Welcome! *********************\n");
    printf("      *                     laby GAME                     *\n");
    printf("      * 1.Enter Game                                      *\n");
    printf("      * 2.Settings                                        *\n");
    printf("      * 3.Quit                                            *\n");
    printf("      *                                                   *\n");
    printf("      *****************************************************\n");
    printf("\n");
    printf("Please choose one from 1-4:\n");
		printf("\033[0m");
    scanf("%d", &choix);


    switch (choix){
      case 1:
        printf("Enter Game:\n");
         int   width,   height;
         char  *laby;
			char  *laby_swap;


         if(argc != 3 && argc != 4) Exit_With_Error("erreur: veuillez renseigner les bons arguments");

          width = atoi(argv[1]);
         height =atoi(argv[2]);
         if(width < 4 || height < 4)Exit_With_Error("erreur: Labyrinthe trop petit");

         if(argc == 4 && argv[3][0] != 's') Exit_With_Error("erreur: argument invalide");
         /* Allocate le laby array. */
         laby = (char *)malloc(width * height * sizeof(char));
         if(laby == NULL) {
            printf("error: not enough memory\n");
            exit(EXIT_FAILURE);
         }

         /* Genere et Affiche le laby. */
         Generate_laby(laby, width, height);

         /* resoudre le laby*/
         if(argc == 4) {
            resoudrelaby(laby, width, height);
            affiche_laby(laby, width, height);
         }

         /* Moove into laby */
				 laby_swap = swap_grille(laby,width,height);
         int x = 1, y = 1;
         int move_x, move_y;
         initscr();
         noecho();
         cbreak();
         do {
					 clear();
					 afficher_grille(laby_swap, width, height);

					 // affiche_laby(laby, width, height);
           mvprintw(y, x, "@");
           mvprintw(y, x, "");
           refresh();
           move_x = x; move_y = y;
           switch(getch()) {
            /*QWERTY*/
             case 'w': move_y = y - 1; break;
             case 's': move_y = y + 1; break;
             case 'a': move_x = x - 1; break;
             case 'd': move_x = x + 1; break;
             /*AZERTY*/
            //  case 'z': move_y = y - 1; break;
            //  case 's': move_y = y + 1; break;
            //  case 'q': move_x = x - 1; break;
            //  case 'd': move_x = x + 1; break;
           }
           if(is_valid(move_x, move_y, height, width,laby)) {
           x = move_x; y = move_y;
           }
         } while(! is_finish(x, y, height, width, laby));

         refresh();
         endwin();
				 printf("\033[0;32m");
				 printf("Bien jouer ! Voulez vous passer au niveau suivant ?\n");
				 printf("\033[0m");

         /* Clean up. */
         free(laby);


        choix = 0;
      break;
      case 2:
      /* recupere l'entree utlisateur */
         width = atoi(argv[1]);
         height =atoi(argv[2]);
         
         if(width < 4 || height < 4)Exit_With_Error("erreur: Labyrinthe trop petit");

        printf("Enter Settings:\n");

        edit_laby(laby, width, height);
        
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