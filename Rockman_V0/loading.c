#include "resource.h"

void DrawLoading (Allegro *allegro)
{
    al_clear_to_color (al_map_rgb(0, 0, 0));
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 300, 350, 0, "LOADING");
    DrawProgressBar(allegro);
}


void DrawProgressBar (Allegro *allegro)
{
    int range = allegro->FRAME%80;

    if ( 0 <= range && range < 20)
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 420, 350, 0, ".");
    else  if ( 20 <= range && range < 40)
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 420, 350, 0, ". .");
    else if ( 40 <= range && range < 60)
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 420, 350, 0, ". . .");
    else if ( 60 <= range && range < 80)
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 420, 350, 0, ". . . .");
}


void LoadingFinish (Allegro *allegro, Rockman *rockman)
{
    int time = 300; // the pass time
    if (allegro->FRAME >= allegro->frame_flag + time)
    {
        allegro->STATE = CONTINUE;
        if (rockman->HP > 0)
            al_set_sample_instance_playing(allegro->instance5, true); // open game music for win
    }
}
