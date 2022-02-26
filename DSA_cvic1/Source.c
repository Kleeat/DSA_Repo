#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct prvok
{
	int hodnota;
	struct prvok* lava;
	struct prvok* prava;
	int posledny;
} PRVOK;

/*void clearmem(PRVOK*)
{
	
}
*/
void vypis(PRVOK* start)
{
	PRVOK* akt;
	akt = start;
	int i, j;
	for (i = 1; akt->posledny != 1; i++)
	{
		printf("Level:%d %d<-%d->%d", i, akt->lava->hodnota, akt->hodnota, akt->prava->hodnota);
		akt = akt->lava;
	}
	return 0;
}

void main()
{
	PRVOK* start = NULL;
	start = (PRVOK*)malloc(sizeof(PRVOK));
	start->lava = (PRVOK*)malloc(sizeof(PRVOK));
	start->prava = (PRVOK*)malloc(sizeof(PRVOK));
	start->hodnota = 1;
	start->lava->hodnota = 2;
	start->lava->posledny = 1;
	start->prava->hodnota = 3;
	start->prava->posledny = 1;
	vypis(start);
	return 0;
}
