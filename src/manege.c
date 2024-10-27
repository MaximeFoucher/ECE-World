#include "manege.h"

int Menu(ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP* clavier, ALLEGRO_FONT *texte, ALLEGRO_EVENT_QUEUE *queue, bool key[KEY_MAX],
         ALLEGRO_BITMAP *ticket, Personnage *p, ALLEGRO_BITMAP *imageperso, Personnage *p2,
         ALLEGRO_BITMAP *imageperso2, int menu, int entrerticket, int *nom) {
    ALLEGRO_EVENT event;
    ALLEGRO_FONT *texte1 = NULL;
    ALLEGRO_FONT *texte2 = NULL;
    ALLEGRO_COLOR couleur = al_map_rgb(200, 200, 200);

    float x = 0;
    //int fin_nom_1=0;
    //int fin_nom_2=0;
    //p->verif_nom = false;
    //p2->verif_nom = false;
    texte1 = al_load_ttf_font("..\\fonts\\pixel.ttf", 100, 0);
    texte2 = al_load_ttf_font("..\\fonts\\pixel.ttf", 50, 0);
    assert(texte1);
    assert(texte2);
    al_install_audio();
    al_init_acodec_addon();

    ///audio
     //ALLEGRO_SAMPLE *musique_menu=NULL;
    //musique_menu= al_load_sample("..\\audio\\song_menu.ogg");


    if (*nom==0) {
        TaperNom(key, nom, texte, queue, p, p2);
        *nom=1;
        ///////////////////////////////////////////////////////sauvegarder les noms, mettre dans score, faire le malloc
    }

    while (true) {
        al_wait_for_event(queue, &event);
        al_draw_scaled_bitmap(fond, 0, 0, 1024, 653, x, -500, 2048, 1306, 0);
        al_draw_filled_rectangle(300, 500, 1000, 600, couleur);///deuxieme
        al_draw_filled_rectangle(300, 350, 1000, 450, couleur);///premier
        al_draw_filled_rectangle(500, 200, 800, 300, couleur);///haut
        al_draw_filled_rectangle(300, 650, 1000, 750, couleur);///troisieme

        al_draw_textf(texte1, al_map_rgb(232, 140, 0), 570, 200, 0, "PARC");///haut
        al_draw_textf(texte1, al_map_rgb(232, 140, 0), 350, 350, 0, "ENTER -> Entrer");///prem
        al_draw_textf(texte1, al_map_rgb(232, 140, 0), 375, 500, 0, "ESC -> Quitter");///deux
        al_draw_textf(texte1, al_map_rgb(232, 140, 0), 350, 650, 0, "P -> Sauvegarde");///trois

        al_flip_display();
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            false;
            al_destroy_font(texte1);
            return 1;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE: {
                    key[ESCAPE] = true;
                    break;
                }
                case ALLEGRO_KEY_ENTER: {
                    key[ENTER] = true;
                    break;
                }
                case ALLEGRO_KEY_P: {
                    key[P] = true;
                    break;
                }
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE: {
                    key[ESCAPE] = false;
                    break;
                }
                case ALLEGRO_KEY_ENTER: {
                    key[ENTER] = false;
                    break;
                }
                case ALLEGRO_KEY_P: {
                    key[P] = false;
                    break;
                }
            }
        }
        if (key[P] == true){
            key[P]=false;
            Sauvegardes(p, p2, &x, event, texte1, queue, key, fond, menu, entrerticket);
        }
        if (key[ESCAPE] == true) {
            false;
            al_destroy_font(texte1);
            key[ESCAPE] = false;
            return 1;
        } else if (key[ENTER]) {
           // al_stop_sample(musique_menu);
            p->x = 10;
            p->y = 625;
            p2->x = 10;
            p2->y = 635;
            Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *p, *p2);
            al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, p->x, p->y, 34, 48, 0);
            al_draw_scaled_bitmap(imageperso2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);
            false;
            al_destroy_font(texte1);

            al_flip_display();
            key[ENTER]=false;
            return 0;
        }
        x -= 0.15f;
        if (x <= -750) { x = 0; }
        //al_destroy_sample(musique_menu);
    }
}

