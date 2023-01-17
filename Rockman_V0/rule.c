#include "resource.h"


void DrawRule (Allegro *allegro, Rockman *rockman)
{
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 50, 1, "RULE");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 650, 50, 0, "Back");
    DrawKeyboardIcon (allegro);
}


void DrawKeyboardIcon (Allegro *allegro)
{
    al_get_keyboard_state(&allegro->keyboardState);
    al_draw_bitmap (allegro->rule.left, 102, 200, 0);
    al_draw_bitmap (allegro->rule.right, 222, 200, 0);
    al_draw_bitmap (allegro->rule.up, 162, 140, 0);
    al_draw_bitmap (allegro->rule.space, 486, 200, 0);

    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_LEFT) )
        al_draw_bitmap (allegro->rule.left_light, 102, 200, 0);
    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_RIGHT) )
        al_draw_bitmap (allegro->rule.right_light, 222, 200, 0);
    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_UP) )
        al_draw_bitmap (allegro->rule.up_light, 162, 140, 0);
    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_SPACE) )
        al_draw_bitmap (allegro->rule.space_light, 486, 200, 0);
}



void InitRockmanInRule (Rockman *rockman)
{
    rockman->x = 350;
    rockman->y = 500;
    rockman->jump_time = 0;
}
