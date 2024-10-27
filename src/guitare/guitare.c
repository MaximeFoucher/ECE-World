//
// Created by augus on 27/04/2023.
//

#include "guitare.h"

void GuitareHeroJoueur1(bool key[KEY_MAX], ALLEGRO_DISPLAY *display, ALLEGRO_EVENT event, ALLEGRO_BITMAP *fond, Personnage *p1,
                        ALLEGRO_BITMAP *ticket, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *imageperso,Personnage *p2) {

////////////////////////////////////////////////////INITIALISATION//////////////////////////////////////////////////////////////////////////

    int fin = 0, pause = 0, dessin = 0, waitInMilliseconds = -1, i = 0, score = 0, r = 15;

    al_init_acodec_addon();
    assert(al_install_keyboard());
    assert(al_install_audio());

    Note notes[NB_MAX_NOTES];
    Note notes2[NB_MAX_NOTES2];
    Note notes3[NB_MAX_NOTES3];
    Note notes4[NB_MAX_NOTES4];
    ALLEGRO_TIMER *timer_guitare = NULL;
    ALLEGRO_EVENT_QUEUE *queue1 = NULL;
    ALLEGRO_KEYBOARD_STATE keybord_state;



    ALLEGRO_BITMAP *hautParleur1 = al_load_bitmap("..\\image\\haut1.png");
    ALLEGRO_BITMAP *hautParleur = al_load_bitmap("..\\image\\haut.png");
    ALLEGRO_SAMPLE *musique = NULL;
     musique = al_load_sample("..\\audio\\40fingers.ogg");
    ALLEGRO_FONT *fontBangers60 = al_load_ttf_font("..\\fonts\\bangers-Regular.ttf", 50, 0);

     al_reserve_samples(16);
    al_set_target_backbuffer(display);

    ///////////////////////////////////////////////////INITIALISATION NOTES///////////////////////////////////////////////////////////////

    for (i = 0; i < NB_MAX_NOTES; i++) {
         notes[i].vitesse = 4;
        notes[i].actif = 0;
        notes[i].width1 = 20;
        notes[i].height1 = 20;
        notes[i].x = 485;
        notes[i].y = 0;
    }
    for (i = 0; i < NB_MAX_NOTES2; i++) {
         notes2[i].vitesse = 4;
        notes2[i].actif = 0;
        notes2[i].width1 = 20;
        notes2[i].height1 = 20;
        notes2[i].x = 585;
        notes2[i].y = 0;
    }
    for (i = 0; i < NB_MAX_NOTES3; i++) {
         notes3[i].vitesse = 4;
        notes3[i].actif = 0;
        notes3[i].width1 = 20;
        notes3[i].height1 = 20;
        notes3[i].x = 685;
        notes3[i].y = 0;
    }
    for (i = 0; i < NB_MAX_NOTES4; i++) {
         notes4[i].vitesse = 4;
        notes4[i].actif = 0;
        notes4[i].width1 = 20;
        notes4[i].height1 = 20;
        notes4[i].x = 785;
        notes4[i].y = 0;
    }



///////////////////////////////////////////TOUCHES////////////////////////////////////////////////////
    al_play_sample(musique, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);


    queue1 = al_create_event_queue();
    timer_guitare = al_create_timer(1.0 / 100);
    al_register_event_source(queue1, al_get_timer_event_source(timer_guitare));
    al_register_event_source(queue1, al_get_keyboard_event_source());
    al_start_timer(timer_guitare);
    do{
        al_wait_for_event(queue1, &event);
        al_get_keyboard_event_source();
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            fin = 1;
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN && !pause && waitInMilliseconds == -1) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_A:
                    key[A] = 1;
                    break;
                case ALLEGRO_KEY_E:
                    key[E] = 1;
                    break;
                case ALLEGRO_KEY_T: // Q
                    key[T] = 1;
                    break;
                case ALLEGRO_KEY_U:
                    key[U] = 1;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    key[ESCAPE] = 1;
                    break;
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_UP && waitInMilliseconds == -1) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_A:
                    key[A] = 0;
                    break;
                case ALLEGRO_KEY_E:
                    key[E] = 0;
                    break;
                case ALLEGRO_KEY_T: // Q
                    key[T] = 0;
                    break;
                case ALLEGRO_KEY_U:
                    key[U] = 0;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    key[ESCAPE] = 0;
                    break;
                case ALLEGRO_KEY_P:
                    key[A] = 0;
                    key[E] = 0;
                    key[T] = 0;
                    key[U] = 0;
                    pause = !pause;
                    dessin = 1;
                    break;
            }
        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            if (!pause) {
                if(key[ESCAPE]){
                    fin = 1;
                    Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *p1, *p2);
                    al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 620, 300, 34, 48, 0);
                    al_flip_display();
                }

