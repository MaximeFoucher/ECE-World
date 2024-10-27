#ifndef PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_TAUPE_H
#define PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_TAUPE_H
#include "../manege.h"

#define WINDOW_SCALE 0.75
#define NbTaupe 6
#define CLEAR 0
#define HAPPY 1
#define SAD 2
#define EMPTY 3
#define TAILLE 80

#define MARTEAU_UP 0
#define MARTEAU_DOWN 1

typedef struct {
    float x;
    float y;
    int rayon;
    bool actif;
    int width,height;
    int statut;
    int ctpAnimation;
    ALLEGRO_BITMAP *happy;
    ALLEGRO_BITMAP *sad;
    ALLEGRO_BITMAP *leave;
}TAUPE;

typedef struct {
    int x,y;
    int width, height;
    int statut;
    int ctpAnimation;
    ALLEGRO_BITMAP *image;
}MARTEAU;

typedef struct{
    int score;
}Player;

bool end,pause,draw;

void Taupe_la (ALLEGRO_EVENT_QUEUE *queue, bool key[KEY_MAX], ALLEGRO_BITMAP *fond, Personnage *p1,
               ALLEGRO_BITMAP *ticket, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *imageperso,Personnage *perso2);


#endif //PROJET_2022_2023_ECE_WORLD_ECE_WORLD_Q_TAUPE_H
