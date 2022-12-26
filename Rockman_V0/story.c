#include "resource.h"


void DrawStory (Allegro *allegro)
{
    al_clear_to_color (al_map_rgb (0, 0, 0));
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 650, 50, 0, "Back");

    if (allegro->pass_stage1 && allegro->pass_stage2 && allegro->pass_stage3)
    {
        AnimePassStory (allegro);
        DrawPass (allegro);
    }
    else
    {
        DrawNotPass (allegro);
    }
}



void DrawNotPass (Allegro *allegro)
{
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 400, 1, "THE FORCES OF EVIL ARE STILL SPREADING !!");
}


void DrawPass (Allegro *allegro)
{

    switch (allegro->state_story)
    {
    case 0:
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 400, 1, "ROCKMAN HAS ENDED THE EVIL");
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 450, 1, "DOMINATION OF JOHN WU AND");
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 500, 1, "RESTORE THE WORLD TO PEACE.");
        break;

    case 1:
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 400, 1, "HOWEVER, THE NEVER ENDING");
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 450, 1, "BSTTLE CONTINUES UNTIL ALL");
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 500, 1, "DESTRUCTIVE FORCES ARE DEFEATED.");
        break;

    case 2:
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 400, 1, "FIGHT, ROCKMAN !");
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 450, 1, "FOR EVERLASTING PEACE !");
        break;
    }
}



void AnimePassStory (Allegro *allegro)
{
    switch (allegro->state_story)
    {
    case 0:
        allegro->time_story001--;
        if (allegro->time_story001 < 0)
        {
            allegro->state_story = 1;
            allegro->time_story002 = 300;
        }
        break;

    case 1:
        allegro->time_story002--;
        if (allegro->time_story002 < 0)
        {
            allegro->state_story = 2;
            allegro->time_story003 = 300;
        }
        break;

    case 2:
        allegro->time_story003--;
        if (allegro->time_story003 < 0)
        {
            allegro->state_story = 0;
            allegro->time_story001 = 300;
        }
        break;
    }
}
