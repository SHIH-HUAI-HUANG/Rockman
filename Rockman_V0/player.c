#include "resource.h"



/** Function : Memery allocation for struct of Rockman */
Rockman *CallocRockman()
{
    Rockman *addr = (Rockman *)calloc(1, sizeof(Rockman));
    return addr;
}



void InitRockman (Rockman *rockman)
{
    rockman->x = 365;
    rockman->y = 400;
    rockman->speed = SPEED;
    rockman->state = STAND;
    rockman->jump_time = -1;
    rockman->HP = 10;
    rockman->record_HP = 10;


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
    int range_hurt = allegro->FRAME%40;

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
        al_draw_bitmap_region (rockman->img, 0, 233, 101, 105, rockman->x, rockman->y + 20, rockman->direction);
        break;

    case ATTACK:
        al_draw_bitmap_region (rockman->img, 467, 118, 109, 105, rockman->x, rockman->y, rockman->direction);
        break;

    case HURT:
        if ( 0 <= range_hurt && range_hurt < 20)
            al_draw_bitmap_region (rockman->img, 118, 352, 100, 105, rockman->x, rockman->y, rockman->direction);

        else if ( 20 <= range_hurt && range_hurt < 40)
            al_draw_bitmap_region (rockman->img, 233, 352, 100, 105, rockman->x, rockman->y, rockman->direction);
        break;
    }
}



void MoveRockmanInBoss(Rockman *rockman, Allegro *allegro)
{
    al_get_keyboard_state(&allegro->keyboardState);

    if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_RIGHT))
    {
        rockman->x = rockman->x + rockman->speed;
        rockman->direction = false;
    }

    else if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_LEFT))
    {
        rockman->x = rockman->x - rockman->speed;
        rockman->direction = true;
    }
}



void RockmanStateInBoss (Rockman *rockman, Allegro *allegro)
{
    al_get_keyboard_state(&allegro->keyboardState);

    if (rockman->state != JUMP && rockman->state != ATTACK)
    {
        if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_RIGHT))
        {
            rockman->state = RUN_RIGHT;
            rockman->direction = false;
        }


        else if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_LEFT))
        {
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



void RockmanJumpInBoss (Rockman *rockman, Allegro *allegro)
{
    if (rockman->jump_time > JUMP_TIME/2)
    {
        rockman->y = rockman->y - 4;
        rockman->jump_time--;
    }

    else if ( 0 < rockman->jump_time && rockman->jump_time <= JUMP_TIME/2 )
    {
        rockman->y = rockman->y + 4;
        rockman->jump_time--;
    }

    else if (rockman->jump_time <= 0)
        rockman->state = STAND;

    /* if (allegro->matrix_map[rockman->y + 106][rockman->x + abs(allegro->map.x)] == 0)
      rockman->jump_time = 0;*/
}



void DrawRockmanHP (Rockman *rockman)
{
    al_draw_filled_rectangle (45, 126, 105, 203, al_map_rgb(0, 0, 0));
    for (int i = 0; i < rockman->HP; i++)
    {
        al_draw_filled_rectangle (50, 193 - (i*7), 100, 198 - (i*7), al_map_rgb(250, 250, 210));
    }
}



void CheckAlive (Rockman *rockman, Allegro *allegro)
{
    if (rockman->HP <= 0)
    {
        allegro->STATE = LOADING;
        allegro->frame_flag = allegro->FRAME;
        al_set_sample_instance_playing(allegro->instance1, false); // close game music
        al_set_sample_instance_playing(allegro->instance2, false); // close game music
        al_set_sample_instance_playing(allegro->instance3, false); // close game music
        al_set_sample_instance_playing(allegro->instance4, false); // close game music
    }
}



void LimitRockmanInBoss (Rockman *rockman)
{
    if (rockman->x < 0)
        rockman->x = 0;
    if (rockman->x > 678)
        rockman->x = 678;
}


// Function : rockman suffer damage, he change his action.
void RockmanSufferDamage (Rockman *rockman)
{
    if (rockman->HP < rockman->record_HP && rockman->time_hurt <= 0)
    {
        rockman->record_HP = rockman->HP;
        rockman->time_hurt = 60; // time for damage
    }

    if (rockman->time_hurt > 0)
    {
        rockman->time_hurt--;
        rockman->state = HURT;
    }
}



void RockmanHurtInBoss (Rockman *rockman)
{
    if (rockman->HP < rockman->record_HP && rockman->time_hurt <= 0)
    {
        rockman->record_HP = rockman->HP;
        rockman->time_hurt = 60; // time for damage
    }

    if (rockman->time_hurt > 0)
    {
        rockman->time_hurt--;
        rockman->HP = rockman->record_HP;
    }
}

