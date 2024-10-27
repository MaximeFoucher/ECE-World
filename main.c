#include "src/manege.h"
#include "src/peche_canards/canard.h"
#include "src/tir_ballon/tireballon.h"
#include "src/paris/paris_hippiques.h"
#include "src/Taupe/taupe.h"
#include "src/flappy/flappy.h"
#include "src/tableauscore/tableauscore.h"
#include"src/Snake/snake.h"
#include "src/guitare/guitare.h"

///afficher tableau classment
///faire sauvegarde

int main() {
    srand(time(NULL));
    ///////
    bool verif_tickets_start1 = true;
    bool verif_tickets_start2 = true;
    int fin = 0;
    int entrerticket = 0;
    int menu = -1;
    int nom=0;
    ////////coordonées
    Personnage p1;
    Personnage p2;
    p1.x = 5, p1.y = 625, p1.score = 0, p1.tickets = 5;
    p2.x = 5, p2.y = 635, p2.score = 0, p2.tickets = 5;
    p1.touractif = true;
    p2.touractif=false;

    /*
    p1.tickets = 5;
    p2.tickets = 5;
    */

    /////////////les init
    assert(al_init());
    al_init_primitives_addon();
    al_init_font_addon();
    assert(al_init_ttf_addon());
    al_init_image_addon();
    assert(al_install_keyboard());
    assert(al_install_mouse());
    al_install_audio();
    al_init_acodec_addon();
    al_init_native_dialog_addon();


    /////////////pointeurs
    ALLEGRO_DISPLAY *screen = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_BITMAP *fond = NULL;
    ALLEGRO_BITMAP* clavier = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP *persoimmobileface = NULL;
    ALLEGRO_BITMAP *persoimmobiledroite = NULL;
    ALLEGRO_BITMAP *persoimmobilegauche = NULL;
    ALLEGRO_BITMAP *persoimmobiledos = NULL;

    ALLEGRO_BITMAP *persoimmobile2face = NULL;
    ALLEGRO_BITMAP *persoimmobile2droite = NULL;
    ALLEGRO_BITMAP *persoimmobile2gauche = NULL;
    ALLEGRO_BITMAP *persoimmobile2dos = NULL;

    ALLEGRO_FONT *texte = NULL;
    ALLEGRO_BITMAP *ticket = NULL;
    ALLEGRO_KEYBOARD_STATE keybord_state;
    ALLEGRO_MOUSE_STATE mouse_state;



    /////////texte
    texte = al_load_ttf_font("..\\fonts\\pixel.ttf", 40, 0);
    assert(texte);

    ///audio
    ALLEGRO_SAMPLE *menu_song=NULL;
    menu_song= al_load_sample("..\\audio\\song_menu.ogg");
    //ALLEGRO_SAMPLE_ID *menu_song2=NULL;
    //menu_song2= al_load_sample("..\\audio\\song_menu.ogg");

    //////screen
    screen = al_create_display(LARGEUR, HAUTEUR);
    assert(screen);
    al_flip_display();
    fond = al_load_bitmap("..\\image\\pokemon-map.png");
    ticket = al_load_bitmap("..\\image\\carte.png");

    clavier = al_load_bitmap("..\\image\\clavier1png.png");

    persoimmobileface = al_load_bitmap("..\\image\\immobileface1.png");
    persoimmobiledos = al_load_bitmap("..\\image\\dos.png");
    persoimmobiledroite = al_load_bitmap("..\\image\\droite.png");
    persoimmobilegauche = al_load_bitmap("..\\image\\gauche.png");

    persoimmobile2face = al_load_bitmap("..\\image\\perso2face.png");
    persoimmobile2dos = al_load_bitmap("..\\image\\perso2dos.png");
    persoimmobile2droite = al_load_bitmap("..\\image\\perso2droit.png");
    persoimmobile2gauche = al_load_bitmap("..\\image\\perso2gauche.png");

    al_flip_display();
    bool key[KEY_MAX] = {false};

    ////////queue et timer
    timer = al_create_timer(1.0 / 100);
    queue = al_create_event_queue();

    al_register_event_source(queue, al_get_display_event_source(screen));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    al_start_timer(timer);

    //al_play_sample(menu_song,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);

    while (fin != 1) {

        al_wait_for_event(queue, &event);
        al_get_keyboard_state(&keybord_state);
        al_get_mouse_state(&mouse_state);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            fin = 1;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_S:
                case ALLEGRO_KEY_DOWN:
                    key[BAS] = true;
                    break;
                case ALLEGRO_KEY_Z:
                case ALLEGRO_KEY_UP :
                    key[HAUT] = true;
                    break;
                case ALLEGRO_KEY_D:
                case ALLEGRO_KEY_RIGHT:
                    key[DROITE] = true;
                    break;
                case ALLEGRO_KEY_Q:
                case ALLEGRO_KEY_LEFT :
                    key[GAUCHE] = true;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    key[ESCAPE] = true;
                    break;
                case ALLEGRO_KEY_ENTER:
                    key[ENTER] = true;
                    break;
                case ALLEGRO_KEY_P:
                    key[P] = true;
                    break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_S:
                case ALLEGRO_KEY_DOWN:
                    key[BAS] = false;
                    break;
                case ALLEGRO_KEY_Z:
                case ALLEGRO_KEY_UP:
                    key[HAUT] = false;
                    break;
                case ALLEGRO_KEY_Q:
                case ALLEGRO_KEY_LEFT:
                    key[GAUCHE] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                case ALLEGRO_KEY_D:
                    key[DROITE] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    key[ESCAPE] = false;
                    break;
                case ALLEGRO_KEY_ENTER:
                    key[ENTER] = false;
                    break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {
            if (menu == -1) {
                menu = Menu(fond, clavier, texte, queue, key, ticket, &p1, persoimmobileface, &p2, persoimmobile2face,
                            menu, entrerticket, &nom);
                if (menu == 1) {
                    fin = 1;
                }
            }
            if (key[ESCAPE]) {
                //al_stop_sample(menu);
                key[ESCAPE] = false;
                fin=Afficherscore(queue, key, fond, &p1, ticket, texte, persoimmobileface, &p2, persoimmobile2face);
            }
            if (key[BAS]) {
                Avancerpersbas(fond, persoimmobileface, persoimmobile2face, al_map_rgb(250, 250, 250), texte, ticket,
                               &p1, &p2, persoimmobileface, persoimmobile2face);
            }
            if (key[HAUT]) {
                Avancerpersohaut(fond, persoimmobiledos, persoimmobile2dos, al_map_rgb(250, 250, 250), texte, ticket,
                                 &p1, &p2, persoimmobileface, persoimmobile2face);
            }
            if (key[DROITE]) {
                Avancerpersodroite(fond, persoimmobiledroite, persoimmobile2droite, al_map_rgb(250, 250, 250), texte,
                                   ticket, &p1, &p2, key, persoimmobileface, persoimmobile2face);
            }
            if (key[GAUCHE]) {
                Avancerpersogauche(fond, persoimmobilegauche, persoimmobile2gauche, al_map_rgb(250, 250, 250), texte,
                                   ticket, &p1, &p2, persoimmobileface, persoimmobile2face);
            }
            if (p1.x < 0 || p2.x < 0) {
                key[GAUCHE] = false;
                fin = Menu(fond, clavier, texte, queue, key, ticket, &p1, persoimmobileface, &p2, persoimmobile2face,
                           menu, entrerticket, &nom);
            }
            if ((((p1.x <= 360 && p1.x >= 240 && p1.y <= 730 && p1.y >= 620) && key[ENTER] && p1.touractif==true ) ||
            ((p2.x <= 360 && p2.x >= 240 && p2.y <= 730 && p2.y >= 620) && key[ENTER] && p2.touractif==true)) && (p1.tickets!=0)){
                key[ENTER] = false;
                ////CANARD
                al_destroy_sample(menu_song);
                Canard(queue, key, fond, &p1, ticket, texte, persoimmobileface, &p2);
            }
            if ((((p1.x <= 590 && p1.x >= 470 && p1.y <= 730 && p1.y >= 620) && key[ENTER] && p1.touractif==true) ||
            ((p2.x <= 590 && p2.x >= 470 && p2.y <= 730 && p2.y >= 620) && key[ENTER] && p2.touractif==true))) {
                key[ENTER] = false;
                ///ticket debut
                al_play_sample(menu_song,0,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                al_destroy_sample(menu_song);
                entrerticket += Entrertickets(entrerticket, texte, fond, persoimmobileface, &p1, ticket, &p2);
                verif_tickets_start1 = false;
                verif_tickets_start2 = false;
            }
            if ((((p1.x <= 530 && p1.x >= 400 && p1.y <= 230 && p1.y >= 120) && key[ENTER] && p1.touractif==true) ||
            ((p2.x <= 530 && p2.x >= 400 && p2.y <= 230 && p2.y >= 120) && key[ENTER] && p2.touractif==true)) && (p1.tickets!=0)) {
                key[ENTER] = false;
                ///paris hippiques
                al_play_sample(menu_song,0,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                al_destroy_sample(menu_song);
                EntrerParisHippiques(queue, texte, fond, persoimmobileface, &p1, &p2, ticket);
            }
            if ((((p1.x <= 820 && p1.x >= 700 && p1.y <= 370 && p1.y >= 220) && key[ENTER] && p1.touractif==true) ||
            ((p2.x <= 820 && p2.x >= 700 && p2.y <= 370 && p2.y >= 220)) && key[ENTER] && p2.touractif==true) && (p1.tickets!=0)) {
                key[ENTER] = false;
                ///flappy bird
                flappy_bird(queue, texte, fond, persoimmobileface, &p1, &p2, ticket);
            }
            if ((((p1.x <= 590 && p1.x >= 470 && p1.y <= 580 && p1.y >= 440) && key[ENTER] && p1.touractif==true) ||
            ((p2.x <= 590 && p2.x >= 470 && p2.y <= 580 && p2.y >= 440) && key[ENTER] && p2.touractif==true)) && (p1.tickets!=0)) {
                key[ENTER] = false;
                ///tir ballon
                al_play_sample(menu_song,0,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                al_destroy_sample(menu_song);
                Tirballon(queue, mouse_state, screen, texte, fond, ticket, persoimmobileface, &p1, &p2, key);
            }
            if ((((p1.x <= 680 && p1.x >= 570 && p1.y <= 380 && p1.y >= 220) && key[ENTER]) &&p1.touractif==true||
            ((p2.x <= 680 && p2.x >= 570 && p2.y <= 380 && p2.y >= 220) && key[ENTER] && p2.touractif==true)) && (p1.tickets!=0)){
                key[ENTER] = false;
                al_destroy_sample(menu_song);
                Taupe_la(queue, key, fond, &p1, ticket, texte, persoimmobileface,&p2);
                /////taupe la
            }
            if ((((p1.x <= 200 && p1.x >= 0 && p1.y <= 285 && p1.y >= 0) && key[ENTER]) &&p1.touractif==true||
                ((p2.x <= 200 && p2.x >= 0 && p2.y <= 285 && p2.y >= 0) && key[ENTER] && p2.touractif==true)) && (p1.tickets!=0)){
                key[ENTER] = false;
                 al_destroy_sample(menu_song);
                 GuitareHeroJoueur1(key, screen, event, fond, &p1, ticket, texte, persoimmobileface,&p2);            /////Guitar Hero
            }
            if (p1.tickets == 0 && p2.tickets!=0 && verif_tickets_start1==false && verif_tickets_start2==false){
            ///rajouter une condition sinon des le depart ca le finit (peut etre un qui à 0 ticket et l'autre qui en a pas zéro)
            ///changer ducoup cette valeur pour pas que ca tourne en boucle
            ///fin
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_textf(texte, al_map_rgb(250, 250, 250), 260, 350, 0, "JOUEUR 1 GAGNE");
                al_flip_display();
                menu=-1;
                al_rest(4);
            }
            if (p1.tickets != 0 && p2.tickets==0 && verif_tickets_start1==false && verif_tickets_start2==false){
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_textf(texte, al_map_rgb(250, 250, 250), 260, 350, 0, "JOUEUR 2 GAGNE");
                al_flip_display();
                menu=-1;
                al_rest(4);
            }
        }
    }
    al_destroy_event_queue(queue);
    al_destroy_display(screen);
    al_destroy_timer(timer);
    al_destroy_bitmap(fond);
    al_destroy_bitmap(persoimmobileface);
    al_destroy_bitmap(persoimmobile2face);
    al_destroy_bitmap(persoimmobiledos);
    al_destroy_bitmap(persoimmobile2dos);
    al_destroy_bitmap(persoimmobile2gauche);
    al_destroy_bitmap(persoimmobile2droite);
    al_destroy_bitmap(persoimmobilegauche);
    al_destroy_bitmap(persoimmobiledroite);
    return 0;
}
