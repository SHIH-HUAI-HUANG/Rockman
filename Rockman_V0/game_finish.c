#include "resource.h"
/**
when the game over, show player win/lose.
And press enter to continue.
*/


void DrawGameFinish (Allegro *allegro, Rockman *rockman)
{
    if (rockman->HP <= 0)
    {
        al_draw_bitmap (allegro->defeat, 0, 100, 0);
        DrawContinue (allegro);
    }

    else if (rockman->HP > 0)
    {
        al_draw_bitmap (allegro->victory, 0, 0, 0);
        al_draw_textf(allegro->font_96, al_map_rgb(255, 255, 255), 200, 300, 1, "Pass !!");
        DrawContinue (allegro);
    }

    al_get_keyboard_state(&allegro->keyboardState);
    if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_ENTER) )
    {
        allegro->STATE = MENU;
        al_set_sample_instance_playing(allegro->instance5, false);
        al_set_sample_instance_playing(allegro->instance8, true);  // turn on taiwan song
    }
}


void DrawContinue (Allegro *allegro)
{
    int range = allegro->FRAME%60;
    if ( 0 <= range && range < 40)
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 390, 600, 1, "PRESS ENTER TO CONTINUE");

}


