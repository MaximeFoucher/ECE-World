#ifndef MAIN_C_TIREBALLON_H
#define MAIN_C_TIREBALLON_H
#include "../manege.h"


#define NUM_CERCLES 10


typedef struct {
    float x, y;
    float dx, dy;
    float rayon;
    bool actif;
    ALLEGRO_COLOR couleur;
} Cercle;
void Tirballon(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_MOUSE_STATE mouse_state, ALLEGRO_DISPLAY *display,ALLEGRO_FONT *police,ALLEGRO_BITMAP *fond,ALLEGRO_BITMAP *ticket,ALLEGRO_BITMAP *imageperso,Personnage* p1, Personnage* p2,bool key[KEY_MAX]) ;

#endif //MAIN_C_TIREBALLON_H
