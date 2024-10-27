#include "snake.h"
#define BLOCK_SIZE 16

void snake(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *display,ALLEGRO_FONT *police,Personnage *p1,Personnage *p2){
    ALLEGRO_KEYBOARD_STATE key_state;
    ALLEGRO_EVENT event;

    ALLEGRO_COLOR snake_color = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR food_color = al_map_rgb(255, 0, 0);
    bool game_over = false;
    float snake_x = LARGEUR / 2;
    float snake_y = HAUTEUR / 2;
    float snake_vitesse = 4;
    float snake_taille = 10;
    double temps_precedent1=al_get_time();
    double temps_precedent2=al_get_time();
    int secondes1 = 30;
    int secondes2=30;
    int fon=0;
    float nourriture_x, nourriture_y;
    srand(time(NULL));
    nourriture_x = rand() % LARGEUR;
    nourriture_y = rand() % HAUTEUR;
    if(fon==0) {

        while (secondes1 > 0) {
            double nouveau_temps1 = al_get_time();
            if (nouveau_temps1 - temps_precedent1 >= 1.0) {///verifier si une seconde s'est passée
                secondes1 = secondes1 - 1;
                temps_precedent1 = nouveau_temps1;
            }

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                secondes1 = -1;
                ///rafficher le fond de map
            } else if (event.type == ALLEGRO_EVENT_TIMER) {
                al_get_keyboard_state(&key_state);
                if (al_key_down(&key_state, ALLEGRO_KEY_UP)) {
                    snake_y -= snake_vitesse;
                }
                if (al_key_down(&key_state, ALLEGRO_KEY_DOWN)) {
                    snake_y += snake_vitesse;
                }
                if (al_key_down(&key_state, ALLEGRO_KEY_LEFT)) {
                    snake_x -= snake_vitesse;
                }
                if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT)) {
                    snake_x += snake_vitesse;
                }

                if (snake_x < 0 || snake_x > LARGEUR || snake_y < 0 || snake_y > HAUTEUR) {
                    game_over = true;
                }
                if (snake_x > nourriture_x - snake_taille && snake_x < nourriture_x + snake_taille &&
                    snake_y > nourriture_y - snake_taille && snake_y < nourriture_y + snake_taille) {
                    // positionnement aléatoire de la nourriture
                    nourriture_x = rand() % LARGEUR;
                    nourriture_y = rand() % HAUTEUR;
                }
                // dessin de la nourriture
               // al_draw_filled_rectangle(nourriture_x - snake_taille, nourriture_y - snake_taille,
                                       //  nourriture_x + snake_taille, nourriture_y + snake_taille, food_color);

                // dessin du serpent
                al_draw_filled_rectangle(snake_x - snake_taille, snake_y - snake_taille, snake_x + snake_taille,
                                         snake_y + snake_taille, snake_color);
                al_flip_display();


            }


        }
    }







}