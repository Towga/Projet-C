#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>




/* Associe une valeur à width et height en fonction du niveau*/
void argument(int arg, int * width, int * height) {

  switch (arg) {
    case 1:
      *width = 7;
      *height = 7;
      break;
    case 2:
      *width = 11;
      *height = 9;
      break;
    case 3:
      *width = 13;
      *height = 13;
      break;
    case 4:
      *width = 21;
      *height = 15;
      break;
    case 5:
      *width = 27;
      *height = 21;
      break;
  }

}

/* donne un pointeur sur une case de la grille */
char * grille_case(char * maze, int x, int y, int width, int height) {
	if(maze == NULL || x < 0 || y < 0 || x >= width || y >= height) {
		return NULL;
	}
	return maze + (x + y * width);
}

/* affiche une grille à l'écran */
void afficher_grille(char * maze, int width, int height) {
	int x, y;
	for(y = 0; y < height; ++y) {
		for(x = 0; x < width; ++x) {
			mvprintw(y, x, "%c", * grille_case(maze, x, y, width,height));
		}
	}
}

/* Modifie la grille de sorte a faire apparaitre une grille plus type labyrinthe*/
char * change_grille(char * maze, int width, int height) {
	int x, y;
	for(y = 0; y < height; ++y) {
		for(x = 0; x < width; ++x) {
			if (maze[y * width + x] == 1){
				maze[y * width + x] = 'I';
			}else if ((maze[y * width + x] == 0) || (maze[y * width + x] == 3)){
				maze[y * width + x] = ' ';
			}else if (maze[y * width + x] == 2){
				maze[y * width + x] = '.';
			}else{
				maze[y * width + x] = 'x';
			}
		}
	}
	return maze;
}


/* is_valid vérifie que les coordonnées (x, y) sont valides pour un déplacement */
int is_valid(int x, int y, int height, int width, char maze[]) {
    if ((y>height)||(x>width)||(y<0)||(x<0)) return 0;
    if (maze[y * width + x] == 'I'){
      return 0;
    }else{
      return 1;
    }
}

/* is_finish vérifie que l'emplacement sur lequel se trouve les coordonnées (x, y) est une sortie */
int is_finish(int x, int y, int height, int width, char maze[]) {
  if (maze[y * width + x] == 'x'){
    return 1;
  }else{
    return 0;
  }
}


/*  Carve the maze starting at x, y. */
void CarveMaze(char *maze, int width, int height, int x, int y) {

   int x1, y1;
   int x2, y2;
   int dx, dy;
   int dir, count;

   dir = rand() % 4;
   count = 0;
   while(count < 4) {
      dx = 0; dy = 0;
      switch(dir) {
      case 0:  dx = 1;  break;
      case 1:  dy = 1;  break;
      case 2:  dx = -1; break;
      default: dy = -1; break;
      }
      x1 = x + dx;
      y1 = y + dy;
      x2 = x1 + dx;
      y2 = y1 + dy;
      if(   x2 > 0 && x2 < width && y2 > 0 && y2 < height
         && maze[y1 * width + x1] == 1 && maze[y2 * width + x2] == 1) {
         maze[y1 * width + x1] = 0;
         maze[y2 * width + x2] = 0;
         x = x2; y = y2;
         dir = rand() % 4;
         count = 0;
      } else {
         dir = (dir + 1) % 4;
         count += 1;
      }
   }

}

/* Generate maze in matrix maze with size width, height. */
void GenerateMaze(char *maze, int width, int height) {

   int x, y;

   /* Initialize the maze. */
   for(x = 0; x < width * height; x++) {
      maze[x] = 1;
   }
   // maze[1 * width + 1] = 2;

   /* Seed the random number generator. */
   srand(time(0));

   /* Carve the maze. */
   for(y = 1; y < height; y += 2) {
      for(x = 1; x < width; x += 2) {
         CarveMaze(maze, width, height, x, y);
      }
   }

   /* Set up the entry and exit. */
   // maze[0 * width + 1] = 3;
   // maze[(height - 1) * width + (width - 2)] = 3;
   // maze[(height - 2) * width + (width - 2)] = 3;
    maze[(height - 1) * width + (width - 2)] = 4;

}

/* Solve the maze. */
void SolveMaze(char *maze, int width, int height) {

   int dir, count;
   int x, y;
   int dx, dy;
   int forward;

   /* Remove the entry and exit. */
   maze[0 * width + 1] = 1;
   maze[(height - 1) * width + (width - 2)] = 1;

   forward = 1;
   dir = 0;
   count = 0;
   x = 1;
   y = 1;
   while(x != width - 2 || y != height - 2) {
      dx = 0; dy = 0;
      switch(dir) {
      case 0:  dx = 1;  break;
      case 1:  dy = 1;  break;
      case 2:  dx = -1; break;
      default: dy = -1; break;
      }
      if(   (forward  && maze[(y + dy) * width + (x + dx)] == 0)
         || (!forward && maze[(y + dy) * width + (x + dx)] == 2)) {
         maze[y * width + x] = forward ? 2 : 3;
         x += dx;
         y += dy;
         forward = 1;
         count = 0;
         dir = 0;
      } else {
         dir = (dir + 1) % 4;
         count += 1;
         if(count > 3) {
            forward = 0;
            count = 0;
         }
      }
   }

   /* Replace the entry and exit. */
   maze[(height - 2) * width + (width - 2)] = 2;
   maze[(height - 1) * width + (width - 2)] = 4;

}

/* Moove into maze */
void moove(char * maze,int width,int height){
  char *maze_change;
  maze_change = change_grille(maze,width,height);
  int x = 1, y = 1;
  int move_x, move_y;
  initscr();
  noecho();
  cbreak();
  do {
    clear();
    afficher_grille(maze_change, width, height);


    printf("\033[0;31m");
    mvprintw(y, x, "@");
    mvprintw(y, x, "");
    refresh();
    move_x = x; move_y = y;
    switch(getch()) {
      case 'z': move_y = y - 1; break;
      case 's': move_y = y + 1; break;
      case 'q': move_x = x - 1; break;
      case 'd': move_x = x + 1; break;
    }
    if(is_valid(move_x, move_y, height, width,maze)) {
    x = move_x; y = move_y;
    }


  } while(! is_finish(x, y, height, width, maze));

  refresh();
  endwin();
}