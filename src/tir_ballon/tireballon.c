#include "tireballon.h"

void Tirballon(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_MOUSE_STATE mouse_state, ALLEGRO_DISPLAY *display,ALLEGRO_FONT *police,ALLEGRO_BITMAP *fond,ALLEGRO_BITMAP *ticket,ALLEGRO_BITMAP *imageperso, Personnage *p1,Personnage *p2,bool key[KEY_MAX]) {
    assert(al_install_keyboard());

    int fin = 0;
    double temps_precedent1=al_get_time();
    double temps_precedent2=al_get_time();


    /*
    if(p1->tickets==0){
        fin=1;
        al_draw_textf(police, al_map_rgb(250,250,250), 100, 650, 0, "je devrais aller chercher des tickets avant");
        al_flip_display();
    }
    if(p2->tickets==0){
        fin=1;

        al_draw_textf(police, al_map_rgb(250,250,250), 100, 650, 0, "je devrais aller chercher des tickets avant");
        al_flip_display();
    }
*/

    ALLEGRO_BITMAP *arriere_plan = NULL;
    ALLEGRO_BITMAP *standballon = NULL;
    ALLEGRO_BITMAP *pokeball=NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER* timer2=NULL;
    //audio
    ALLEGRO_SAMPLE *soncapture=NULL;
    soncapture= al_load_sample("..\\audio\\Pokeball_catch.ogg");

    ALLEGRO_SAMPLE_INSTANCE *songinstance=NULL;
    ALLEGRO_SAMPLE *finjeu=NULL;
    finjeu= al_load_sample("..\\audio\\fin_mini_jeu.ogg");
    al_reserve_samples(16);
    songinstance= al_create_sample_instance(soncapture);
    al_set_sample_instance_playmode(songinstance,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songinstance,al_get_default_mixer());

    ///
    timer2 = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer2));



    if (fin == 0) {
        ///pas un while donc rentre toujours dans le if (sert à rien)
        standballon = al_load_bitmap("..\\image\\stand tire ballon remove.png");
        arriere_plan = al_load_bitmap("..\\image\\arriere plan.png");
        pokeball= al_load_bitmap("..\\image\\Pokeball20.png");
        al_draw_scaled_bitmap(arriere_plan, 0, 0, 1280, 720, 0, 0, LARGEUR, HAUTEUR, 0);
        Cercle cercles[NUM_CERCLES];

        int i = 0;
        int compteurcercle1 = 0;
        int compteurcercle2 = 0;

        int secondes1 = 30;
        int secondes2=30;



        for ( i = 0; i < NUM_CERCLES; i++) {
            cercles[i].x = al_get_display_width(display) / 2;
            cercles[i].y = al_get_display_height(display) / 2;
            cercles[i].dx = rand() % 10 - 3;
            cercles[i].dy = rand() % 10 - 3;
            cercles[i].rayon = 10;
            cercles[i].couleur = al_map_rgb(rand() % 256, rand() % 256, rand() % 256);
            cercles[i].actif = true;
        }
        al_draw_scaled_bitmap(arriere_plan, 0, 0, 1280, 720, 0, 0, 1200, 800, 0);
        al_draw_filled_rectangle(300, 200, 800, 300, al_map_rgb(250, 250, 250));
        al_draw_text(police, al_map_rgb(232, 140, 0), 350, 230, 0, "C'EST AU TOUR DU JOUEUR 1!");
        al_flip_display();
        al_rest(3);


        while (compteurcercle1<10&&secondes1>0) {

                double nouveau_temps1 = al_get_time();
                if (nouveau_temps1 - temps_precedent1 >= 1.0) {///verifier si une seconde s'est passée
                    secondes1=secondes1-1;
                    temps_precedent1 = nouveau_temps1;
                }

            al_wait_for_event(queue, &event);
            al_get_mouse_state(&mouse_state);
            al_draw_scaled_bitmap(arriere_plan, 0, 0, 1280, 720, 0, 0, 1200, 800, 0);
            for (i = 0; i < NUM_CERCLES; i++) {
                al_draw_scaled_bitmap(standballon, 0, 0, 458, 545, 350, 0, 514, 612, 0);

            }
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                fin=1;
                ///rafficher le fond de map
            }
            else if (event.type == ALLEGRO_EVENT_TIMER) {
                if (key[ESCAPE] == true) {
                    compteurcercle1=10;
                    Attractions(fond, al_map_rgb(250, 250, 250), police, ticket, *p1, *p2);
                    al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 260, 675, 34, 48, 0);
                    al_flip_display();
                }


                for (i = 0; i < NUM_CERCLES; i++) {
                        cercles[i].x += cercles[i].dx;
                        cercles[i].y += cercles[i].dy;

                    if (cercles[i].x < 385 ||
                        cercles[i].x > 830 - cercles[i].rayon) {
                        cercles[i].dx *= -1;
                    }

                    if (cercles[i].y < 225 ||
                        cercles[i].y > 445 - cercles[i].rayon) {
                        cercles[i].dy *= -1;
                    }
                }
                for (i = 0; i < NUM_CERCLES; i++) {
                     if(cercles[i].actif==true) {
                    al_draw_scaled_bitmap(pokeball, 0, 0, 20, 20, cercles[i].x, cercles[i].y, 20, 20, 0);
                    }
                }
                    al_draw_textf(police, al_map_rgb(255,255,255),500,150,0,"%d",compteurcercle1);
                    al_draw_textf(police, al_map_rgb(255,255,255),600,150,0,"%02d", secondes1);

                al_flip_display();

            }
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.mouse.button == 1) {
                    for ( i = 0; i < NUM_CERCLES; i++) {
                        float distance = sqrt(pow(event.mouse.x - cercles[i].x, 2) +
                                              pow(event.mouse.y - cercles[i].y,
                                                  2));
                        if (distance < cercles[i].rayon) {
                            cercles[i].actif = false;
                            al_play_sample(soncapture,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                            compteurcercle1 +=1 ;
                        }
                    }

                }
            }
             if (event.type == ALLEGRO_EVENT_KEY_DOWN){
                 switch (event.keyboard.keycode){
                     case ALLEGRO_KEY_ESCAPE:
                         key[ESCAPE] = true;
                         break;
                 }

             }
             if (event.type == ALLEGRO_EVENT_KEY_UP) {
                 switch (event.keyboard.keycode){
                     case ALLEGRO_KEY_ESCAPE:
                         key[ESCAPE] = false;
                         break;
                 }

             }
        }
        al_draw_scaled_bitmap(arriere_plan, 0, 0, 1280, 720, 0, 0, 1200, 800, 0);
        al_draw_filled_rectangle(300, 200, 900, 300, al_map_rgb(250, 250, 250));
        al_draw_text(police, al_map_rgb(232, 140, 0), 350, 230, 0, "C'EST AU TOUR DU JOUEUR 2!\n""préparez-vous!");
        ///ne met pasle truc à la ligne donc le \n sert à rien
        al_flip_display();
        al_rest(3);
        for(i=0;i<NUM_CERCLES;i++){
            cercles[i].actif=true;
        }


        while (compteurcercle2<10&&secondes2>0) {
            time(0);

            double nouveau_temps2 = al_get_time()+secondes1;
            if (nouveau_temps2 - temps_precedent2 >= 1.0) {///verifier si une seconde s'est passée
                secondes2=secondes2-1;
                temps_precedent2 = nouveau_temps2;
            }

            al_wait_for_event(queue, &event);
            al_get_mouse_state(&mouse_state);
            al_draw_scaled_bitmap(arriere_plan, 0, 0, 1280, 720, 0, 0, 1200, 800, 0);
            for (i = 0; i < NUM_CERCLES; i++) {
                al_draw_scaled_bitmap(standballon, 0, 0, 458, 545, 350, 0, 514, 612, 0);

            }
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                fin=1;
                ///rafficher le fond de map
            } else if (event.type == ALLEGRO_EVENT_TIMER) {
                if (key[ESCAPE] == true) {
                    compteurcercle2=10;
                    Attractions(fond, al_map_rgb(250, 250, 250), police, ticket, *p1, *p2);
                    al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 260, 675, 34, 48, 0);
                    al_flip_display();
                }



                for (i = 0; i < NUM_CERCLES; i++) {
                    cercles[i].x += cercles[i].dx;
                    cercles[i].y += cercles[i].dy;

                    if (cercles[i].x < 385 ||
                        cercles[i].x > 830 - cercles[i].rayon) {
                        cercles[i].dx *= -1;
                    }

                    if (cercles[i].y < 225 ||
                        cercles[i].y > 445 - cercles[i].rayon) {
                        cercles[i].dy *= -1;
                    }

                }
                for (i = 0; i < NUM_CERCLES; i++) {
                    if(cercles[i].actif==true) {
                        al_draw_scaled_bitmap(pokeball, 0, 0, 20, 20, cercles[i].x, cercles[i].y, 20, 20, 0);
                    }
                }
                    al_draw_textf(police, al_map_rgb(255,255,255),500,150,0,"%d",compteurcercle2);
                    al_draw_textf(police, al_map_rgb(255,255,255),600,150,0,"%02d", secondes2);

                al_flip_display();

            }
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.mouse.button == 1) {
                    for ( i = 0; i < NUM_CERCLES; i++) {
                        float distance = sqrt(pow(event.mouse.x - cercles[i].x, 2) +
                                              pow(event.mouse.y - cercles[i].y,
                                                  2));
                        if (distance < cercles[i].rayon) {
                            cercles[i].actif = false;
                            al_play_sample(soncapture,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                            compteurcercle2 +=1 ;
                        }

                    }
                }
            }
            if (event.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (event.keyboard.keycode){
                    case ALLEGRO_KEY_ESCAPE:
                        key[ESCAPE] = true;
                        break;
                }

            }
            if (event.type == ALLEGRO_EVENT_KEY_UP) {
                switch (event.keyboard.keycode){
                    case ALLEGRO_KEY_ESCAPE:
                        key[ESCAPE] = false;
                        break;
                }

            }

        }
        al_draw_filled_rectangle(300, 200, 700, 300, al_map_rgb(250, 250, 250));
        if(compteurcercle1<compteurcercle2){
            al_draw_text(police, al_map_rgb(232, 140, 0), 350, 230, 0, "LE JOUEUR 2 GAGNE");
            al_flip_display();
            p1->tickets -= 1;
            p2->tickets += 1;
            p2->score += 1;
            al_rest(4);



        }
        else if(compteurcercle2<compteurcercle1){
            al_draw_text(police, al_map_rgb(232, 140, 0), 350, 230, 0, "LE JOUEUR 1 GAGNE");
            al_flip_display();
            p1->tickets += 1;
            p2->tickets -= 1;
            p1->score += 1;
            al_rest(4);


        }
        else{
            al_draw_text(police, al_map_rgb(232, 140, 0), 350, 230, 0, "EGALITE");
            al_rest(4);
            al_flip_display();

        }
        al_play_sample(finjeu,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);

        Attractions(fond, al_map_rgb(250, 250, 250), police, ticket, *p1, *p2);
        al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 530, 510, 34, 48, 0);



        if(p1->touractif==true){
            p1->touractif=false;
            p2->touractif=true;
            p1->x = 520;
            p1->y = 510;
            p2->x=530;
            p2->y=510;
        }else if(p2->touractif==true){
            p2->touractif=false;
            p1->touractif=true;
            p1->x = 520;
            p1->y = 510;
            p2->x=530;
            p2->y=510;
        }

    }
    al_flip_display();
    al_destroy_bitmap(arriere_plan);
    al_destroy_bitmap(standballon);
    al_destroy_sample(soncapture);
    al_destroy_sample_instance(songinstance);
}