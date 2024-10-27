//
// Created by augus on 27/04/2023.
//

#ifndef PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_GUITARE_H
#define PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_GUITARE_H
#include "../manege.h"
#define NB_MAX_NOTES 20
#define NB_MAX_NOTES2 20
#define NB_MAX_NOTES3 20
#define NB_MAX_NOTES4 20

typedef struct {
    int x, y, r;
    float vitesse;
    int width1, height1;
    int actif;
} Note;


void GuitareHeroJoueur1(bool key[KEY_MAX], ALLEGRO_DISPLAY *display, ALLEGRO_EVENT event, ALLEGRO_BITMAP *fond, Personnage *p1,
                        ALLEGRO_BITMAP *ticket, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *imageperso,Personnage *p2);

#endif //PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_GUITARE_H
