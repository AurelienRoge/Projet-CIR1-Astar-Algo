//L'algorithme A* qui trouve le chemin le plus court dans un labyrinthe (ici seulement avec les mouvement haut bas droite gauche)
//On peut changer la taille dans star_1.h
//
#include "stdio.h"
#include "star_priQueue.h"


void printshortest(close cls[M + 1][N + 1], point start, point end) {
	close* steps[MAXSIZE];
	int flag = 1;
	int i;

	steps[0] = cls[end.x][end.y].from;
	for (i = 1;; i++) {
		steps[i] = steps[i - 1]->from;
		flag = i + 1;
		if (steps[i]->p.x == start.x && steps[i]->p.y == start.y)
			break;
	}
	printf("The shortest path takes %d moves\n", flag);
	for (i = flag - 1; i >= 0; i--) {
		printf("(%d,%d)->", steps[i]->p.x, steps[i]->p.y);
	}
}

int within(int x, int y) {
	if (x >= 1 && x <= M && y >= 1 && y <= N)
		return 1;
	else
		return 0;
}
int getshortest(int maze[M + 2][N + 2], point start, point end) {
	close cls[M + 1][N + 1];
	open op;
	close* c;
	int x0, y0;//position actuelle
	int x1, y1, g1;//noeud enfant
	int i, j;

	point dir[4];
	dir[0].x = 0; dir[0].y = 1;//Droite
	dir[1].x = 0; dir[1].y = -1;//Gauche
	dir[2].x = 1; dir[2].y = 0;//Bas
	dir[3].x = -1; dir[3].y = 0;//Haut

	initOpen(&op);
	initClose(cls, start.x, start.y, end.x, end.y);
	cls[start.x][start.y].visited = 1;

	pushOpen(&op, cls, 1, 1, 0);
	while (op.len != 0) {
		c = popOpen(&op);
		x0 = c->p.x;
		y0 = c->p.y;

		if (c->H == 0) {
			printshortest(cls, start, end);
			return 1;
		}
		for (i = 0; i < 4; i++) {
			x1 = x0 + dir[i].x;
			y1 = y0 + dir[i].y;
			if (within(x1, y1) == 1 && maze[x1][y1] == 0) {
				if (cls[x1][y1].visited == 0) {
					cls[x1][y1].visited = 1;
					cls[x1][y1].from = c;
					g1 = cls[x0][y0].G + 1;
					pushOpen(&op, cls, x1, y1, g1);
				}
				else {
					for (j = 0; j < op.len - 1; j++) {
						if (op.arr[j]->p.x == x1 && op.arr[j]->p.y == y1 && cls[x0][y0].G + 1 + cls[x0][y0].H < op.arr[j]->G) {
							op.arr[j]->F = cls[x0][y0].G + 1 + cls[x0][y0].H;
							op.arr[j]->from = &(cls[x0][y0]);
							sortOpen(&op);
						}
					}
				}
			}
			else
				continue;
		}
	}
	printf("x");
	return 0;
}



int main() {

	int f;
	int i, j;
	//On a instauré des murs tout autour qui permettent ansi d'empecher l'algorithme de sortir de la carte
	//De ce fait, la taille est augmentée de 2 en abscisse et en ordonnée
	int maze[M + 2][N + 2] =
	{
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,1,1,0,0,1,0,1 },
		{ 1,0,0,0,0,1,0,1,1,1 },
		{ 1,1,0,1,0,0,0,0,0,1 },
		{ 1,1,0,0,1,0,0,0,0,1 },
		{ 1,0,0,1,0,0,0,0,0,1 },
		{ 1,1,1,0,1,0,1,0,0,1 },
		{ 1,0,0,1,0,1,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
	};

	for (i = 1; i <= M; i++) {
		for (j = 1; j <= N; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}

	point start, end;
	//point de départ(1,1)  point d'arrivée(7,7);
	start.x = 1;
	start.y = 1;
	end.x = 8;
	end.y = 8;

	f = getshortest(maze, start, end);
	if (f == 0)
		printf("This maze has no solution!");


	return 0;
}
