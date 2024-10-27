#ifndef PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_FLAPPY_H
#define PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_FLAPPY_H

#include "../manege.h"

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} flappy_rectangle;


typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} Rectangle_tuyaux;



void flappy_bird(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT *texte, ALLEGRO_BITMAP* fond, ALLEGRO_BITMAP* imageperso, Personnage *perso, Personnage *perso2, ALLEGRO_BITMAP *ticket);

#endif //PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_FLAPPY_H