void TaperNom(bool key[KEY_MAX], int* nom, ALLEGRO_FONT *texte, ALLEGRO_EVENT_QUEUE *queue
              , Personnage *p, Personnage *p2){
    ALLEGRO_EVENT event;

    char nomtemporaire[MAXNOM];
    int i=0;
    int fin=0;

    while(fin==0){
        al_wait_for_event(queue, &event);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(texte, al_map_rgb(255, 255, 255), 425, 300, 0, "Joueur 1, tapez votre nom");
        for(int j=0; j<=i; ++j) {
            al_draw_textf(texte, al_map_rgb(255, 255, 255), 0+15*j, 400, 0,
                          "%c", nomtemporaire[j]);
        }
        if (i==MAXNOM){
            al_draw_text(texte, al_map_rgb(255, 255, 255), 325, 200, 0, "Vous avez atteint le maximum de caractères");
        }
        al_flip_display();
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            fin=1;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE: {
                    key[ESCAPE] = true;
                    break;
                }
                case ALLEGRO_KEY_LEFT: {
                    key[GAUCHE] = true;
                    break;
                }
                case ALLEGRO_KEY_ENTER: {
                    key[ENTER] = true;
                    break;
                }
                case ALLEGRO_KEY_A: {
                    key[A] = true;
                    break;
                }
                case ALLEGRO_KEY_B: {
                    key[B] = true;
                    break;
                }
                case ALLEGRO_KEY_C: {
                    key[C] = true;
                    break;
                }
                case ALLEGRO_KEY_D: {
                    key[D] = true;
                    break;
                }
                case ALLEGRO_KEY_E: {
                    key[E] = true;
                    break;
                }
                case ALLEGRO_KEY_F: {
                    key[F] = true;
                    break;
                }
                case ALLEGRO_KEY_G: {
                    key[G] = true;
                    break;
                }
                case ALLEGRO_KEY_H: {
                    key[H] = true;
                    break;
                }
                case ALLEGRO_KEY_I: {
                    key[I] = true;
                    break;
                }
                case ALLEGRO_KEY_J: {
                    key[J] = true;
                    break;
                }
                case ALLEGRO_KEY_K: {
                    key[K] = true;
                    break;
                }
                case ALLEGRO_KEY_L: {
                    key[L] = true;
                    break;
                }
                case ALLEGRO_KEY_M: {
                    key[M] = true;
                    break;
                }
                case ALLEGRO_KEY_N: {
                    key[N] = true;
                    break;
                }
                case ALLEGRO_KEY_O: {
                    key[O] = true;
                    break;
                }
                case ALLEGRO_KEY_P: {
                    key[P] = true;
                    break;
                }
                case ALLEGRO_KEY_Q: {
                    key[Q] = true;
                    break;
                }
                case ALLEGRO_KEY_R: {
                    key[R] = true;
                    break;
                }
                case ALLEGRO_KEY_S: {
                    key[S] = true;
                    break;
                }
                case ALLEGRO_KEY_T: {
                    key[T] = true;
                    break;
                }
                case ALLEGRO_KEY_U: {
                    key[U] = true;
                    break;
                }
                case ALLEGRO_KEY_V: {
                    key[V] = true;
                    break;
                }
                case ALLEGRO_KEY_W: {
                    key[W] = true;
                    break;
                }
                case ALLEGRO_KEY_X: {
                    key[X] = true;
                    break;
                }
                case ALLEGRO_KEY_Y: {
                    key[Y] = true;
                    break;
                }
                case ALLEGRO_KEY_Z: {
                    key[Z] = true;
                    break;
                }
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE: {
                    key[ESCAPE] = false;
                    break;
                }
                case ALLEGRO_KEY_LEFT: {
                    key[GAUCHE] = false;
                    break;
                }
                case ALLEGRO_KEY_ENTER: {
                    key[ENTER] = false;
                    break;
                }
                case ALLEGRO_KEY_A: {
                    key[A] = false;
                    break;
                }
                case ALLEGRO_KEY_B: {
                    key[B] = false;
                    break;
                }
                case ALLEGRO_KEY_C: {
                    key[C] = false;
                    break;
                }
                case ALLEGRO_KEY_D: {
                    key[D] = false;
                    break;
                }
                case ALLEGRO_KEY_E: {
                    key[E] = false;
                    break;
                }
                case ALLEGRO_KEY_F: {
                    key[F] = false;
                    break;
                }
                case ALLEGRO_KEY_G: {
                    key[G] = false;
                    break;
                }
                case ALLEGRO_KEY_H: {
                    key[H] = false;
                    break;
                }
                case ALLEGRO_KEY_I: {
                    key[I] = false;
                    break;
                }
                case ALLEGRO_KEY_J: {
                    key[J] = false;
                    break;
                }
                case ALLEGRO_KEY_K: {
                    key[K] = false;
                    break;
                }
                case ALLEGRO_KEY_L: {
                    key[L] = false;
                    break;
                }
                case ALLEGRO_KEY_M: {
                    key[M] = false;
                    break;
                }
                case ALLEGRO_KEY_N: {
                    key[N] = false;
                    break;
                }
                case ALLEGRO_KEY_O: {
                    key[O] = false;
                    break;
                }
                case ALLEGRO_KEY_P: {
                    key[P] = false;
                    break;
                }
                case ALLEGRO_KEY_Q: {
                    key[Q] = false;
                    break;
                }
                case ALLEGRO_KEY_R: {
                    key[R] = false;
                    break;
                }
                case ALLEGRO_KEY_S: {
                    key[S] = false;
                    break;
                }
                case ALLEGRO_KEY_T: {
                    key[T] = false;
                    break;
                }
                case ALLEGRO_KEY_U: {
                    key[U] = false;
                    break;
                }
                case ALLEGRO_KEY_V: {
                    key[V] = false;
                    break;
                }
                case ALLEGRO_KEY_W: {
                    key[W] = false;
                    break;
                }
                case ALLEGRO_KEY_X: {
                    key[X] = false;
                    break;
                }
                case ALLEGRO_KEY_Y: {
                    key[Y] = false;
                    break;
                }
                case ALLEGRO_KEY_Z: {
                    key[Z] = false;
                    break;
                }
            }
        }
        if (key[A] && i<MAXNOM){
            nomtemporaire[i]='A';
            key[A]=false;
            i+=1;
        }
        if (key[B] && i<MAXNOM){
            nomtemporaire[i]='B';
            key[B]=false;
            i+=1;
        }
        if (key[C] && i<MAXNOM){
            nomtemporaire[i]='C';
            key[C]=false;
            i+=1;
        }
        if (key[D] && i<MAXNOM){
            nomtemporaire[i]='D';
            key[D]=false;
            i+=1;
        }
        if (key[E] && i<MAXNOM){
            nomtemporaire[i]='E';
            key[E]=false;
            i+=1;
        }
        if (key[F] && i<MAXNOM){
            nomtemporaire[i]='F';
            key[F]=false;
            i+=1;
        }
        if (key[G] && i<MAXNOM){
            nomtemporaire[i]='G';
            key[G]=false;
            i+=1;
        }
        if (key[H] && i<MAXNOM){
            nomtemporaire[i]='H';
            key[H]=false;
            i+=1;
        }
        if (key[I] && i<MAXNOM){
            nomtemporaire[i]='I';
            key[I]=false;
            i+=1;
        }
        if (key[J] && i<MAXNOM){
            nomtemporaire[i]='J';
            key[J]=false;
            i+=1;
        }
        if (key[J] && i<MAXNOM){
            nomtemporaire[i]='J';
            key[J]=false;
            i+=1;
        }
        if (key[K] && i<MAXNOM){
            nomtemporaire[i]='K';
            key[K]=false;
            i+=1;
        }
        if (key[L] && i<MAXNOM){
            nomtemporaire[i]='L';
            key[L]=false;
            i+=1;
        }
        if (key[M] && i<MAXNOM){
            nomtemporaire[i]='M';
            key[M]=false;
            i+=1;
        }
        if (key[N] && i<MAXNOM){
            nomtemporaire[i]='N';
            key[N]=false;
            i+=1;
        }
        if (key[O] && i<MAXNOM){
            nomtemporaire[i]='O';
            key[O]=false;
            i+=1;
        }
        if (key[P] && i<MAXNOM){
            nomtemporaire[i]='P';
            key[P]=false;
            i+=1;
        }
        if (key[Q] && i<MAXNOM){
            nomtemporaire[i]='Q';
            key[Q]=false;
            i+=1;
        }
        if (key[R] && i<MAXNOM){
            nomtemporaire[i]='R';
            key[R]=false;
            i+=1;
        }
        if (key[S] && i<MAXNOM){
            nomtemporaire[i]='S';
            key[S]=false;
            i+=1;
        }
        if (key[T] && i<MAXNOM){
            nomtemporaire[i]='T';
            key[T]=false;
            i+=1;
        }
        if (key[U] && i<MAXNOM){
            nomtemporaire[i]='U';
            key[U]=false;
            i+=1;
        }
        if (key[V] && i<MAXNOM){
            nomtemporaire[i]='V';
            key[V]=false;
            i+=1;
        }
        if (key[W] && i<MAXNOM){
            nomtemporaire[i]='W';
            key[W]=false;
            i+=1;
        }
        if (key[X] && i<MAXNOM){
            nomtemporaire[i]='X';
            key[X]=false;
            i+=1;
        }
        if (key[Y] && i<MAXNOM){
            nomtemporaire[i]='Y';
            key[Y]=false;
            i+=1;
        }
        if (key[Z] && i<MAXNOM){
            nomtemporaire[i]='Z';
            key[Z]=false;
            i+=1;
        }
        if (key[GAUCHE]==true){
            nomtemporaire[i]=0;
            i-=1;
            key[GAUCHE]=false;
        }
        if (key[ENTER] || key[ESCAPE]){
            fin=1;
            key[ENTER]=false;
            key[ESCAPE]=false;
        }
    }
}

