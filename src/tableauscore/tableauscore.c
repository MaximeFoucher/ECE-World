#include "tableauscore.h"

int Afficherscore(ALLEGRO_EVENT_QUEUE *queue, bool key[KEY_MAX], ALLEGRO_BITMAP *fondmap, Personnage *p1,
                   ALLEGRO_BITMAP *ticket, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *imageperso1, Personnage *p2, ALLEGRO_BITMAP *imageperso2){

    ALLEGRO_BITMAP *tableau = NULL;
    ALLEGRO_BITMAP *fond = NULL;
    ALLEGRO_EVENT event;

    tableau= al_load_bitmap("..\\image\\tableauscore.png");
    fond = al_load_bitmap("..\\image\\fondscore.jpg");


    while (true) {
        al_wait_for_event(queue, &event);

        al_draw_scaled_bitmap(fond, 0, 0, 620, 349, 0, 0, LARGEUR, HAUTEUR, 0);
        al_draw_scaled_bitmap(tableau, 0, 0, 612, 408, 150, 150, 918, 612, 0);

        al_draw_textf(texte, al_map_rgb(250, 250, 250), 230, 450, 0, "score:   %d", p1->score);
        al_draw_textf(texte, al_map_rgb(250, 250, 250), 230, 510, 0, "tickets: %d", p1->tickets);
        al_draw_textf(texte, al_map_rgb(250, 250, 250), 800, 450, 0, "score:    %d", p2->score);
        al_draw_textf(texte, al_map_rgb(250, 250, 250), 800, 510, 0, "tickets:  %d", p2->tickets);
        al_draw_textf(texte, al_map_rgb(250, 250, 250), 540, 450, 0, "TABLEAU");
        al_draw_textf(texte, al_map_rgb(250, 250, 250), 515, 500, 0, "DES SCORES");

        ////mettre nom
        al_draw_textf(texte, al_map_rgb(250, 250, 250), 260, 350, 0, "Joueur 1");
        al_draw_textf(texte, al_map_rgb(250, 250, 250), 780, 350, 0, "Joueur 2");

        al_flip_display();

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            //fin = 1;
            Attractions(fondmap, al_map_rgb(250, 250, 250), texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso1, 0, 0, 67, 95, p1->x, p1->y, 34, 48, 0);
            al_draw_scaled_bitmap(imageperso2, 0, 0, 127,147, p2->x, p2->y, 50, 58, 0);

            ////mettre deuxieme perso
            al_flip_display();
            key[ESCAPE]=false;
            al_destroy_bitmap(tableau);
            al_destroy_bitmap(fond);
            return 1;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE: {
                    key[ESCAPE] = true;
                    break;
                }
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    key[ESCAPE] = false;
                    break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {
            if (key[ESCAPE] == true) {
                //fin = 1;
                Attractions(fondmap, al_map_rgb(250, 250, 250), texte, ticket, *p1, *p2);
                al_draw_scaled_bitmap(imageperso1, 0, 0, 67, 95, p1->x, p1->y, 34, 48, 0);
                al_draw_scaled_bitmap(imageperso2, 0, 0, 127,147, p2->x, p2->y, 50, 58, 0);

                al_flip_display();
                key[ESCAPE]=false;
                al_destroy_bitmap(tableau);
                al_destroy_bitmap(fond);
                return 0;
            }
        }
    }
}