#include "paris_hippiques.h"



void EntrerParisHippiques (ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT *texte, ALLEGRO_BITMAP* fond, ALLEGRO_BITMAP* imageperso, Personnage *perso, Personnage *perso2, ALLEGRO_BITMAP *ticket) {
    ///Initialisations
    Pokemon *p1 = NULL;
    Pokemon *p2 = NULL;
    Pokemon *p3 = NULL;
    Pokemon *p4 = NULL;
    Pokemon *p5 = NULL;
    Pokemon *tab[5] = {p1,p2,p3,p4,p5};

    ALLEGRO_EVENT event;
    ALLEGRO_FONT* police1 = NULL;
    ALLEGRO_FONT* police2 = NULL;
    ALLEGRO_FONT* police3 = NULL;
    police1 = al_load_ttf_font("..\\fonts\\pixel.ttf", 100, 0);
    police2 = al_load_ttf_font("..\\fonts\\pixel.ttf", 70, 0);
    police3 = al_load_ttf_font("..\\fonts\\pixel.ttf", 60, 0);
    Pokemon *choix_joueur1 = NULL;
    Pokemon *choix_joueur2 = NULL;

    int ecran_fin = 0;
    int i = 0;
    int c = 1;
    int y_lap = 0;
    int y_bour = 0;
    int y_feur = 0;
    int y_grain = 0;
    int y_gour = 0;
    int fin = 0;

    ALLEGRO_BITMAP* fond_course = NULL;
    fond_course = al_load_bitmap("..\\image\\grass_texture_pokemon.jpg");


    ///Création des pokemons
    Pokemon lapyro = {
            "lapyro",
            al_load_bitmap("..\\image\\lapyro_course.png"),
            0,0,250,286,30,136,80,80,rand()%20, 0
    };

    Pokemon bourrinos = {
            "bourinos",
            al_load_bitmap("..\\image\\cheval_course.png"),
            0, 0, 1200, 1172, 30, 136*2, 80, 80, rand()%20, 0
    };

    Pokemon feurisson = {
            "feurisson",
            al_load_bitmap("..\\image\\quilava_course.png"),
            0, 0, 900, 650, 30, 136*3, 80, 80, rand()%20, 0
    };

    Pokemon grainipiot = {
            "grainipiot",
            al_load_bitmap("..\\image\\grainipiot_course.png"),
            0, 0, 501, 512, 30, 136*4, 110, 110, rand()%5, 0
    };

    Pokemon gourmelet = {
            "gourmelet",
            al_load_bitmap("..\\image\\gourmelet_course.png"),
            0, 0, 650, 590,
            30, 136*5, 110, 110, rand()%5, 0
    };

    ///Boucle du jeu
    while(fin == 0) {
        al_wait_for_event(queue, &event);
        al_get_keyboard_event_source();
        al_draw_scaled_bitmap(fond_course, 0, 0, 720, 360, 0, 0, LARGEUR, HAUTEUR, 0);
        al_draw_text(police1, al_map_rgb(0,0,0), 140, 150, 0, "Bienvenue dans la course :");
        al_draw_text(police2, al_map_rgb(0,0,0), 140, 350, 0, "Pariez sur le pokemon le plus rapide");
        al_draw_text(police3, al_map_rgb(0,0,0), 70, 700, 0, "(E pour quitter, J pour jouer)");
        al_flip_display();
        ///E pour quitter
        if (event.keyboard.keycode == ALLEGRO_KEY_E) {
            fin = 1;
            Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *perso2);
            al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 470, 170, 34, 48, 0);
            al_flip_display();
        }
        ///J pour jouer
        else if(event.keyboard.keycode == ALLEGRO_KEY_J) {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(fond_course, 0, 0, 720, 360, 0, 0, LARGEUR, HAUTEUR, 0);
            al_draw_scaled_bitmap(lapyro.cheval, lapyro.sx, lapyro.sy, lapyro.sw, lapyro.sh, lapyro.dx, lapyro.dy, lapyro.dw, lapyro.dh, lapyro.flags);
            al_draw_scaled_bitmap(bourrinos.cheval, bourrinos.sx, bourrinos.sy, bourrinos.sw, bourrinos.sh, bourrinos.dx, bourrinos.dy, bourrinos.dw, bourrinos.dh, bourrinos.flags);
            al_draw_scaled_bitmap(feurisson.cheval, feurisson.sx, feurisson.sy, feurisson.sw, feurisson.sh, feurisson.dx, feurisson.dy, feurisson.dw, feurisson.dh, feurisson.flags);
            al_draw_scaled_bitmap(grainipiot.cheval,grainipiot.sx,grainipiot.sy,grainipiot.sw,grainipiot.sh,grainipiot.dx,grainipiot.dy,grainipiot.dw,grainipiot.dh,grainipiot.flags);
            al_draw_scaled_bitmap(gourmelet.cheval,gourmelet.sx,gourmelet.sy,gourmelet.sw,gourmelet.sh,gourmelet.dx,gourmelet.dy,gourmelet.dw,gourmelet.dh,gourmelet.flags);

            ///Choix du joueur 1
            while(choix_joueur1 == NULL) {
                al_draw_text(police2, al_map_rgb(0,0,0), 50, 20, 0, "Joueur 1, pariez en cliquant sur un pokemon");
                al_draw_rectangle(30, 130, 150, 230, al_map_rgb(0,0,0), 0);
                al_draw_rectangle(30, 260, 150, 360, al_map_rgb(0,0,0), 0);
                al_draw_rectangle(30, 400, 150, 500, al_map_rgb(0,0,0), 0);
                al_draw_rectangle(30, 550, 150, 650, al_map_rgb(0,0,0), 0);
                al_draw_rectangle(30, 690, 150, 790, al_map_rgb(0,0,0), 0);
                al_flip_display();
                al_wait_for_event(queue, &event);

                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1) {
                    int x = event.mouse.x;
                    int y = event.mouse.y;

                    if (x >= 30 && x <= 150 && y >= 120 && y <= 210) {
                        choix_joueur1 = &lapyro;
                    }
                    else if (x >= 30 && x <= 150 && y >= 240 && y <= 335) {
                        choix_joueur1 = &bourrinos;
                    }
                    else if (x >= 30 && x <= 150 && y >= 370 && y <= 465) {
                        choix_joueur1 = &feurisson;
                    }
                    else if (x >= 30 && x <= 150 && y >= 510 && y <= 600) {
                        choix_joueur1 = &grainipiot;
                    }
                    else if (x >= 30 && x <= 150 && y >= 640 && y <= 735) {
                        choix_joueur1 = &gourmelet;
                    }
                    printf("%s", (choix_joueur1)->nom);
                }
            }
            ///Choix du joueur 2
            while(choix_joueur2 == NULL) {
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_scaled_bitmap(fond_course, 0, 0, 720, 360, 0, 0, LARGEUR, HAUTEUR, 0);
                al_draw_scaled_bitmap(lapyro.cheval, lapyro.sx, lapyro.sy, lapyro.sw, lapyro.sh, lapyro.dx, lapyro.dy, lapyro.dw, lapyro.dh, lapyro.flags);
                al_draw_scaled_bitmap(bourrinos.cheval, bourrinos.sx, bourrinos.sy, bourrinos.sw, bourrinos.sh, bourrinos.dx, bourrinos.dy, bourrinos.dw, bourrinos.dh, bourrinos.flags);
                al_draw_scaled_bitmap(feurisson.cheval, feurisson.sx, feurisson.sy, feurisson.sw, feurisson.sh, feurisson.dx, feurisson.dy, feurisson.dw, feurisson.dh, feurisson.flags);
                al_draw_scaled_bitmap(grainipiot.cheval,grainipiot.sx,grainipiot.sy,grainipiot.sw,grainipiot.sh,grainipiot.dx,grainipiot.dy,grainipiot.dw,grainipiot.dh,grainipiot.flags);
                al_draw_scaled_bitmap(gourmelet.cheval,gourmelet.sx,gourmelet.sy,gourmelet.sw,gourmelet.sh,gourmelet.dx,gourmelet.dy,gourmelet.dw,gourmelet.dh,gourmelet.flags);
                al_draw_text(police2, al_map_rgb(0,0,0), 50, 20, 0, "Joueur 2, pariez en cliquant sur un pokemon");
                al_draw_rectangle(30, 130, 150, 230, al_map_rgb(0,0,0), 0);
                al_draw_rectangle(30, 260, 150, 360, al_map_rgb(0,0,0), 0);
                al_draw_rectangle(30, 400, 150, 500, al_map_rgb(0,0,0), 0);
                al_draw_rectangle(30, 550, 150, 650, al_map_rgb(0,0,0), 0);
                al_draw_rectangle(30, 690, 150, 790, al_map_rgb(0,0,0), 0);
                al_flip_display();
                al_wait_for_event(queue, &event);

                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1) {
                    int x = event.mouse.x;
                    int y = event.mouse.y;

                    if (x >= 30 && x <= 150 && y >= 120 && y <= 210) {
                        choix_joueur2 = &lapyro;
                    }
                    else if (x >= 30 && x <= 150 && y >= 240 && y <= 335) {
                        choix_joueur2 = &bourrinos;
                    }
                    else if (x >= 30 && x <= 150 && y >= 370 && y <= 465) {
                        choix_joueur2 = &feurisson;
                    }
                    else if (x >= 30 && x <= 150 && y >= 510 && y <= 600) {
                        choix_joueur2 = &grainipiot;
                    }
                    else if (x >= 30 && x <= 150 && y >= 640 && y <= 735) {
                        choix_joueur2 = &gourmelet;
                    }
                    printf("%s", (choix_joueur2)->nom);
                }
            }

            ///Lance la course
            while(lapyro.dx < 1150 || bourrinos.dx < 1150 || feurisson.dx < 1150 || gourmelet.dx < 1150 || grainipiot.dx < 1150) {
                if(lapyro.dx < 950) {
                    lapyro.v = rand()%20;
                    lapyro.dx += lapyro.v;
                }
                else if(lapyro.dx > 950 && lapyro.dx < 1050){
                    tab[i] = &lapyro;
                    lapyro.dx = 1150;
                    lapyro.dy = 136+(i*136);
                    y_lap = 136+(i*136);
                    i++;
                }
                else {
                    lapyro.dx = 1150;
                    lapyro.dy = y_lap;
                }
                if(bourrinos.dx < 950) {
                    bourrinos.v = rand()%20;
                    bourrinos.dx += bourrinos.v;
                }
                else if(bourrinos.dx > 950 && bourrinos.dx < 1050){
                    tab[i] = &bourrinos;
                    bourrinos.dx = 1150;
                    bourrinos.dy = 136+(i*136);
                    y_bour = 136+(i*136);
                    i++;
                }
                else {
                    bourrinos.dx = 1150;
                    bourrinos.dy = y_bour;
                }
                if(feurisson.dx < 950) {
                    feurisson.v = rand()%20;
                    feurisson.dx += feurisson.v;
                }
                else if(feurisson.dx > 950 && feurisson.dx < 1050){
                    tab[i] = &feurisson;
                    feurisson.dx = 1150;
                    feurisson.dy = 136+(i*136);
                    y_feur = 136+(i*136);
                    i++;
                }
                else {
                    feurisson.dx = 1150;
                    feurisson.dy = y_feur;
                }
                if(gourmelet.dx < 950) {
                    gourmelet.v = rand()%20;
                    gourmelet.dx += gourmelet.v;
                }
                else if(gourmelet.dx > 950 && gourmelet.dx < 1050){
                    tab[i] = &gourmelet;
                    gourmelet.dx = 1150;
                    gourmelet.dy = 136+(i*136);
                    y_gour = 136+(i*136);
                    i++;
                }
                else {
                    gourmelet.dx = 1150;
                    gourmelet.dy = y_gour;
                }
                if(grainipiot.dx < 950) {
                    grainipiot.v = rand()%20;
                    grainipiot.dx += grainipiot.v;
                }
                else if(grainipiot.dx > 950 && grainipiot.dx < 1050){
                    tab[i] = &grainipiot;
                    grainipiot.dx = 1150;
                    grainipiot.dy = 136+(i*136);
                    y_grain = 136+(i*136);
                    i++;
                }
                else {
                    grainipiot.dx = 1150;
                    grainipiot.dy = y_grain;
                }

                if(c == 1) {
                    c = -1;
                }
                else if (c == -1) {
                    c = 1;
                }

                al_clear_to_color(al_map_rgb(0, 0, 0)); // Efface l'affichage précédent


                al_draw_scaled_bitmap(fond_course, 0, 0, 720, 360, 0, 0, LARGEUR, HAUTEUR, 0);

                al_draw_scaled_rotated_bitmap(lapyro.cheval, 40, 40, lapyro.dx, lapyro.dy, 0.4, 0.4, c*(1*(ALLEGRO_PI/180)), 0);
                al_draw_scaled_rotated_bitmap(bourrinos.cheval, 40, 40, bourrinos.dx, bourrinos.dy, 0.09, 0.09, c*(1*(ALLEGRO_PI/180)), 0);
                al_draw_scaled_rotated_bitmap(grainipiot.cheval, 40, 40, grainipiot.dx, grainipiot.dy, 0.24, 0.24, c*(1*(ALLEGRO_PI/180)), 0);
                al_draw_scaled_rotated_bitmap(gourmelet.cheval, 40, 40, gourmelet.dx, gourmelet.dy, 0.2, 0.2, c*(1*(ALLEGRO_PI/180)), 0);
                al_draw_scaled_rotated_bitmap(feurisson.cheval, 40, 40, feurisson.dx, feurisson.dy, 0.15, 0.15, c*(1*(ALLEGRO_PI/180)), 0);


                al_flip_display();
                al_rest(0.05); // Pause pour donner l'illusion de mouvement
            }
            bool affiche = true;
            while(ecran_fin == 0) {
                al_wait_for_event(queue, &event);
                if (event.keyboard.keycode == ALLEGRO_KEY_E) {
                    ecran_fin = 1;
                    Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *perso, *perso2);
                    al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 470, 170, 34, 48, 0);
                    al_flip_display();
                }

                if(affiche) {
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_scaled_bitmap(fond_course, 0, 0, 720, 360, 0, 0, LARGEUR, HAUTEUR, 0);
                    al_draw_scaled_bitmap(lapyro.cheval, lapyro.sx, lapyro.sy, lapyro.sw, lapyro.sh, lapyro.dx,
                                          lapyro.dy, lapyro.dw, lapyro.dh, lapyro.flags);
                    al_draw_scaled_bitmap(bourrinos.cheval, bourrinos.sx, bourrinos.sy, bourrinos.sw, bourrinos.sh,
                                          bourrinos.dx, bourrinos.dy, bourrinos.dw, bourrinos.dh, bourrinos.flags);
                    al_draw_scaled_bitmap(feurisson.cheval, feurisson.sx, feurisson.sy, feurisson.sw, feurisson.sh,
                                          feurisson.dx, feurisson.dy, feurisson.dw, feurisson.dh, feurisson.flags);
                    al_draw_scaled_bitmap(grainipiot.cheval, grainipiot.sx, grainipiot.sy, grainipiot.sw, grainipiot.sh,
                                          grainipiot.dx, grainipiot.dy, grainipiot.dw, grainipiot.dh, grainipiot.flags);
                    al_draw_scaled_bitmap(gourmelet.cheval, gourmelet.sx, gourmelet.sy, gourmelet.sw, gourmelet.sh,
                                          gourmelet.dx, gourmelet.dy, gourmelet.dw, gourmelet.dh, gourmelet.flags);
                    al_draw_text(police1, al_map_rgb(0, 0, 0), 1000, 136, 0, "1 :");
                    al_draw_text(police1, al_map_rgb(0, 0, 0), 1000, 136 * 2, 0, "2 :");
                    al_draw_text(police1, al_map_rgb(0, 0, 0), 1000, 136 * 3, 0, "3 :");
                    al_draw_text(police1, al_map_rgb(0, 0, 0), 1000, 136 * 4, 0, "4 :");
                    al_draw_text(police1, al_map_rgb(0, 0, 0), 1000, 136 * 5, 0, "5 :");
                    al_flip_display();

                    if (tab[0] == &lapyro) {
                        p1 = &lapyro;
                    } else if (tab[0] == &bourrinos) {
                        p1 = &bourrinos;
                    } else if (tab[0] == &feurisson) {
                        p1 = &feurisson;
                    } else if (tab[0] == &grainipiot) {
                        p1 = &grainipiot;
                    } else if (tab[0] == &gourmelet) {
                        p1 = &gourmelet;
                    }

                    ///Vérification de la victoire
                    if (p1 == choix_joueur1) {
                        al_draw_text(police1, al_map_rgb(0, 0, 0), 25, 200, 0, "Joueur 1 gagne +1 ticket");
                        perso->tickets += 1;
                        perso->score += 1;
                    } else {
                        al_draw_text(police1, al_map_rgb(0, 0, 0), 25, 200, 0, "Joueur 1 perd");
                        perso->tickets -= 1;
                    }
                    if (p1 == choix_joueur2) {
                        al_draw_text(police1, al_map_rgb(0, 0, 0), 25, 600, 0, "Joueur 2 gagne +1 ticket");
                        perso2->tickets += 1;
                        perso2->score += 1;
                    } else {
                        al_draw_text(police1, al_map_rgb(0, 0, 0), 25, 600, 0, "Joueur 2 perd");
                        perso2->tickets = perso2->tickets -1;
                    }
                    al_draw_text(police3, al_map_rgb(0, 0, 0), 200, 700, 0, "E pour quitter");
                    al_flip_display();
                    affiche = false;
                }


            }
            fin =0;
        }
    }
    if(perso->touractif==true){
        perso->touractif=false;
        perso2->touractif=true;
        perso->x = 470;
        perso->y = 170;
        perso2->x=480;
        perso2->y=170;
    }else if(perso2->touractif==true){
        perso2->touractif=false;
        perso->touractif=true;
        perso->x = 470;
        perso->y = 170;
        perso2->x=480;
        perso2->y=170;
    }
    ///Destroy
    al_destroy_bitmap(fond_course);
    al_destroy_bitmap(al_load_bitmap("C:\\Users\\33781\\CLionProjects\\Projet2\\image\\lapyro_course.png"));
    al_destroy_bitmap(al_load_bitmap("C:\\Users\\33781\\CLionProjects\\Projet2\\image\\cheval_course.png"));
    al_destroy_bitmap(al_load_bitmap("C:\\Users\\33781\\CLionProjects\\Projet2\\image\\quilava_course.png"));
    al_destroy_bitmap(al_load_bitmap("C:\\Users\\33781\\CLionProjects\\Projet2\\image\\grainipiot_course.png"));
    al_destroy_bitmap(al_load_bitmap("C:\\Users\\33781\\CLionProjects\\Projet2\\image\\gourmelet_course.png"));
    al_destroy_font(police1);
    al_destroy_font(police2);
    al_destroy_font(police3);
}