void lire_sauvegarde(Personnage *p1, Personnage *p2, int *menu, int *entrerticket, ALLEGRO_FONT *texte1) {
    FILE *sauvegarde = NULL;
    sauvegarde = fopen("..\\Sauvegarde\\sauvegarde.txt", "r+");
    if (sauvegarde == NULL) {
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_textf(texte1, al_map_rgb(255, 255, 255), HAUTEUR/2, HAUTEUR/2, 0, "Probleme lors de la sauvegarde");
        al_flip_display();
        al_rest(2);
    }

    fscanf(sauvegarde, "%d %d %d %d %d %d", &(p1->score), &(p2->score), &(p1->tickets), &(p2->tickets), &menu, &entrerticket);
    fclose(sauvegarde);
    sauvegarde = NULL;


}

void ecrire_sauvegarde(Personnage *p1, Personnage *p2, int menu, int entrerticket, ALLEGRO_FONT *texte1) {
    FILE *sauvegardejoueur = NULL;

    sauvegardejoueur = fopen("..\\Sauvegarde\\sauvegarde.txt", "w+");
    if (sauvegardejoueur == NULL) {
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_textf(texte1, al_map_rgb(255, 255, 255), HAUTEUR/2, HAUTEUR/2, 0, "Probleme lors de la sauvegarde");
        al_flip_display();
        al_rest(2);
    }
    fprintf(sauvegardejoueur, "%d %d %d %d %d %d", p1->score, p2->score, p1->tickets, p2->tickets, menu, entrerticket);
    fclose(sauvegardejoueur);
    sauvegardejoueur = NULL;
}

