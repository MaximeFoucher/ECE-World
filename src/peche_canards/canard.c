#include "canard.h"

int Canard(ALLEGRO_EVENT_QUEUE *queue, bool key[KEY_MAX], ALLEGRO_BITMAP *fond, Personnage *perso,
            ALLEGRO_BITMAP *ticket, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *imageperso, Personnage *p2) {

    int fin = 0;
    /*
    if (perso->tickets == 0 || p2->tickets == 0) {
        fin = 1;
        al_draw_textf(texte, al_map_rgb(250, 250, 250), 100, 650, 0, "je devrais aller chercher des tickets avant");
        al_flip_display();
        al_rest(2.0);
    }*/
    ALLEGRO_BITMAP *peche = NULL;
    ALLEGRO_BITMAP *psyko = NULL;
    ALLEGRO_BITMAP *cannapeche = NULL;

    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_EVENT event;
    ALLEGRO_SAMPLE *psycho_son=NULL;
    psycho_son= al_load_sample("..\\audio\\psycho.ogg");

    if (fin == 0) {
        psyko = al_load_bitmap("..\\image\\psyko.png");
        peche = al_load_bitmap("..\\image\\canard.jpg");
        cannapeche = al_load_bitmap("..\\image\\canne peche.png");
        al_draw_scaled_bitmap(peche, 0, 0, 2302, 1777, 0, 0, LARGEUR, HAUTEUR, 0);

        CANARD tabcanard[NbCanard];
        CANARD *canardDeplace = NULL;
        int compteurcanard1 = 0;
        int compteurcanard2=0;
        int xsouris, ysouris;

        ///temps
        int secondes1=23;
        int secondes2=23;

        double temps_precedent1=al_get_time();
        double temps_precedent2=al_get_time();


        ////////////////////////////////////////generation canards
        for (int i = 0; i < NbCanard; i++) {
            tabcanard[i].x = rand() % LARGEUR * 6 - LARGEUR * 6;
            /////mettre les x à -10
            tabcanard[i].y = rand() % 160 + 200;
            tabcanard[i].rayon = 32;
            tabcanard[i].actif = false;
            al_draw_scaled_bitmap(psyko, 0, 0, 90, 90, tabcanard[i].x, tabcanard[i].y, 90, 90, 0);
        }
        al_flip_display();

        while (fin == 0) {///////////////////joueur 1
        ///secondes

            double nouveau_temps1 = al_get_time();
            if (nouveau_temps1 - temps_precedent1 >= 1.0) {///verifier si une seconde s'est passée
                secondes1=secondes1-1;
                temps_precedent1 = nouveau_temps1;
            }
            if (secondes1==0){
                fin=1;
            }

            al_wait_for_event(queue, &event);
            al_get_mouse_state(&mouse_state);
            al_draw_scaled_bitmap(peche, 0, 0, 2302, 1777, 0, 0, LARGEUR, HAUTEUR, 0);
            for (int i = 0; i < NbCanard; i++) {
                al_draw_scaled_bitmap(psyko, 0, 0, 90, 90, tabcanard[i].x, tabcanard[i].y, 90, 90, 0);
            }
            al_draw_textf(texte, al_map_rgb(250, 250, 250), 0, 0, 0, "score: %d", compteurcanard1);
            al_draw_textf(texte, al_map_rgb(250, 250, 250), 0, 20, 0, "temps: %d", secondes1);
            al_draw_scaled_bitmap(cannapeche, 0, 0, 225, 225, xsouris - 160, ysouris - 440, 900, 900, 0);
            if(secondes1>=20){
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_textf(texte, al_map_rgb(250, 250, 250), 600, 400, 0, "%d", secondes1-20);
                al_draw_textf(texte, al_map_rgb(250, 250, 250), 600, 360, 0, "Au tour du premier joueur");
            }
            al_flip_display();
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                fin = 1;
                Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *p2);
                al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 260, 675, 34, 48, 0);
                al_flip_display();
                ////retourner 1 pour que ca marque la fin dans le main
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
            else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
                xsouris = event.mouse.x;
                ysouris = event.mouse.y;
                if (canardDeplace != NULL) {
                    canardDeplace->x = xsouris - 30;
                    canardDeplace->y = ysouris - 30;
                }
            }
            else if (event.type == ALLEGRO_EVENT_TIMER) {
                if (key[ESCAPE] == true) {
                    fin = 1;
                    Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *p2);
                    al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 260, 675, 34, 48, 0);
                    al_flip_display();
                    key[ESCAPE]=false;
                }
                for (int i = 0; i < NbCanard; i++) {
                    if (tabcanard[i].actif == true) {
                        tabcanard[i].x += 3;
                        if(secondes1>=20){
                            tabcanard[i].x -= 3;
                        }
                        int deplaaleay = rand() % 2;
                        if (deplaaleay == 1 && tabcanard[i].y < 350) {
                            tabcanard[i].y += 6;
                        }
                        if (deplaaleay == 0 && tabcanard[i].y > 200) {
                            tabcanard[i].y -= 6;
                        }
                    }
                }
                int aleacanard = rand() % NbCanard;
                ////////////
                if (tabcanard[aleacanard].y < 450 || tabcanard[aleacanard].y>650) { //600
                    tabcanard[aleacanard].actif = true;
                    if(tabcanard[aleacanard].y>650){
                        //compteurcanard-=1;
                    }
                }
            }
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.mouse.button == 1) { //////mettre la suite dans timer
                    if (event.mouse.y < 450) {
                        for (int i = 0; i < NbCanard; i++) {
                            double distance = sqrt(pow(event.mouse.x - tabcanard[i].x - 45, 2) +
                                                   pow(event.mouse.y - tabcanard[i].y - 45, 2));
                            if (distance < tabcanard[i].rayon) {
                                tabcanard[i].actif = false;
                                al_play_sample(psycho_son,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);

                                canardDeplace = &tabcanard[i];
                            }
                        }
                    }
                }
            }
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                if (event.mouse.button == 1) {
                    if(canardDeplace!=NULL) {
                        if (event.mouse.y >= 450) {
                            canardDeplace->actif=false;
                            if(ysouris<650){
                                compteurcanard1 += 1;
                            }
                        }
                    }
                    canardDeplace = NULL;
                }
            }
            ////////////////////////////
            al_flip_display();
            if (compteurcanard1 == NbCanard) {
                fin = 1;

            }
        }
        ////////////////////////////////////////////////joueur 2
        fin=0;

        for (int i = 0; i < NbCanard; i++) {
            tabcanard[i].x = rand() % LARGEUR * 6 - LARGEUR * 6;
            /////mettre les x à -10
            tabcanard[i].y = rand() % 160 + 200;
            tabcanard[i].rayon = 32;
            tabcanard[i].actif = false;
            al_draw_scaled_bitmap(psyko, 0, 0, 90, 90, tabcanard[i].x, tabcanard[i].y, 90, 90, 0);
        }
        al_flip_display();

        while (fin == 0) {

            double nouveau_temps2 = al_get_time();
            if (nouveau_temps2 - temps_precedent2 >= 1.0) {///verifier si une seconde s'est passée
                secondes2=secondes2-1;
                temps_precedent2 = nouveau_temps2;
            }
            if (secondes2==0){
                fin=1;
            }

            al_wait_for_event(queue, &event);
            al_get_mouse_state(&mouse_state);
            al_draw_scaled_bitmap(peche, 0, 0, 2302, 1777, 0, 0, LARGEUR, HAUTEUR, 0);
            for (int i = 0; i < NbCanard; i++) {
                al_draw_scaled_bitmap(psyko, 0, 0, 90, 90, tabcanard[i].x, tabcanard[i].y, 90, 90, 0);
            }
            al_draw_textf(texte, al_map_rgb(250, 250, 250), 0, 0, 0, "score: %d", compteurcanard2);
            al_draw_textf(texte, al_map_rgb(250, 250, 250), 0, 20, 0, "temps: %d", secondes2);
            al_draw_scaled_bitmap(cannapeche, 0, 0, 225, 225, xsouris - 160, ysouris - 440, 900, 900, 0);
            if(secondes2>=20){
                ////mettre le changement
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_textf(texte, al_map_rgb(250, 250, 250), 600, 400, 0, "%d", secondes2-20);
                al_draw_textf(texte, al_map_rgb(250, 250, 250), 600, 360, 0, "Au tour du deuxieme joueur");
            }
            al_flip_display();
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                fin = 1;
                Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *p2);
                al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 260, 675, 34, 48, 0);
                al_flip_display();
                ////retourner 1 pour que ca marque la fin dans le main
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
            else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
                xsouris = event.mouse.x;
                ysouris = event.mouse.y;
                if (canardDeplace != NULL) {
                    canardDeplace->x = xsouris - 30;
                    canardDeplace->y = ysouris - 30;
                }
            }
            else if (event.type == ALLEGRO_EVENT_TIMER) {
                if (key[ESCAPE] == true) {
                    fin = 1;
                    Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *p2);
                    al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 260, 675, 34, 48, 0);
                    al_flip_display();
                    key[ESCAPE]=false;
                }
                for (int i = 0; i < NbCanard; i++) {
                    if (tabcanard[i].actif == true) {
                        tabcanard[i].x += 3;
                        if(secondes2>=20){
                            tabcanard[i].x -= 3;
                        }
                        int deplaaleay = rand() % 2;
                        if (deplaaleay == 1 && tabcanard[i].y < 350) {
                            tabcanard[i].y += 6;
                        }
                        if (deplaaleay == 0 && tabcanard[i].y > 200) {
                            tabcanard[i].y -= 6;
                        }
                    }
                }
                int aleacanard = rand() % NbCanard;
                ////////////
                if (tabcanard[aleacanard].y < 450 || tabcanard[aleacanard].y>650) { //600
                    tabcanard[aleacanard].actif = true;
                }
            }
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.mouse.button == 1) { //////mettre la suite dans timer
                    if (event.mouse.y < 450) {
                        for (int i = 0; i < NbCanard; i++) {
                            double distance = sqrt(pow(event.mouse.x - tabcanard[i].x - 45, 2) +
                                                   pow(event.mouse.y - tabcanard[i].y - 45, 2));
                            if (distance < tabcanard[i].rayon) {
                                tabcanard[i].actif = false;
                                al_play_sample(psycho_son,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);

                                canardDeplace = &tabcanard[i];
                            }
                        }
                    }
                }
            }
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                if (event.mouse.button == 1) {
                    if(canardDeplace!=NULL) {
                        if (event.mouse.y >= 450) {
                            canardDeplace->actif=false;
                            if(ysouris<650){
                                compteurcanard2 += 1;
                            }
                        }
                    }
                    canardDeplace = NULL;
                }
            }
            ////////////////////////////
            al_flip_display();
            if (compteurcanard2 == NbCanard) {
                fin = 1;
            }
        }

        if(compteurcanard1>compteurcanard2){
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_textf(texte, al_map_rgb(255,255,255),HAUTEUR/2, 300, 0, "Le joueur 1 gagne");
            al_draw_textf(texte, al_map_rgb(255,255,255),HAUTEUR/2, 340, 0, "Tu recois donc un de score et un ticket");
            al_draw_textf(texte, al_map_rgb(255,255,255),HAUTEUR/2, 380, 0, "Le joueur 2 perds un tickets");
            al_flip_display();
            perso->tickets += 1;
            p2->tickets -= 1;
            perso->score += 1;
            al_rest(4);
        }
        else if(compteurcanard2>compteurcanard1){
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_textf(texte, al_map_rgb(255,255,255),HAUTEUR/2, 300, 0, "Le joueur 2 gagne");
            al_draw_textf(texte, al_map_rgb(255,255,255),HAUTEUR/2, 340, 0, "Tu recois donc un de score et un ticket");
            al_draw_textf(texte, al_map_rgb(255,255,255),HAUTEUR/2, 380, 0, "Le joueur 1 perds un tickets");
            al_flip_display();
            al_rest(4);
            perso->tickets -= 1;
            p2->tickets += 1;
            p2->score += 1;
        }
        else{
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_textf(texte, al_map_rgb(255,255,255),HAUTEUR/2, 300, 0, "Egalité");
            al_draw_textf(texte, al_map_rgb(255,255,255),HAUTEUR/2, 340, 0, "Aucun joueur ne perd ou recoit quoi que ce soit");
            al_flip_display();
            al_rest(4);
        }
    }
    if(perso->touractif==true){
        perso->touractif=false;
        p2->touractif=true;
    }else if(p2->touractif==true){
        p2->touractif=false;
        perso->touractif=true;
    }
    Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *p2);
    al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 260, 675, 34, 48, 0);
    al_flip_display();
    al_destroy_bitmap(psyko);
    al_destroy_bitmap(peche);
    al_destroy_bitmap(cannapeche);
    al_destroy_sample(psycho_son);
    perso->x = 300;
    perso->y = 675;
    p2->x=310;
    p2->y=675;
}