///////////////////////////////////////////////////////VALIDATION NOTES/////////////////////////////////////////////////////


                for (i = 0; i < NB_MAX_NOTES; i++) {
                    if (notes[i].actif == 1 && notes[i].y > 616 && notes[i].y < 646) {
                        if (key[A]) {
                            notes[i].actif = 0;
                            score += 1;
                        }
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                    }
                }
                for (i = 0; i < NB_MAX_NOTES2; i++) {
                    if (notes2[i].actif == 1 && notes2[i].y > 616 && notes2[i].y < 646) {
                        if (key[E]) {
                            notes2[i].actif = 0;
                            score += 1;
                        }
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                    }
                }

                for (i = 0; i < NB_MAX_NOTES3; i++) {
                    if (notes3[i].actif == 1 && notes3[i].y > 616 && notes3[i].y < 646) {
                        if (key[E]) {
                            notes3[i].actif = 0;
                            score += 1;
                        }
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                    }
                }
                for (i = 0; i < NB_MAX_NOTES4; i++) {
                    if (notes4[i].actif == 1 && notes4[i].y > 616 && notes4[i].y < 646) {
                        if (key[U]) {
                            notes4[i].actif = 0;
                            score += 1;
                        }
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                    }
                }

                for (i = 0; i < NB_MAX_NOTES; i++) {
                    if (notes[i].actif == 1 && notes[i].y > 646) {
                        notes[i].actif = 0;
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                    }
                }for (i = 0; i < NB_MAX_NOTES2; i++) {
                    if (notes2[i].actif == 1 && notes2[i].y > 646) {
                        notes2[i].actif = 0;
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                    }
                }for (i = 0; i < NB_MAX_NOTES3; i++) {
                    if (notes3[i].actif == 1 && notes3[i].y > 646) {
                        notes3[i].actif = 0;
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                    }
                }for (i = 0; i < NB_MAX_NOTES4; i++) {
                    if (notes4[i].actif == 1 && notes4[i].y > 646) {
                        notes4[i].actif = 0;
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                    }
                }



///////////////////////////////////////////////////APPARITION NOTES///////////////////////////////////////////////////////////////:



                for (i = 0; i < NB_MAX_NOTES; i++) {
                    if (!notes[i].actif && rand() % 7000 < 10) {
                        notes[i].x = notes[i].x;
                        notes[i].y = notes[i].y + notes[i].vitesse;
                        notes[i].actif = 1;
                    }
                }
                for (i = 0; i < NB_MAX_NOTES2; i++) {
                    if (!notes2[i].actif && rand() % 7000 < 10) {
                        notes2[i].x = notes2[i].x;
                        notes2[i].y = notes2[i].y + notes2[i].vitesse;
                        notes2[i].actif = 1;
                    }
                }
                for (i = 0; i < NB_MAX_NOTES3; i++) {
                    if (!notes3[i].actif && rand() % 7000 < 10) {
                        notes3[i].x = notes3[i].x;
                        notes3[i].y = notes3[i].y + notes3[i].vitesse;
                        notes3[i].actif = 1;
                    }
                }
                for (i = 0; i < NB_MAX_NOTES4; i++) {
                    if (!notes4[i].actif && rand() % 7000 < 10) {
                        notes4[i].x = notes4[i].x;
                        notes4[i].y = notes4[i].y + notes4[i].vitesse;
                        notes4[i].actif = 1;
                    }
                }