void Sauvegardes(Personnage *p1, Personnage *p2, float *x,
                 ALLEGRO_EVENT event, ALLEGRO_FONT *texte1, ALLEGRO_EVENT_QUEUE *queue,
                 bool key[KEY_MAX], ALLEGRO_BITMAP *fond, int menu, int entrerticket) {

    int fin=0;
    ALLEGRO_COLOR couleur = al_map_rgb(100, 100, 100);


    while (fin!=1) {
        al_wait_for_event(queue, &event);
        al_draw_scaled_bitmap(fond, 0, 0, 1024, 653, *x, -500, 2048, 1306, 0);
        al_draw_filled_rectangle(300, 500, 1000, 600, couleur);///deuxieme
        al_draw_filled_rectangle(250, 350, 1050, 450, couleur);///premier
        al_draw_filled_rectangle(400, 200, 900, 300, couleur);///haut
        al_draw_filled_rectangle(150, 650, 1180, 750, couleur);///troisieme

        al_draw_textf(texte1, al_map_rgb(232, 140, 0), 470, 200, 0, "SAUVEGARDE");///haut
        al_draw_textf(texte1, al_map_rgb(232, 140, 0), 250, 350, 0, "ENTER -> Sauvegarder");///prem
        al_draw_textf(texte1, al_map_rgb(232, 140, 0), 375, 500, 0, "ESC -> Quitter");///deux
        al_draw_textf(texte1, al_map_rgb(232, 140, 0), 160, 650, 0, "P -> recuperer sauvegarde");///trois

        al_flip_display();
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            al_destroy_font(texte1);
            fin=1;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE: {
                    key[ESCAPE] = true;
                    break;
                }
                case ALLEGRO_KEY_ENTER: {
                    key[ENTER] = true;
                    break;
                }
                case ALLEGRO_KEY_P: {
                    key[P] = true;
                    break;
                }
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE: {
                    key[ESCAPE] = false;
                    break;
                }
                case ALLEGRO_KEY_ENTER: {
                    key[ENTER] = false;
                    break;
                }
                case ALLEGRO_KEY_P: {
                    key[P] = false;
                    break;
                }
            }
        }
        if (key[P] == true) {
            lire_sauvegarde(p1, p2, &menu, &entrerticket, texte1);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_textf(texte1, al_map_rgb(255, 255, 255), HAUTEUR/2, HAUTEUR/2, 0, "Recuperation de la sauvegarde");
            al_flip_display();
            al_rest(2);
            fin=1;
        }
        if (key[ENTER] == true) {
            ecrire_sauvegarde(p1, p2, menu, entrerticket, texte1);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_textf(texte1, al_map_rgb(255, 255, 255), 570, 200, 0, "Sauvegarde... ");
            al_flip_display();
            al_rest(2);
            fin=1;
        }
        if (key[ESCAPE] == true) {
            key[ESCAPE]=false;
            fin=1;
            key[ESCAPE] = false;
        }
        *x -= 0.15f;
        if (*x <= -750) { *x = 0; }
    }
}

