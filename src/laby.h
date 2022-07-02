#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>


/* Moove into maze */
void moove(char * maze,int width,int height);

/* Associe une valeur à width et height en fonction du niveau*/
void argument(char arg, int *width, int *height) ;

/* donne un pointeur sur une case de la grille */
char * grille_case(char * maze, int x, int y, int width, int height) ;

/* affiche une grille à l'écran */
void afficher_grille(char * maze, int width, int height);

/* Modifie la grille de sorte a faire apparaitre une grille plus type labyrinthe*/
char * change_grille(char * maze, int width, int height);

/* is_valid vérifie que les coordonnées (x, y) sont valides pour un déplacement */
int is_valid(int x, int y, int height, int width, char maze[]) ;

/* is_finish vérifie que l'emplacement sur lequel se trouve les coordonnées (x, y) est une sortie */
int is_finish(int x, int y, int height, int width, char maze[]) ;

/*  Carve the maze starting at x, y. */
void CarveMaze(char *maze, int width, int height, int x, int y) ;

/* Generate maze in matrix maze with size width, height. */
void GenerateMaze(char *maze, int width, int height) ;

/* Solve the maze. */
void SolveMaze(char *maze, int width, int height);