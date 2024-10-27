#ifndef PROJET2MANEGE_MANEGE_H
#define PROJET2MANEGE_MANEGE_H
#include<allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include<time.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#define LARGEUR 1280
#define HAUTEUR 816
#define MAXNOM 100


typedef struct {
    float x;
    float y;
    int skin;
    int tickets;
    int score;
    char nom;
    bool verif_nom;
    bool touractif;
}Personnage;

////ajouter nom et selectionner skin

enum {
    HAUT, BAS, GAUCHE, DROITE, ESCAPE, ENTER, SOURIS, UN, DEUX, A, B, C, D, E , F, G, H, I, J, K, L, M, N, O, P, Q, R,
    S, T, U, V, W, X, Y, Z, SUPPRIMER, KEY_MAX
};

void TaperNom(bool key[KEY_MAX], int* nom, ALLEGRO_FONT *texte, ALLEGRO_EVENT_QUEUE *queue,
              Personnage *p, Personnage *p2);

int Menu(ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP* clavier, ALLEGRO_FONT *texte, ALLEGRO_EVENT_QUEUE *queue, bool key[KEY_MAX],
         ALLEGRO_BITMAP *ticket, Personnage *p, ALLEGRO_BITMAP *imageperso, Personnage *p2,
         ALLEGRO_BITMAP *imageperso2, int menu, int entrerticket, int *nom);

void lire_sauvegarde(Personnage *p1, Personnage *p2, int *menu, int *entrerticket, ALLEGRO_FONT *texte1);

void ecrire_sauvegarde(Personnage *p1, Personnage *p2, int menu, int entrerticket, ALLEGRO_FONT *texte1);

void Sauvegardes(Personnage *p1, Personnage *p2, float *x, ALLEGRO_EVENT event, ALLEGRO_FONT *texte1,
                 ALLEGRO_EVENT_QUEUE *queue, bool key[KEY_MAX], ALLEGRO_BITMAP *fond, int menu, int entrerticket);

void Avancerpersbas(ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *imageperso1,ALLEGRO_BITMAP *imageperso2, ALLEGRO_COLOR couleur,
                    ALLEGRO_FONT *texte, ALLEGRO_BITMAP *ticket, Personnage* p1, Personnage* p2,
                    ALLEGRO_BITMAP *imagepersoimmo1,  ALLEGRO_BITMAP *imagepersoimmo2);

void Avancerpersohaut(ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *imageperso1,ALLEGRO_BITMAP *imageperso2, ALLEGRO_COLOR couleur,
                     ALLEGRO_FONT *texte, ALLEGRO_BITMAP *ticket, Personnage* p1, Personnage* p2,
                      ALLEGRO_BITMAP *imagepersoimmo1,  ALLEGRO_BITMAP *imagepersoimmo2);

void Avancerpersodroite(ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *imageperso1,ALLEGRO_BITMAP *imageperso2, ALLEGRO_COLOR couleur,
                        ALLEGRO_FONT *texte, ALLEGRO_BITMAP *ticket, Personnage* p1, Personnage* p2, bool key[KEY_MAX],
                        ALLEGRO_BITMAP *imagepersoimmo1,  ALLEGRO_BITMAP *imagepersoimmo2);

void Avancerpersogauche(ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *imageperso1,ALLEGRO_BITMAP *imageperso2, ALLEGRO_COLOR couleur,
                        ALLEGRO_FONT *texte, ALLEGRO_BITMAP *ticket, Personnage* p1, Personnage* p2,
                        ALLEGRO_BITMAP *imagepersoimmo1,  ALLEGRO_BITMAP *imagepersoimmo2);

void Attractions(ALLEGRO_BITMAP *fond, ALLEGRO_COLOR couleur, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *ticket,
                 Personnage p1, Personnage p2);

int Entrertickets(int i, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *imageperso, Personnage *p1,
                  ALLEGRO_BITMAP *ticket, Personnage*p2);

#endif //PROJET2MANEGE_MANEGE_H