int Entrertickets(int i, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *imageperso, Personnage *p1,
                  ALLEGRO_BITMAP *ticket, Personnage *p2) {
    ALLEGRO_BITMAP *stand = NULL;
    stand = al_load_bitmap("..\\image\\stand_ticket.png");
    al_clear_to_color(al_map_rgb(232, 140, 0));
    al_draw_scaled_bitmap(stand, 0, 0, 612, 612, 200, 0, 918, 918, 0);
    al_flip_display();
    al_rest(1);
    al_draw_filled_rectangle(300, 200, 500, 300, al_map_rgb(250, 250, 250));
    al_draw_text(texte, al_map_rgb(232, 140, 0), 350, 230, 0, "Bonjour");
    al_flip_display();
    al_rest(1.5);
    if (i != 1) {
        al_draw_filled_rectangle(330, 200, 1100, 300, al_map_rgb(250, 250, 250));
        al_draw_text(texte, al_map_rgb(232, 140, 0), 350, 230, 0, "Voila vos pokeball pour faire vos activités");
        al_flip_display();
        al_rest(5);
        al_destroy_bitmap(stand);
        Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *p1, *p2);

        al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 530, 675, 34, 48, 0);
        al_flip_display();
        ///////////////////ajouter animation
        if (p1->touractif == true) {
            p1->tickets = 5;
            p2->tickets = 5;
        }
        return 1;
    } else {
        al_draw_filled_rectangle(300, 200, 700, 300, al_map_rgb(250, 250, 250));
        al_draw_text(texte, al_map_rgb(232, 140, 0), 350, 230, 0, "Vous êtes déjà passé");
        al_flip_display();
        al_rest(1);
    }
    al_destroy_bitmap(stand);
    Attractions(fond, al_map_rgb(250, 250, 250), texte, ticket, *p1, *p2);

    al_draw_scaled_bitmap(imageperso, 0, 0, 67, 95, 530, 675, 34, 48, 0);
    al_flip_display();
    p1->x = 530, p1->y = 675;
    p2->x = 545, p2->y = 675;

}


