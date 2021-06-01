#pragma once
#include "stdio.h"
#include "malloc.h"
#include "math.h"


# define M 8//TAILLE
# define N 8//TAILLE


typedef struct node1 {
	int x;
	int y;
}point;

typedef struct node2 {
	point  p;
	struct node2* from;
	int H, F, G;
	int visited;
}close;//Liste fermée (closedList)

//Initialisation de la liste fermée
void initClose(close cls[M + 1][N + 1], int startx, int starty, int endx, int endy) {
	int i, j;
	for (i = 1; i <= M; i++) {
		for (j = 1; j <= N; j++) {
			cls[i][j].p.x = i;
			cls[i][j].p.y = j;
			cls[i][j].visited = 0;
			cls[i][j].G = cls[i][j].F = 0;
			cls[i][j].H = abs(i - endx) + abs(j - endy);//Calcul de l'heuristique
		}
	}
	cls[startx][starty].F = cls[startx][starty].H;//Evaluation du cout de départ
}
