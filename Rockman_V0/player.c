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
    rockman->HP = 10;


    for (int i = 0; i < NUM_BULLET; i++)
    {
        rockman->bullet[i].activity = false;
    }

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
            al_draw_bitmap_region (rockman->img, 6, 3, 74, 105, rockman->x, rockman->y, rockman->direction);

        else if ( 100 <= range_stand && range_stand < 120)
            al_draw_bitmap_region (rockman->img, 122, 3, 73, 105, rockman->x, rockman->y, rockman->direction);
        break;

    case RUN_RIGHT:
        if ( 0 <= range && range < 8)
            al_draw_bitmap_region (rockman->img, 125, 233, 101, 105, rockman->x, rockman->y, rockman->direction);

        else if ( 8 <= range && range < 16)
            al_draw_bitmap_region (rockman->img, 251, 233, 91, 105, rockman->x, rockman->y, rockman->direction);

        else if ( 16 <= range && range < 24)
            al_draw_bitmap_region (rockman->img, 352, 233, 105, 105, rockman->x, rockman->y, rockman->direction);

        else if ( 24 <= range && range < 32)
            al_draw_bitmap_region (rockman->img, 251, 233, 91, 105, rockman->x, rockman->y, rockman->direction);
        break;

    case RUN_LEFT:
        if ( 0 <= range && range < 8)
            al_draw_bitmap_region (rockman->img, 125, 233, 101, 105, rockman->x, rockman->y, rockman->direction);

        else if ( 8 <= range && range < 16)
            al_draw_bitmap_region (rockman->img, 251, 233, 91, 105, rockman->x, rockman->y, rockman->direction);

        else if ( 16 <= range && range < 24)
            al_draw_bitmap_region (rockman->img, 352, 233, 105, 105, rockman->x, rockman->y, rockman->direction);

        else if ( 24 <= range && range < 32)
            al_draw_bitmap_region (rockman->img, 251, 233, 91, 105, rockman->x, rockman->y, rockman->direction);
        break;

    case JUMP:
        al_draw_bitmap_region (rockman->img, 0, 233, 101, 105, rockman->x, rockman->y, rockman->direction);
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


void DrawRockmanHP (Rockman *rockman)
{
    for (int i = 0; i < rockman->HP; i++)
    {
        al_draw_filled_rectangle (10, 100 - (i*7), 60, 105 - (i*7), al_map_rgb(255, 250, 0));
    }
  al_draw_filled_rectangle (500, 500 , 550, 550, al_map_rgb(255, 250, 0));
}