void Attractions(ALLEGRO_BITMAP *fond, ALLEGRO_COLOR couleur, ALLEGRO_FONT *texte, ALLEGRO_BITMAP *ticket,
                 Personnage p1, Personnage p2) {
    al_draw_scaled_bitmap(fond, 0, 0, 1024, 653, 0, 0, LARGEUR, HAUTEUR, 0);
    al_draw_textf(texte, couleur, 0, 0, 0, "score: %d / %d", p1.score, p2.score);
    al_draw_scaled_bitmap(ticket, 0, 0, 542, 762, -30, 0, 135, 190, 0);
    al_draw_textf(texte, couleur, 70, 70, 0, " X %d / X %d", p1.tickets, p2.tickets);

    if ((p1.x <= LARGEUR / 3.55 && p1.x >= 240 && p1.y <= 730 && p1.y >= 620)&&(p1.touractif==true) ||
        (p2.x <= LARGEUR / 3.55 && p2.x >= 240 && p2.y <= 730 && p2.y >= 620)&&(p2.touractif==true)) {
        al_draw_circle(300, 680, 60, couleur, 2);
        al_draw_text(texte, couleur, 220, 580, 0, "peche canards");
    }
    if ((p1.x <= 590 && p1.x >= 470 && p1.y <= 730 && p1.y >= 620)&&(p1.touractif==true) ||
               (p2.x <= 590 && p2.x >= 470 && p2.y <= 730 && p2.y >= 620)&&(p2.touractif==true)) {
        al_draw_circle(550, 680, 60, couleur, 2);
        al_draw_text(texte, couleur, 500, 580, 0, "tickets");
    }
    if ((p1.x <= 530 && p1.x >= 400 && p1.y <= 230 && p1.y >= 120)&&(p1.touractif==true) ||
               (p2.x <= 530 && p2.x >= 400 && p2.y <= 230 && p2.y >= 120)&&(p2.touractif==true)) {
        al_draw_circle(500, 190, 60, couleur, 2);
        al_draw_text(texte, couleur, 410, 100, 0, "paris hippiques");
    }
    if ((p1.x <= 590 && p1.x >= 470 && p1.y <= 580 && p1.y >= 440) &&(p1.touractif==true)||
               (p2.x <= 590 && p2.x >= 470 && p2.y <= 580 && p2.y >= 440)&&(p2.touractif==true)) {
        al_draw_circle(550, 520, 60, couleur, 2);
        al_draw_text(texte, couleur, 480, 415, 0, "tir ballon");
    }
    if ((p1.x <= 680 && p1.x >= 570 && p1.y <= 380 && p1.y >= 220)&&(p1.touractif==true) ||
               (p2.x <= 680 && p2.x >= 570 && p2.y <= 380 && p2.y >= 220)&&(p2.touractif==true)) {
        al_draw_circle(640, 370, 60, couleur, 2);
        al_draw_text(texte, couleur, 580, 260, 0, "taupe la");
    }
    if ((p1.x <= 820 && p1.x >= 700 && p1.y <= 370 && p1.y >= 220)&&(p1.touractif==true) ||
               (p2.x <= 820 && p2.x >= 700 && p2.y <= 370 && p2.y >= 220)&&(p2.touractif==true)) {
        al_draw_circle(770, 370, 60, couleur, 2);
        al_draw_text(texte, couleur, 700, 260, 0, "flappy bird");
    }
    if ((p1.x <= 200 && p1.x >= 0 && p1.y <= 285 && p1.y >= 0)&&(p1.touractif==true) ||
             (p2.x <= 200 && p2.x >= 0 && p2.y <= 285 && p2.y >= 0)&&(p2.touractif==true)) {
        al_draw_circle(185, 270, 60, couleur, 2);
        al_draw_text(texte, couleur, 100, 170, 0, "Guitare Hero");
    }
    //////ajouter les autres
}


void
Avancerpersbas(ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *imageperso1, ALLEGRO_BITMAP *imageperso2, ALLEGRO_COLOR couleur,
               ALLEGRO_FONT *texte, ALLEGRO_BITMAP *ticket, Personnage *p1, Personnage *p2,
               ALLEGRO_BITMAP *imagepersoimmo1, ALLEGRO_BITMAP *imagepersoimmo2) {

    if (p1->touractif == true) {
        if ((p1->y >= 650 && p1->x <= 200) || (p1->y >= 700) || (p1->y >= 500 && p1->y <= 520 && p1->x >= 450) ||
            (p1->y >= 350 && p1->y <= 370 && p1->x >= 450) || (p1->y >= 200 && p1->y <= 220 && p1->x >= 450) ||
            (p1->y >= 350 && p1->y <= 370 && p1->x <= 400)) {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso1, 0, 0, 67, 95, p1->x, p1->y, 34, 48, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);
            al_flip_display();
        } else {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso1, 0, 0, 67, 95, p1->x, p1->y + 2, 34, 48, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);

            al_flip_display();
            p1->y += 2;
        }
    } else {
        if ((p2->y >= 650 && p2->x <= 200) || (p2->y >= 700) || (p2->y >= 500 && p2->y <= 520 && p2->x >= 450) ||
            (p2->y >= 350 && p2->y <= 370 && p2->x >= 450) || (p2->y >= 200 && p2->y <= 220 && p2->x >= 450) ||
            (p2->y >= 350 && p2->y <= 370 && p2->x <= 400)) {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo1, 0, 0, 67, 95, p1->x, p1->y, 34, 48, 0);

            al_flip_display();
        } else {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso2, 0, 0, 127, 147, p2->x, p2->y + 2, 50, 58, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo1, 0, 0, 67, 95, p1->x, p1->y, 34, 48, 0);

            al_flip_display();
            p2->y += 2;
        }
    }
}

