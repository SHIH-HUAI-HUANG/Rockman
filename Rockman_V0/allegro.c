#include "resource.h"


/** Function : Memery allocation for struct of Allegro */
Allegro *CallocAllegro()
{
    Allegro *addr = (Allegro *)calloc(1, sizeof(Allegro));
    return addr;
}


/** Function : Initialize all basic function */
void AllegroDriverInit(Allegro *allegro)
{
    /* first, set up Allegro and the graphics mode */
    al_init();             // initialize Allegro
    al_install_keyboard(); // install the keyboard for Allegro to use
    al_init_image_addon();
    al_install_audio();     // install sound driver
    al_init_acodec_addon();
    al_install_mouse();
    al_init_font_addon(); // install font addons
    al_init_ttf_addon();  // TureType Font addon also support .ttc
    al_init_native_dialog_addon();
    al_init_primitives_addon();
    //al_reserve_samples(2);


    allegro->display = al_create_display(WINDOWS_W, WINDOWS_H);
    al_set_window_title(allegro->display, " Rockman ");
    al_set_window_position(allegro->display, 780, 220);

    /* Envent queue **/
    allegro->timer = al_create_timer(1.0 / FPS);
    allegro->event_queue = al_create_event_queue();
    al_register_event_source(allegro->event_queue, al_get_mouse_event_source());
    al_register_event_source(allegro->event_queue, al_get_display_event_source(allegro->display));
    al_register_event_source(allegro->event_queue, al_get_keyboard_event_source());
    al_register_event_source(allegro->event_queue, al_get_timer_event_source(allegro->timer));
    al_start_timer(allegro->timer);

    allegro->finish = false;
    allegro->FRAME = 0;
    allegro->STATE = MENU;
}



void EventCheck(Allegro *allegro, Rockman *rockman)
{
    if (!al_is_event_queue_empty(allegro->event_queue))
    {
        while (al_get_next_event(allegro->event_queue, &allegro->events))
        {
            switch (allegro->events.type)
            {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                allegro->finish = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN: /** key down */
                al_get_keyboard_state(&allegro->keyboardState);
                switch (allegro->STATE)
                {
                case MENU:
                    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_ENTER) )
                        allegro->STATE = BOSS_1;
                    break;

                case RULE:
                    break;

                case BOSS_1:
                    al_clear_to_color (al_map_rgb (0, 0, 0));

                    break;

                }
                break;

            case ALLEGRO_EVENT_KEY_UP:
                rockman->state = STAND;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                break;

            case ALLEGRO_EVENT_TIMER: /** timer */
                allegro->FRAME++; // count the frame

                switch (allegro->STATE)
                {
                case MENU:
                    al_clear_to_color (al_map_rgb (240, 230, 140));

                    break;

                case RULE:
                    break;

                case BOSS_1:
                    MoveRockmanInBoss (rockman, allegro);
                    al_clear_to_color (al_map_rgb (0, 0, 0));
                    DrawRockman (rockman, allegro);
                    break;

                }


                break;
            }
        }
    }
}



