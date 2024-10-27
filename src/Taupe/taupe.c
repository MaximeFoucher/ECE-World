#include "taupe.h"

void Taupe_la (ALLEGRO_EVENT_QUEUE *queue, bool key[KEY_MAX], ALLEGRO_BITMAP *fond, Personnage *p1,
            ALLEGRO_BITMAP *ticket, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *imageperso,Personnage *p2) {
    int fin = 0;
    /*
    if (p1->tickets == 0) {
        fin = 1;
        al_draw_textf(texte, al_map_rgb(250, 250, 250), 100, 650, 0, "je devrais aller chercher des tickets avant");
        al_flip_display();
    }
     */
    double temps_precedent1 = al_get_time();
    double temps_precedent2 = al_get_time();


    p1->touractif = true;
    p2->touractif = false;
    if (key[ESCAPE]) {
        if (p1->touractif == true) {
            p1->touractif = false;
            p2->touractif = true;
        } else {
            p1->touractif = true;
            p2->touractif = false;
        }
    }
/////////1- DECLARATIONS des STRUCTURES////////////
    ALLEGRO_BITMAP *roche = NULL;
    ALLEGRO_BITMAP *taupe = NULL;
    ALLEGRO_BITMAP *marteau = NULL;
    ALLEGRO_BITMAP *canyon = NULL;
    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_TIMER *timer_taupe = NULL;
    ALLEGRO_EVENT event;
    TAUPE tabtaupe[NbTaupe];
    TAUPE *taupetouche = NULL;
    int compteurtaupe1 = 0;
    int compteurtaupe2 = 0;
    int xsouris, ysouris;
    int clic = 0;
    int compteurtimer = 0;
    int compteurvalide1 = 0;
    int compteurvalide2 = 0;
    int secondes1 = 30;
    int secondes2 = 30;

    if (fin == 0) {
        timer_taupe = al_create_timer(1.8);
        al_register_event_source(queue, al_get_timer_event_source(timer_taupe));
        taupe = al_load_bitmap("..\\image\\taupe.png");
        roche = al_load_bitmap("..\\image\\roche.jpg");
        canyon = al_load_bitmap("..\\image\\canyon.jpg");
        marteau = al_load_bitmap("..\\image\\marteau1.png");
        al_draw_scaled_bitmap(roche, 0, 0, 626, 626, 0, 0, LARGEUR, HAUTEUR, 0);

        for (int i = 0; i < NbTaupe; i++) {
            tabtaupe[i].x = rand() % LARGEUR;
            /////mettre les x à -10
            tabtaupe[i].y = rand() % HAUTEUR;
            tabtaupe[i].rayon = 40;
            tabtaupe[i].actif = true;
            al_draw_scaled_bitmap(taupe, 0, 0, 475, 475, tabtaupe[i].x, tabtaupe[i].y, 110, 110, 0);
        }

        al_flip_display();
        p1->tickets -= 1;
        al_start_timer(timer_taupe);

        al_draw_scaled_bitmap(canyon, 0, 0, 1280, 720, 0, 0, LARGEUR, HAUTEUR, 0);
        al_draw_filled_rectangle(300, 200, 800, 300, al_map_rgb(250, 250, 250));
        al_draw_text(texte, al_map_rgb(252, 30, 0), 350, 230, 0, "C'EST AU TOUR DU JOUEUR 1!");
        al_flip_display();
        al_rest(3);

        while ((compteurtaupe1 < 40 && secondes1 > 0) && fin == 0) {
            p1->touractif = true;
            p2->touractif = false;

            double nouveau_temps1 = al_get_time();
            if (nouveau_temps1 - temps_precedent1 >= 1.0) {///verifier si une seconde s'est passée
                secondes1 = secondes1 - 1;

                temps_precedent1 = nouveau_temps1;
            }
            al_wait_for_event(queue, &event);
            al_get_mouse_state(&mouse_state);
            al_draw_scaled_bitmap(roche, 0, 0, 626, 626, 0, 0, LARGEUR, HAUTEUR, 0);
            for (int i = 0; i < NbTaupe; i++) {
                if (tabtaupe[i].actif == true) {
                    al_draw_scaled_bitmap(taupe, 0, 0, 475, 475, tabtaupe[i].x, tabtaupe[i].y, 110, 110, 0);
                }
            }
            al_draw_textf(texte, al_map_rgb(58, 158, 35), 0, 50, 0, "SCORE: %d", compteurtaupe1);
            al_draw_textf(texte, al_map_rgb(250, 30, 0), 600, 70, 0, "TIMER: %02d", secondes1);
            al_draw_scaled_bitmap(marteau, 0, 0, 512, 512, xsouris - 50, ysouris, 90, 90, 0);
            al_flip_display();

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                fin = 1;
                Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *p1, *p2);
                al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 620, 300, 34, 48, 0);
                al_flip_display();
            } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        key[ESCAPE] = true;
                        break;
                    }
                }
            } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        key[ESCAPE] = false;
                        break;
                }


            } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
                xsouris = event.mouse.x;
                ysouris = event.mouse.y;
            } else if (event.type == ALLEGRO_EVENT_TIMER) {
                if (event.timer.source == timer_taupe) {
                    for (int i = 0; i < NbTaupe; i++) {
                        tabtaupe[i].x = 70 + rand() % (LARGEUR - 170);
                        /////mettre les x à -10
                        tabtaupe[i].y = 60 + rand() % (HAUTEUR - 150);
                        tabtaupe[i].rayon = 40;
                        tabtaupe[i].actif = true;
                        al_draw_scaled_bitmap(taupe, 0, 0, 475, 475, tabtaupe[i].x, tabtaupe[i].y, 110, 110, 0);
                    }
                }
            } else if (key[ESCAPE] == true) {
                fin = 1;
                Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *p1, *p2);
                al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 620, 300, 34, 48, 0);
                al_flip_display();
            } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.mouse.button == 1) {
                    for (int i = 0; i < NbTaupe; i++) {
                        float distance = sqrt(pow(event.mouse.x - tabtaupe[i].x - 45, 2) +
                                              pow(event.mouse.y - tabtaupe[i].y - 45,
                                                  2));
                        //float distance = sqrt(pow(event.mouse.x - circles[i].x, 2) + pow(event.mouse.y - circles[i].y, 2));//pow calcul baseexposant
                        if (distance < tabtaupe[i].rayon) {
                            if (tabtaupe[i].actif = true) {
                                tabtaupe[i].x = 0;
                                tabtaupe[i].y = 0;
                                tabtaupe[i].actif = false;
                                compteurtaupe1 += 1;
                            }

                        }

                    }
                }
            }
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                if (event.mouse.button == 1) {
                    taupetouche = NULL;
                }
            }
        }
        //--//////////////////////////
        al_flip_display();

        al_draw_scaled_bitmap(canyon, 0, 0, 1280, 720, 0, 0, LARGEUR, HAUTEUR, 0);
        al_draw_filled_rectangle(300, 200, 1060, 300, al_map_rgb(250, 250, 250));
        al_draw_text(texte, al_map_rgb(252, 30, 0), 350, 200, 0, "C'EST AU TOUR DU JOUEUR 2!\n""préparez-vous!");
        al_flip_display();
        al_rest(3);
        for (int i = 0; i < NbTaupe; i++) {
            tabtaupe[i].actif = true;
        }

        while ((compteurtaupe2 < 40 && secondes2 > 0) && fin == 0) {////fin commit/////
            time(0);
            p1->touractif = false;
            p2->touractif = true;

            double nouveau_temps2 = al_get_time() + secondes1;
            if (nouveau_temps2 - temps_precedent2 >= 1.0) {///verifier si une seconde s'est passée
                secondes2 = secondes2 - 1;

                ///

                temps_precedent2 = nouveau_temps2;
            }
            al_wait_for_event(queue, &event);
            al_get_mouse_state(&mouse_state);
            al_draw_scaled_bitmap(roche, 0, 0, 626, 626, 0, 0, LARGEUR, HAUTEUR, 0);
            for (int i = 0; i < NbTaupe; i++) {
                if (tabtaupe[i].actif == true) {
                    al_draw_scaled_bitmap(taupe, 0, 0, 475, 475, tabtaupe[i].x, tabtaupe[i].y, 110, 110, 0);
                }
            }
            al_draw_textf(texte, al_map_rgb(58, 158, 35), 0, 50, 0, "SCORE: %d", compteurtaupe2);
            al_draw_textf(texte, al_map_rgb(250, 30, 0), 600, 70, 0, "TIMER: %02d", secondes2);
            al_draw_scaled_bitmap(marteau, 0, 0, 512, 512, xsouris - 50, ysouris, 90, 90, 0);
            al_flip_display();

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                fin = 1;
                Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *p1, *p2);
                al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 620, 300, 34, 48, 0);
                al_flip_display();
                ////retourner 1 pour que ca marque la fin dans le main
            } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        key[ESCAPE] = true;
                        break;
                    }
                }
            } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        key[ESCAPE] = false;
                        break;
                }
            } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
                xsouris = event.mouse.x;
                ysouris = event.mouse.y;
            } else if (event.type == ALLEGRO_EVENT_TIMER) {
                if (event.timer.source == timer_taupe) {
                    for (int i = 0; i < NbTaupe; i++) {
                        tabtaupe[i].x = 70 + rand() % (LARGEUR - 170);
                        /////mettre les x à -10
                        tabtaupe[i].y = 60 + rand() % (HAUTEUR - 150);
                        tabtaupe[i].rayon = 40;
                        tabtaupe[i].actif = true;
                        al_draw_scaled_bitmap(taupe, 0, 0, 475, 475, tabtaupe[i].x, tabtaupe[i].y, 110, 110, 0);
                    }

                }
                if (key[ESCAPE] == true) {
                    fin = 1;
                    Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *p1, *p2);
                    al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 620, 300, 34, 48, 0);
                    al_flip_display();
                }
            }
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.mouse.button == 1) {
                    for (int i = 0; i < NbTaupe; i++) {
                        float distance = sqrt(pow(event.mouse.x - tabtaupe[i].x - 45, 2) +
                                              pow(event.mouse.y - tabtaupe[i].y - 45,
                                                  2));
                        //float distance = sqrt(pow(event.mouse.x - circles[i].x, 2) + pow(event.mouse.y - circles[i].y, 2));//pow calcul baseexposant
                        if (distance < tabtaupe[i].rayon) {

                            if (tabtaupe[i].actif = true) {
                                tabtaupe[i].x = 0;
                                tabtaupe[i].y = 0;
                                tabtaupe[i].actif = false;
                                compteurtaupe2 += 1;
                            }
                        }

                    }
                }
            }

            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                if (event.mouse.button == 1) {
                    taupetouche = NULL;
                }
            }
            //--//////////////////////////
            al_flip_display();

        }
        al_draw_scaled_bitmap(canyon, 0, 0, 1280, 720, 0, 0, LARGEUR, HAUTEUR, 0);
        al_draw_filled_rectangle(15, 550, 450, 650, al_map_rgb(250, 250, 250));
        al_draw_filled_rectangle(15, 150, 450, 250, al_map_rgb(250, 250, 250));
        if (compteurtaupe1 < compteurtaupe2) {
            al_draw_text(texte, al_map_rgb(0, 0, 0), 25, 600, 0, "Joueur 2 gagne +1 ticket");
            p2->tickets += 1;
            p2->score += 1;
        }   else {
            al_draw_text(texte, al_map_rgb(0, 0, 0), 25, 600, 0, "Joueur 2 perd");
            p2->tickets = p2->tickets - 1;

        }


        if (compteurtaupe2 < compteurtaupe1) {
            al_draw_text(texte, al_map_rgb(0, 0, 0), 25, 200, 0, "Joueur 1 gagne +1 ticket");
            p1->tickets += 1;
            p1->score += 1;
        } else {
            al_draw_text(texte, al_map_rgb(0, 0, 0), 25, 200, 0, "Joueur 1 perd");
            p1->tickets -= 1;
        }

    al_flip_display();
    fin = 1;
}





    al_destroy_bitmap(taupe);
    al_destroy_bitmap(roche);
    al_destroy_bitmap(canyon);
    al_destroy_bitmap(marteau);
    al_destroy_timer(timer_taupe);
    p1->x = 620;
    p1->y = 315;
    p2->x = 630;
    p2->y = 315;
}








