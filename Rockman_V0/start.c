#include "resource.h"


void DrawRockmanInStart (Rockman *rockman, Allegro *allegro)
{
    int range = allegro->FRAME%32;
    int x = 340;
    int y = 250;

    if ( 0 <= range && range < 8)
        al_draw_bitmap_region (rockman->img, 125, 233, 101, 105, x, y, 0);

    else if ( 8 <= range && range < 16)
        al_draw_bitmap_region (rockman->img, 251, 233, 91, 105, x, y, 0);

    else if ( 16 <= range && range < 24)
        al_draw_bitmap_region (rockman->img, 352, 233, 105, 105, x, y, 0);

    else if ( 24 <= range && range < 32)
        al_draw_bitmap_region (rockman->img, 251, 233, 91, 105, x, y, 0);

}


void DrawTextInStart (Allegro *allegro)
{
    int range = allegro->FRAME%60;
    if ( 0 <= range && range < 40)
    {
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 600, 1, "PRESS ENTER TO START");
        al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 384, 650, 1, "LICENSED BY NINTENDO");
        al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 384, 675, 1, "SHIH-HUAI & JIA-LIN");
    }
}



void InitStart (Allegro *allegro)
{
    allegro->start.mark_megaman = al_load_bitmap ("./picture/mark_megaman.png");
    allegro->start.earth = al_load_bitmap ("./picture/earth.png");
}


void DrawStart (Rockman *rockman, Allegro *allegro)
{
    al_clear_to_color (al_map_rgb(0, 0, 0));
    al_draw_bitmap (allegro->start.mark_megaman, 190, 50, 0);
    DrawStar (NUM_STAR, allegro);
    DrawEarth (allegro);
    DrawRockmanInStart (rockman, allegro);
    DrawTextInStart (allegro);
}


void DrawEarth (Allegro *allegro)
{
    int range = allegro->FRAME%150;
    int x = 290;
    int y = 350;

    if ( 0 <= range && range < 15)
        al_draw_bitmap_region (allegro->start.earth, 0, 0, 200, 200, x, y, 0);

    else if ( 15 <= range && range < 30)
        al_draw_bitmap_region (allegro->start.earth, 200, 0, 200, 200, x, y, 0);

    else if ( 30 <= range && range < 45)
        al_draw_bitmap_region (allegro->start.earth, 400, 0, 200, 200, x, y, 0);

    else if ( 45 <= range && range < 60)
        al_draw_bitmap_region (allegro->start.earth, 600, 0, 200, 200, x, y, 0);

    else if ( 60 <= range && range < 75)
        al_draw_bitmap_region (allegro->start.earth, 800, 0, 200, 200, x, y, 0);

    else if ( 75 <= range && range < 90)
        al_draw_bitmap_region (allegro->start.earth, 1000, 0, 200, 200, x, y, 0);

    else if ( 90 <= range && range < 105)
        al_draw_bitmap_region (allegro->start.earth, 1200, 0, 200, 200, x, y, 0);

    else if ( 105 <= range && range < 120)
        al_draw_bitmap_region (allegro->start.earth, 1400, 0, 200, 200, x, y, 0);

    else if ( 120 <= range && range < 135)
        al_draw_bitmap_region (allegro->start.earth, 1600, 0, 200, 200, x, y, 0);

    else if ( 135 <= range && range < 150)
        al_draw_bitmap_region (allegro->start.earth, 1800, 0, 200, 200, x, y, 0);

}


void InitStar (int number, Allegro *allegro)
{
    for (int i = 0; i < number; i++)
    {
        allegro->star[i].x = rand()%WINDOWS_W;
        allegro->star[i].y = rand()%WINDOWS_H;
        allegro->star[i].r = rand()%3 + 1;
    }
}


void DrawStar (int number, Allegro *allegro)
{
    int range = allegro->FRAME%60;
    int range_star = allegro->FRAME%120;
    for (int i = 0; i < number; i++)
    {
        if ( 0 <= range && range < 50)
            al_draw_filled_circle (allegro->star[i].x, allegro->star[i].y, allegro->star[i].r, al_map_rgb(255, 255, 255));
    }
    if ( 115 <= range_star && range_star < 120)
        InitStar (NUM_STAR, allegro);
}
