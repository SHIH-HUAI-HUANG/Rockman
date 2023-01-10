#include "resource.h"

void DrawMenu (Allegro *allegro)
{
    al_clear_to_color (al_map_rgb (0, 0, 0));
    DrawStar (NUM_STAR, allegro);
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 350, 1, "STAGE");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 420, 1, "RULE ");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 490, 1, "STORY");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 560, 1, "SCOREBOARD");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 630, 1, "EXIT");
    DrawArrowInMenu (allegro);
    DrawSaturn (allegro);
}

void MoveArrowInMenu (Allegro *allegro)
{
    al_get_keyboard_state(&allegro->keyboardState);
    if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_UP) )
    {
        allegro->menu.state--;
        al_set_sample_instance_playing(allegro->instance6, false); // button music
        al_set_sample_instance_playing(allegro->instance6, true); // button music
    }


    else if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_DOWN) )
    {
        allegro->menu.state++;
        al_set_sample_instance_playing(allegro->instance6, false); // button music
        al_set_sample_instance_playing(allegro->instance6, true); // button music
    }


    if (allegro->menu.state > 4)
        allegro->menu.state = 4;
    if (allegro->menu.state < 0)
        allegro->menu.state = 0;
}


void DrawArrowInMenu (Allegro *allegro)
{
    switch (allegro->menu.state)
    {
    case M_CHOOSE_STAGE:
        al_draw_bitmap(allegro->menu.icon_right, 100, 340, 0);
        break;

    case M_RULE:
        al_draw_bitmap(allegro->menu.icon_right, 100, 410, 0);
        break;

    case M_STORY:
        al_draw_bitmap(allegro->menu.icon_right, 100, 480, 0);
        break;

    case M_BOARD:
        al_draw_bitmap(allegro->menu.icon_right, 100, 550, 0);
        break;

    case M_EXIT:
        al_draw_bitmap(allegro->menu.icon_right, 100, 620, 0);
        break;

    }
}


void InitMenu (Allegro *allegro)
{
    allegro->menu.icon_right = al_load_bitmap ("./picture/icon_right.png");
    allegro->menu.saturn = al_load_bitmap ("./picture/saturn.png");

}


void EnterInMenu (Allegro *allegro, Rockman *rockman)
{
    al_get_keyboard_state(&allegro->keyboardState);
    if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_ENTER) )
    {
        al_set_sample_instance_playing(allegro->instance6, true); // button music
        switch (allegro->menu.state)
        {
        case M_CHOOSE_STAGE:
            allegro->STATE = STAGE;
            break;

        case M_RULE:
            allegro->STATE = RULE;
            InitRockmanInRule (rockman);
            break;

        case M_STORY:
            allegro->STATE = STORY;
            allegro->state_story = 0;
            allegro->time_story001 = 180;
            al_set_sample_instance_playing(allegro->instance8, false);  // turn off taiwan song
            break;

        case M_BOARD:
            allegro->STATE = SCOREBOARD;
            break;

        case M_EXIT:
            allegro->finish = true;
            break;
        }
    }
}

void DrawSaturn (Allegro *allegro)
{
    int range = allegro->FRAME%150;
    int x = 100;
    int y = -80;

    if ( 0 <= range && range < 15)
        al_draw_bitmap_region (allegro->menu.saturn, 0, 0, 500, 500, x, y, 0);

    else if ( 15 <= range && range < 30)
        al_draw_bitmap_region (allegro->menu.saturn, 500, 0, 500, 500, x, y, 0);

    else if ( 30 <= range && range < 45)
        al_draw_bitmap_region (allegro->menu.saturn, 1000, 0, 500, 500, x, y, 0);

    else if ( 45 <= range && range < 60)
        al_draw_bitmap_region (allegro->menu.saturn, 1500, 0, 500, 500, x, y, 0);

    else if ( 60 <= range && range < 75)
        al_draw_bitmap_region (allegro->menu.saturn, 2000, 0, 500, 500, x, y, 0);

    else if ( 75 <= range && range < 90)
        al_draw_bitmap_region (allegro->menu.saturn, 2500, 0, 500, 500, x, y, 0);

    else if ( 90 <= range && range < 105)
        al_draw_bitmap_region (allegro->menu.saturn, 3000, 0, 500, 500, x, y, 0);

    else if ( 105 <= range && range < 120)
        al_draw_bitmap_region (allegro->menu.saturn, 3500, 0, 500, 500, x, y, 0);

    else if ( 120 <= range && range < 135)
        al_draw_bitmap_region (allegro->menu.saturn, 4000, 0, 500, 500, x, y, 0);

    else if ( 135 <= range && range < 150)
        al_draw_bitmap_region (allegro->menu.saturn, 4500, 0, 500, 500, x, y, 0);
}