void
Avancerpersohaut(ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *imageperso1, ALLEGRO_BITMAP *imageperso2, ALLEGRO_COLOR couleur,
                 ALLEGRO_FONT *texte, ALLEGRO_BITMAP *ticket, Personnage *p1, Personnage *p2,
                 ALLEGRO_BITMAP *imagepersoimmo1, ALLEGRO_BITMAP *imagepersoimmo2) {

    if (p1->touractif == true) {
        if ((p1->y >= 600 && p1->y <= 620 && p1->x <= 300) ||
            (p1->y >= 630 && p1->y <= 650 && p1->x <= 400 && p1->x >= 250) ||
            (p1->y >= 630 && p1->y <= 650 && p1->x >= 450) || (p1->y >= 450 && p1->y <= 470 && p1->x >= 450) ||
            (p1->y >= 300 && p1->y <= 320 && p1->x >= 450) ||
            (p1->y >= 300 && p1->y <= 320 && p1->x <= 405 && p1->x >= 200) ||
            (p1->y >= 150 && p1->y <= 170) || (p1->y >= 200 && p1->y <= 220 && p1->x <= 250)) {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso1, 0, 0, 117, 157, p1->x, p1->y, 34, 48, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);


            al_flip_display();
        } else {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso1, 0, 0, 117, 157, p1->x, p1->y - 2, 34, 48, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);

            al_flip_display();
            p1->y -= 2;
        }
    } else {
        if ((p2->y >= 600 && p2->y <= 620 && p2->x <= 300) ||
            (p2->y >= 630 && p2->y <= 650 && p2->x <= 400 && p2->x >= 250) ||
            (p2->y >= 630 && p2->y <= 650 && p2->x >= 450) || (p2->y >= 450 && p2->y <= 470 && p2->x >= 450) ||
            (p2->y >= 300 && p2->y <= 320 && p2->x >= 450) ||
            (p2->y >= 300 && p2->y <= 320 && p2->x <= 405 && p2->x >= 200) ||
            (p2->y >= 150 && p2->y <= 170) || (p2->y >= 200 && p2->y <= 220 && p2->x <= 250)) {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo1, 0, 0, 67, 95, p1->x, p1->y - 2, 34, 48, 0);

            al_flip_display();
        } else {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso2, 0, 0, 127, 147, p2->x, p2->y - 2, 50, 58, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo1, 0, 0, 67, 95, p1->x, p1->y, 34, 48, 0);

            al_flip_display();
            p2->y -= 2;
        }
    }

}

