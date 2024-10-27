#ifndef PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_CANARD_H
#define PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_CANARD_H
#include "../manege.h"

#define NbCanard 30



typedef struct {
    float x;
    float y;
    int rayon;
    bool actif;
}CANARD;


int Canard(ALLEGRO_EVENT_QUEUE *queue, bool key[KEY_MAX], ALLEGRO_BITMAP *fond, Personnage *perso,
            ALLEGRO_BITMAP *ticket, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *imageperso, Personnage *p2);

#endif //PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_CANARD_H