//////////////////////////////////////////////DEPLACEMENT NOTES//////////////////////////////////////////////////////////////////


                for (i = 0; i < NB_MAX_NOTES; i++) {
                    if (notes[i].actif) {
                        notes[i].y += notes[i].vitesse;
                        if (notes[i].y - notes[i].width1 < 0) {
                            notes[i].actif = 0;
                        }
                    }
                }
                for (i = 0; i < NB_MAX_NOTES2; i++) {
                    if (notes2[i].actif) {
                        notes2[i].y += notes2[i].vitesse;
                        if (notes2[i].y - notes2[i].width1 < 0) {
                            notes2[i].actif = 0;
                        }
                    }
                }
                for (i = 0; i < NB_MAX_NOTES3; i++) {
                    if (notes3[i].actif) {
                        notes3[i].y += notes3[i].vitesse;
                        if (notes3[i].y - notes3[i].width1 < 0) {
                            notes3[i].actif = 0;
                        }
                    }
                }
                for (i = 0; i < NB_MAX_NOTES4; i++) {
                    if (notes4[i].actif) {
                        notes4[i].y += notes4[i].vitesse;
                        if (notes4[i].y - notes4[i].width1 < 0) {
                            notes4[i].actif = 0;
                        }
                    }
                }


                dessin = 1;
            }


            if (dessin) {
                al_draw_filled_rectangle(0, 0, LARGEUR, HAUTEUR, al_map_rgb(0, 0, 0));
                al_draw_filled_rectangle(440, 0, 840, 816, al_map_rgb(120, 66, 18));
                al_draw_filled_rectangle(440, 616, 840, 646, al_map_rgb(255, 255, 255));
                al_draw_filled_rectangle(440, 0, 840, 10, al_map_rgb(66, 73, 73));
                al_draw_filled_rectangle(440, 100, 840, 110, al_map_rgb(66, 73, 73));
                al_draw_filled_rectangle(440, 300, 840, 310, al_map_rgb(66, 73, 73));
                al_draw_filled_rectangle(440, 500, 840, 510, al_map_rgb(66, 73, 73));
                al_draw_filled_rectangle(440, 700, 840, 710, al_map_rgb(66, 73, 73));
                al_draw_filled_rectangle(480, 0, 490, 816, al_map_rgb(81, 90, 90));
                al_draw_filled_rectangle(580, 0, 590, 816, al_map_rgb(81, 90, 90));
                al_draw_filled_rectangle(680, 0, 690, 816, al_map_rgb(81, 90, 90));
                al_draw_filled_rectangle(780, 0, 790, 816, al_map_rgb(81, 90, 90));

///////////////////////////////////////////////////////NOTES FORMES///////////////////////////////////////////////////////:

                for (i = 0; i < NB_MAX_NOTES; i++) {
                    if (notes[i].actif) {
                        al_draw_filled_circle(notes[i].x, notes[i].y, r, al_map_rgb(255, 255, 255));
                    }
                }
                for (i = 0; i < NB_MAX_NOTES2; i++) {
                    if (notes2[i].actif) {
                        al_draw_filled_circle(notes2[i].x, notes2[i].y, r,
                                              al_map_rgb(255, 255, 255));
                    }
                }
                for (i = 0; i < NB_MAX_NOTES3; i++) {
                    if (notes3[i].actif) {
                        al_draw_filled_circle(notes3[i].x, notes3[i].y, r,
                                              al_map_rgb(255, 255, 255));
                    }
                }
                for (i = 0; i < NB_MAX_NOTES4; i++) {
                    if (notes4[i].actif) {
                        al_draw_filled_circle(notes4[i].x, notes4[i].y, r,
                                              al_map_rgb(255, 255, 255));
                    }
                }


                al_draw_textf(fontBangers60, al_map_rgb(52, 152, 219), 30, 600, 0, "Valide ici ----->");
                //al_draw_textf(fontBangers60, al_map_rgb(52, 152, 219), 10, 46, 0, "ECHAP = Quitter");
                al_draw_scaled_bitmap(hautParleur, 0, 0, 225, 225, 10, 100, 400, 400, 0);
                al_draw_scaled_bitmap(hautParleur1, 0, 0, 225, 225, 850, 100, 400, 400, 0);
                al_draw_filled_rectangle(440, 646, 840, 816, al_map_rgb(120, 66, 18));
                al_draw_filled_circle(490, 696, 40, al_map_rgb(183, 149, 11));
                al_draw_textf(fontBangers60, al_map_rgb(0, 0, 0), 475, 666, 0, "A");
                al_draw_filled_circle(590, 696, 40, al_map_rgb(183, 149, 11));
                al_draw_textf(fontBangers60, al_map_rgb(0, 0, 0), 575, 666, 0, "E");
                al_draw_filled_circle(690, 696, 40, al_map_rgb(183, 149, 11));
                al_draw_textf(fontBangers60, al_map_rgb(0, 0, 0), 675, 666, 0, "T");
                al_draw_filled_circle(790, 696, 40, al_map_rgb(183, 149, 11));
                al_draw_textf(fontBangers60, al_map_rgb(0, 0, 0), 775, 666, 0, "U");
                al_draw_textf(fontBangers60, al_map_rgb(255, 255, 0), 565, 10, 0, "Score : %d", score);
                al_flip_display();



                dessin = 0;
            }
        }
    }while(!fin);
    al_destroy_sample(musique);
    //al_destroy_sample_instance(songinstance);

}