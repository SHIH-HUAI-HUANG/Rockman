#include "resource.h"



/** Function : Memery allocation for struct of Rockman */
Rockman *CallocRockman()
{
    Rockman *addr = (Rockman *)calloc(1, sizeof(Rockman));
    return addr;
}



void InitRockman (Rockman *rockman)
{
    rockman->x = 300;
    rockman->y = 400;
    rockman->speed = SPEED;
    rockman->state = STAND;
    rockman->jump_time = -1;


    rockman->direction = false;
    rockman->img = al_load_bitmap ("./picture/rockman.png");

}


void DrawRockman (Rockman *rockman, Allegro *allegro)
{
    int range = allegro->FRAME%32;
    int range_stand = allegro->FRAME%120;

    switch (rockman->state)
    {
    case STAND:
        if ( 0 <= range_stand && range_stand < 100)
            al_draw_bitmap_region (rockman->img, 11, 40, 123, 140, rockman->x, rockman->y, rockman->direction);

        else if ( 100 <= range_stand && range_stand < 120)
            al_draw_bitmap_region (rockman->img, 203, 40, 123, 140, rockman->x, rockman->y, rockman->direction);
        break;

    case RUN_RIGHT:
        if ( 0 <= range && range < 8)
            al_draw_bitmap_region (rockman->img, 17, 232, 140, 140, rockman->x, rockman->y, rockman->direction);

        else if ( 8 <= range && range < 16)
            al_draw_bitmap_region (rockman->img, 226, 232, 94, 140, rockman->x, rockman->y, rockman->direction);

        else if ( 16 <= range && range < 24)
            al_draw_bitmap_region (rockman->img, 395, 232, 123, 140, rockman->x, rockman->y, rockman->direction);

        else if ( 24 <= range && range < 32)
            al_draw_bitmap_region (rockman->img, 226, 232, 94, 140, rockman->x, rockman->y, rockman->direction);
        break;

    case RUN_LEFT:
        if ( 0 <= range && range < 8)
            al_draw_bitmap_region (rockman->img, 17, 232, 140, 140, rockman->x, rockman->y, rockman->direction);

        else if ( 8 <= range && range < 16)
            al_draw_bitmap_region (rockman->img, 226, 232, 94, 140, rockman->x, rockman->y, rockman->direction);

        else if ( 16 <= range && range < 24)
            al_draw_bitmap_region (rockman->img, 395, 232, 123, 140, rockman->x, rockman->y, rockman->direction);

        else if ( 24 <= range && range < 32)
            al_draw_bitmap_region (rockman->img, 226, 232, 94, 140, rockman->x, rockman->y, rockman->direction);
        break;

    case JUMP:
        al_draw_bitmap_region (rockman->img, 0, 389, 169, 175, rockman->x, rockman->y, rockman->direction);
        break;

    }
}


void MoveRockmanInBoss(Rockman *rockman, Allegro *allegro)
{
    al_get_keyboard_state(&allegro->keyboardState);

    if (rockman->state != JUMP)
    {
        if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_RIGHT))
        {
            rockman->x = rockman->x + rockman->speed;
            rockman->state = RUN_RIGHT;
            rockman->direction = false;
        }


        else if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_LEFT))
        {
            rockman->x = rockman->x - rockman->speed;
            rockman->state = RUN_LEFT;
            rockman->direction = true;
        }


        if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_UP))
        {
            rockman->state = JUMP;
            rockman->jump_time = JUMP_TIME;
        }
    }


}