void Avancerpersodroite(ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *imageperso1, ALLEGRO_BITMAP *imageperso2,
                        ALLEGRO_COLOR couleur,
                        ALLEGRO_FONT *texte, ALLEGRO_BITMAP *ticket, Personnage *p1, Personnage *p2, bool key[KEY_MAX],
                        ALLEGRO_BITMAP *imagepersoimmo1, ALLEGRO_BITMAP *imagepersoimmo2) {

    if (p1->touractif == true) {
        if ((p1->x >= 780) || (p1->y >= 450 && p1->x >= 700) || (p1->y >= 520 && p1->y <= 640 && p1->x >= 450) ||
            (p1->y >= 355 && p1->y <= 465 && p1->x >= 450) ||
            (p1->y >= 210 && p1->y <= 317 && p1->x > 450) || (p1->y >= 600 && p1->y <= 640 && p1->x >= 230) ||
            (p1->y <= 315 && p1->x >= 190 && p1->x <= 210) || (p1->x >= 600 && p1->y > 600)) {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso1, 0, 0, 111, 159, p1->x, p1->y, 34, 48, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);


            if (p1->x >= 600 && p1->y > 600) {
                al_draw_text(al_load_ttf_font("..\\fonts\\pixel.ttf", 30, 0), couleur, 500, p1->y - 30, 0,
                             "je ne devrais pas m'aventurer");
                key[DROITE] = false;
            }
            al_flip_display();
        } else {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso1, 0, 0, 111, 159, p1->x + 2, p1->y, 34, 48, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);


            al_flip_display();
            p1->x += 2;
        }
    } else {
        if ((p2->x >= 780) || (p2->y >= 450 && p2->x >= 700) || (p2->y >= 520 && p2->y <= 640 && p2->x >= 450) ||
            (p2->y >= 355 && p2->y <= 465 && p2->x >= 450) ||
            (p2->y >= 210 && p2->y <= 317 && p2->x > 450) || (p2->y >= 600 && p2->y <= 640 && p2->x >= 230) ||
            (p2->y <= 315 && p2->x >= 190 && p2->x <= 210) || (p2->x >= 600 && p2->y > 600)) {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo1, 0, 0, 67, 95, p1->x, p1->y, 34, 48, 0);

            if (p2->x >= 600 && p2->y > 600) {
                al_draw_text(al_load_ttf_font("..\\fonts\\pixel.ttf", 30, 0), couleur, 500, p2->y - 30, 0,
                             "je ne devrais pas m'aventurer");
                key[DROITE] = false;
            }
            al_flip_display();
        } else {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso2, 0, 0, 127, 147, p2->x + 2, p2->y, 50, 58, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo1, 0, 0, 67, 95, p1->x, p1->y, 34, 48, 0);

            al_flip_display();
            p2->x += 2;
        }
    }
}

void Avancerpersogauche(ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *imageperso1, ALLEGRO_BITMAP *imageperso2,
                        ALLEGRO_COLOR couleur,
                        ALLEGRO_FONT *texte, ALLEGRO_BITMAP *ticket, Personnage *p1, Personnage *p2,
                        ALLEGRO_BITMAP *imagepersoimmo1, ALLEGRO_BITMAP *imagepersoimmo2) {
    if (p1->touractif == true) {
        if ((p1->x <= 135 && p1->y <= 370) || (p1->x <= 410 && p1->x >= 390 && p1->y < 315) ||
            (p1->x <= 410 && p1->x >= 390 && p1->y > 365 && p1->y < 650) ||
            (p1->x < 200 && p1->y > 660)) {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso1, 0, 0, 111, 165, p1->x, p1->y, 34, 48, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);

            al_flip_display();
        } else {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            ///
            al_draw_scaled_bitmap(imagepersoimmo2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);
            al_draw_scaled_bitmap(imageperso1, 0, 0, 111, 165, p1->x - 2, p1->y, 34, 48, 0);

            if (p1->x <= 120 && p1->y >= 600) {
                al_draw_text(al_load_ttf_font("..\\fonts\\pixel.ttf", 30, 0), couleur, p1->x - 20, p1->y - 20, 0,
                             "je me dirige vers la sortie");
            }
            al_flip_display();
            p1->x -= 2;
        }
    } else {
        if ((p2->x <= 135 && p2->y <= 370) || (p2->x <= 410 && p2->x >= 390 && p2->y < 315) ||
            (p2->x <= 410 && p2->x >= 390 && p2->y > 365 && p2->y < 650) ||
            (p2->x < 200 && p2->y > 660)) {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso2, 0, 0, 127, 147, p2->x, p2->y, 50, 58, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo1, 0, 0, 67, 95, p1->x, p1->y, 34, 48, 0);

            al_flip_display();
        } else {
            Attractions(fond, couleur, texte, ticket, *p1, *p2);
            al_draw_scaled_bitmap(imageperso2, 0, 0, 127, 147, p2->x - 2, p2->y, 50, 58, 0);
            ///
            al_draw_scaled_bitmap(imagepersoimmo1, 0, 0, 67, 95, p1->x, p1->y, 34, 48, 0);

            if (p2->x <= 120 && p2->y >= 600) {
                al_draw_text(al_load_ttf_font("..\\fonts\\pixel.ttf", 30, 0), couleur, p2->x - 20, p2->y - 20, 0,
                             "je me dirige vers la sortie");
            }
            al_flip_display();
            p2->x -= 2;
        }
    }
}