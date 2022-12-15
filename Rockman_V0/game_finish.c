#include "resource.h"
/**
when the game over, show player win/lose.
And press enter to continue.
*/


void DrawGameFinish (Allegro *allegro, Rockman *rockman)
{
    al_clear_to_color (al_map_rgb (255, 255, 255));
    DrawContinue (allegro);

    if (rockman->HP <= 0)
        al_draw_textf(allegro->font_24, al_map_rgb(0, 0, 0), 390, 400, 1, "Loser");
    else if (rockman->HP > 0)
        al_draw_textf(allegro->font_24, al_map_rgb(0, 0, 0), 390, 400, 1, "Pass");

    al_get_keyboard_state(&allegro->keyboardState);
    if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_ENTER) )
        allegro->STATE = START;
}


void DrawContinue (Allegro *allegro)
{
    int range = allegro->FRAME%60;
    if ( 0 <= range && range < 40)
        al_draw_textf(allegro->font_24, al_map_rgb(0, 0, 0), 390, 600, 1, "PRESS ENTER TO CONTINUE");

}


