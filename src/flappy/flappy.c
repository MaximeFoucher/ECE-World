#include "flappy.h"

void flappy_bird(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT *texte, ALLEGRO_BITMAP* fond, ALLEGRO_BITMAP* imageperso, Personnage *perso, Personnage *perso2, ALLEGRO_BITMAP *ticket) {
    ALLEGRO_BITMAP* fond_flappy = NULL;
    ALLEGRO_BITMAP* flappy = NULL;
    ALLEGRO_BITMAP* tuyaux_haut = NULL;
    ALLEGRO_BITMAP* tuyaux_bas = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_COLOR transparent_color = al_map_rgba_f(0, 0, 0, 0);

    int compteur_1=0;
    int compteur_2=0;
    int fini = 0;
    int i = 0;
    int position = 300;
    int position_tuyaux = 1280;
    float vitesse_tuyaux = 3.0;
    ///Hauteur aléatoire des tuyaux
    int dh = rand()%596 + 20;
    int db = dh + 200;

    ///Création des hitbox pour les collisions
    flappy_rectangle flappy_hitbox = {20, position+40, 160, position+100};

    fond_flappy = al_load_bitmap("..\\image\\fond_flappy.jpg");
    flappy = al_load_bitmap("..\\image\\flappy_bird_pokemonV2.png");
    tuyaux_haut = al_load_bitmap("..\\image\\tuyaux_haut.png");
    tuyaux_bas = al_load_bitmap("..\\image\\tuyaux_bas.png");

    bool once = true;
    ///Verifier le tour actif
    bool verif_tour_actif1 = perso->touractif;

    ///Pour commencer par le joueur 1
    perso->touractif = true;
    perso2->touractif = false;

    while(fini == 0) {
        al_wait_for_event(queue, &event);
        al_get_keyboard_event_source();
        if (event.keyboard.keycode == ALLEGRO_KEY_E) {
            fini = 1;
            Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *perso2);
            al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 710, 350, 34, 48, 0);
            al_flip_display();
        }
        else if (perso->touractif == true && event.type == ALLEGRO_EVENT_TIMER) {
            Rectangle_tuyaux rectangle_haut = {position_tuyaux, 0, position_tuyaux+100, dh};
            Rectangle_tuyaux rectangle_bas = {position_tuyaux, db, position_tuyaux+100, 816};
            al_clear_to_color(al_map_rgb(0, 250, 0));
            al_draw_scaled_bitmap(fond_flappy, 0, 0, 612, 306, 0, 0, LARGEUR, HAUTEUR, 0);

            al_draw_scaled_bitmap(flappy, 0, 0, 256, 256, 20, position, 150, 150, 0);
            al_draw_rectangle(flappy_hitbox.x1, flappy_hitbox.y1, flappy_hitbox.x2, flappy_hitbox.y2, transparent_color, 0);

            al_draw_scaled_bitmap(tuyaux_haut, 0, 0, 54, 186, position_tuyaux, 0, 100, dh, 0);
            al_draw_rectangle(rectangle_haut.x1, rectangle_haut.y1, rectangle_haut.x2, rectangle_haut.y2,transparent_color, 0);

            al_draw_scaled_bitmap(tuyaux_bas, 0, 0, 54, 190, position_tuyaux, db, 100, HAUTEUR-db, 0);
            al_draw_rectangle(rectangle_bas.x1, rectangle_bas.y1, rectangle_bas.x2, rectangle_bas.y2,transparent_color, 0);

            ///Affiche le score
            al_draw_textf(texte, al_map_rgb(255, 255, 255), 100, 50, 0, "score joueur 1 : %d", compteur_1);

            al_flip_display();
            rectangle_haut.x1 -= vitesse_tuyaux;
            rectangle_haut.x2 -= vitesse_tuyaux;
            rectangle_bas.x1 -= vitesse_tuyaux;
            rectangle_bas.x2 -= vitesse_tuyaux;
            position_tuyaux -= vitesse_tuyaux;
            flappy_hitbox.y1 += 0.1*i;
            flappy_hitbox.y2 += 0.1*i;
            position += 0.1 * i;
            i++;
            if(rectangle_haut.x2<0) {
                position_tuyaux = 1280;
                dh = rand()%596 + 20;
                db = dh + 200;
                vitesse_tuyaux = 0.5+vitesse_tuyaux;
                compteur_1++;
            }
            ///Collisions
            if((flappy_hitbox.y1 < 0) || (flappy_hitbox.y2 > HAUTEUR) ||
               (flappy_hitbox.x1+140 > rectangle_haut.x1 && flappy_hitbox.x1+140 < rectangle_haut.x2 && flappy_hitbox.y2-60 < rectangle_haut.y2) ||
               (flappy_hitbox.x2-30 > rectangle_bas.x1 && flappy_hitbox.x2+20 < rectangle_bas.x2 && flappy_hitbox.y2 > rectangle_bas.y1) ||
               (flappy_hitbox.y1+60 > rectangle_bas.y1 && flappy_hitbox.x1 > rectangle_bas.x1 && flappy_hitbox.x1 < rectangle_bas.x2) ||
               flappy_hitbox.y1 < rectangle_haut.y2   && flappy_hitbox.x1 > rectangle_haut.x1 && flappy_hitbox.x1 < rectangle_haut.x2) {
                perso->touractif = false;
                position_tuyaux = 1280;
                vitesse_tuyaux = 3.0;
                dh = rand()%596 + 20;
                db = dh + 200;
                position = 300;
                flappy_hitbox.y1 = position+40;
                flappy_hitbox.y2 = position+100;
                i=0;
                perso2->touractif = true;
            }

        }
        else if (perso2->touractif == true && event.type == ALLEGRO_EVENT_TIMER) {
            Rectangle_tuyaux rectangle_haut = {position_tuyaux, 0, position_tuyaux+100, dh};
            Rectangle_tuyaux rectangle_bas = {position_tuyaux, db, position_tuyaux+100, 816};
            al_clear_to_color(al_map_rgb(0, 250, 0));
            al_draw_scaled_bitmap(fond_flappy, 0, 0, 612, 306, 0, 0, LARGEUR, HAUTEUR, 0);

            al_draw_scaled_bitmap(flappy, 0, 0, 256, 256, 20, position, 150, 150, 0);
            al_draw_rectangle(flappy_hitbox.x1, flappy_hitbox.y1, flappy_hitbox.x2, flappy_hitbox.y2, transparent_color, 0);

            al_draw_scaled_bitmap(tuyaux_haut, 0, 0, 54, 186, position_tuyaux, 0, 100, dh, 0);
            al_draw_rectangle(rectangle_haut.x1, rectangle_haut.y1, rectangle_haut.x2, rectangle_haut.y2,transparent_color, 0);

            al_draw_scaled_bitmap(tuyaux_bas, 0, 0, 54, 190, position_tuyaux, db, 100, HAUTEUR-db, 0);
            al_draw_rectangle(rectangle_bas.x1, rectangle_bas.y1, rectangle_bas.x2, rectangle_bas.y2,transparent_color, 0);

            ///Affiche le score
            al_draw_textf(texte, al_map_rgb(255, 255, 255), 100, 50, 0, "score joueur 2 : %d", compteur_2);

            al_flip_display();
            rectangle_haut.x1 -= vitesse_tuyaux;
            rectangle_haut.x2 -= vitesse_tuyaux;
            rectangle_bas.x1 -= vitesse_tuyaux;
            rectangle_bas.x2 -= vitesse_tuyaux;
            position_tuyaux -= vitesse_tuyaux;
            flappy_hitbox.y1 += 0.1*i;
            flappy_hitbox.y2 += 0.1*i;
            position += 0.1 * i;
            i++;
            if(rectangle_haut.x2<0) {
                position_tuyaux = 1280;
                dh = rand()%596 + 20;
                db = dh + 200;
                vitesse_tuyaux = 0.5+vitesse_tuyaux;
                compteur_2++;
            }
            ///Collisions
            if((flappy_hitbox.y1 < 0) || (flappy_hitbox.y2 > HAUTEUR) ||
               (flappy_hitbox.x1+140 > rectangle_haut.x1 && flappy_hitbox.x1+140 < rectangle_haut.x2 && flappy_hitbox.y2-60 < rectangle_haut.y2) ||
               (flappy_hitbox.x2-30 > rectangle_bas.x1 && flappy_hitbox.x2+20 < rectangle_bas.x2 && flappy_hitbox.y2 > rectangle_bas.y1) ||
               (flappy_hitbox.y1+60 > rectangle_bas.y1 && flappy_hitbox.x1 > rectangle_bas.x1 && flappy_hitbox.x1 < rectangle_bas.x2) ||
               flappy_hitbox.y1 < rectangle_haut.y2   && flappy_hitbox.x1 > rectangle_haut.x1 && flappy_hitbox.x1 < rectangle_haut.x2) {
                perso->touractif = false;
                perso2->touractif = false;
            }

        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_SPACE && (perso->touractif==true || perso2->touractif==true)) {
            i = 0;
            for (int j = 0; j < 50; j++) {
                Rectangle_tuyaux rectangle_haut = {position_tuyaux, 0, position_tuyaux+100, dh};
                Rectangle_tuyaux rectangle_bas = {position_tuyaux, db, position_tuyaux+100, 816};
                al_clear_to_color(al_map_rgb(0, 250, 0));
                al_draw_scaled_bitmap(fond_flappy, 0, 0, 612, 306, 0, 0, LARGEUR, HAUTEUR, 0);

                al_draw_scaled_bitmap(flappy, 0, 0, 256, 256, 20, position, 150, 150, 0);
                al_draw_rectangle(flappy_hitbox.x1, flappy_hitbox.y1, flappy_hitbox.x2, flappy_hitbox.y2, transparent_color, 0);


                al_draw_scaled_bitmap(tuyaux_haut, 0, 0, 54, 186, position_tuyaux-j*0.15, 0, 100, dh, 0);
                al_draw_rectangle(rectangle_haut.x1, rectangle_haut.y1, rectangle_haut.x2, rectangle_haut.y2,transparent_color, 0);

                al_draw_scaled_bitmap(tuyaux_bas, 0, 0, 54, 190, position_tuyaux-j*0.15, db, 100, HAUTEUR - db, 0);
                al_draw_rectangle(rectangle_bas.x1, rectangle_bas.y1, rectangle_bas.x2, rectangle_bas.y2,transparent_color, 0);

                flappy_hitbox.y1 += -0.05*i;
                flappy_hitbox.y2 += -0.05*i;
                position += -0.05 * i;

                if(perso->touractif == true) {
                    al_draw_textf(texte, al_map_rgb(255, 255, 255), 100, 50, 0, "score joueur 1 : %d", compteur_1);
                }
                else if(perso2->touractif == true) {
                    al_draw_textf(texte, al_map_rgb(255, 255, 255), 100, 50, 0, "score joueur 2 : %d", compteur_2);
                }
                al_flip_display();
                i++;
            }
            i = 0;
        }
        else if(perso->touractif == false && perso2->touractif == false) {
            if(once) {
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_scaled_bitmap(fond_flappy, 0, 0, 612, 306, 0, 0, LARGEUR, HAUTEUR, 0);
                al_draw_textf(texte, al_map_rgb(0,0,0), 200, 200, 0,"Score : %d / %d", compteur_1, compteur_2);
                if(compteur_1 > compteur_2) {
                    al_draw_textf(texte, al_map_rgb(0,0,0), 200, 300, 0, "Joueur 1 gagne +1");
                    al_draw_textf(texte, al_map_rgb(0,0,0), 100, 700, 0, "E pour quitter");
                    perso->tickets += 1;
                    perso->score += 1;
                    perso2->tickets = perso2->tickets -1;
                    al_flip_display();
                    al_wait_for_event(queue, &event);
                    if (event.keyboard.keycode == ALLEGRO_KEY_E) {
                        fini = 1;
                        Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *perso2);
                        al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 710, 340, 34, 48, 0);
                        al_flip_display();
                    }
                }
                else if(compteur_2 > compteur_1) {
                    al_draw_textf(texte, al_map_rgb(0,0,0), 200, 300, 0, "Joueur 2 gagne +1");
                    al_draw_textf(texte, al_map_rgb(0,0,0), 100, 700, 0, "E pour quitter");
                    perso2->tickets += 1;
                    perso2->score += 1;
                    perso->tickets = perso2->tickets -1;
                    al_flip_display();
                    al_wait_for_event(queue, &event);
                    if (event.keyboard.keycode == ALLEGRO_KEY_E) {
                        fini = 1;
                        Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *perso2);
                        al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 710, 340, 34, 48, 0);
                        al_flip_display();
                    }
                }
                else if(compteur_1 == compteur_2) {
                    al_draw_textf(texte, al_map_rgb(0,0,0), 200, 300, 0, "Egalite");
                    al_draw_textf(texte, al_map_rgb(0,0,0), 100, 700, 0, "E pour quitter");
                    perso->tickets -= 1;
                    perso2->tickets -= 1;
                    al_flip_display();
                    al_wait_for_event(queue, &event);
                    if (event.keyboard.keycode == ALLEGRO_KEY_E) {
                        fini = 1;
                        Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *perso2);
                        al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 710, 340, 34, 48, 0);
                        al_flip_display();
                    }
                }
                once = false;
            }
        }
    }
    if(verif_tour_actif1 == true) {
        perso->touractif = false;
        perso2->touractif = true;
        perso->x = 710;
        perso->y = 340;
        perso2->x=720;
        perso2->y=340;
    }
    else {
        perso->touractif = true;
        perso2->touractif = false;
        perso->x = 710;
        perso->y = 340;
        perso2->x=720;
        perso2->y=340;
    }
    al_destroy_bitmap(fond_flappy);
    al_destroy_bitmap(flappy);
    al_destroy_bitmap(tuyaux_bas);
    al_destroy_bitmap(tuyaux_haut);

}
