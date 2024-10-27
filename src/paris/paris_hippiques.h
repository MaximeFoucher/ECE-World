#ifndef PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_PARIS_HIPPIQUES_H
#define PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_PARIS_HIPPIQUES_H
#include "../manege.h"

typedef struct {
    char nom[50];
    ALLEGRO_BITMAP* cheval;
    int sx;
    int sy;
    int sw;
    int sh;
    int dx;
    int dy;
    int dw;
    int dh;

    int v;

    int flags;
} Pokemon;

void EntrerParisHippiques(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* texte, ALLEGRO_BITMAP* fond, ALLEGRO_BITMAP* imageperso, Personnage *perso, Personnage *p2, ALLEGRO_BITMAP *ticket);


#endif //PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_PARIS_HIPPIQUES_H
