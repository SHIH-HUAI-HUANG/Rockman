#include "resource.h"
/** The Boss 1 is called "Necromancer - Simon" */


/** Function : Memery allocation for struct of Boss_2 */
Boss_2 *CallocBoss_2()
{
    Boss_2 *addr = (Boss_2 *)calloc(1, sizeof(Boss_2));
    return addr;
}


void InitBoss_2 (Boss_2 *boss_2)
{
    boss_2->x = 600;
    boss_2->y = 495;
    boss_2->speed = 1;
    boss_2->HP = 20;
    boss_2->state = 1;

    boss_2->direction = true;
    boss_2->img_idle = al_load_bitmap ("./picture/demon-idle.png");
    boss_2->img_attack = al_load_bitmap ("./picture/demon-attack.png");
    boss_2->background = al_load_bitmap ("./picture/map_boss2.png");

    boss_2->time_idle = 300;
    boss_2->time_attack = 110;
}


// Function : track the rockman's position
void MoveBoss_2 (Boss_2 *boss_2, Rockman *rockman)
{
    if ( (rockman->x - boss_2->x - 120) > 0 )
    {
        boss_2->x = boss_2->x + boss_2->speed;
        boss_2->direction = true;
    }

    else if ( (rockman->x - boss_2->x - 120) < 0 )
    {
        boss_2->x = boss_2->x - boss_2->speed;
        boss_2->direction = false;
    }
    if (boss_2->x > 528)
        boss_2->x = 528;
}


void StateBoss_2 (Boss_2 *boss_2, Allegro *allegro, Rockman *rockman)
{
    switch (boss_2->state)
    {
    case 0:
        boss_2->time_idle--;
        MoveBoss_2 (boss_2, rockman);
        if (boss_2->time_idle <- 0)
        {
            boss_2->state = 1;
            boss_2->time_attack = 110;
        }
        break;

    case 1:
        boss_2->time_attack--;
        if (boss_2->time_attack <- 0)
        {
            boss_2->state = 0;
            boss_2->time_idle = 300;
            /** check rockman position for attack */
        }
        break;
    }

}


void DrawBoss_2 (Boss_2 *boss_2, Allegro *allegro, Rockman *rockman)
{
    int range1 = allegro->FRAME%60;

    switch (boss_2->state)
    {
    case 0: /** IDLE */
        if ( 0 <= range1 && range1 < 10)
            al_draw_bitmap_region (boss_2->img_idle, 0, 0, 160, 144, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 10 <= range1 && range1 < 20)
            al_draw_bitmap_region (boss_2->img_idle, 160, 0, 160, 144, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 20 <= range1 && range1 < 30)
            al_draw_bitmap_region (boss_2->img_idle, 320, 0, 160, 144, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 30 <= range1 && range1 < 40)
            al_draw_bitmap_region (boss_2->img_idle, 480, 0, 160, 144, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 40 <= range1 && range1 < 50)
            al_draw_bitmap_region (boss_2->img_idle, 640, 0, 160, 144, boss_2->x, boss_2->y, boss_2->direction);

        else if (50 <= range1 && range1 < 60)
            al_draw_bitmap_region (boss_2->img_idle, 800, 0, 160, 144, boss_2->x, boss_2->y, boss_2->direction);
        break;

    case 1: /** Attack */
        if ( 100 < boss_2->time_attack && boss_2->time_attack <= 110)
            al_draw_bitmap_region (boss_2->img_attack, 0, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 90 < boss_2->time_attack && boss_2->time_attack <= 100)
            al_draw_bitmap_region (boss_2->img_attack, 240, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 80 < boss_2->time_attack && boss_2->time_attack <= 90)
            al_draw_bitmap_region (boss_2->img_attack, 480, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 70 < boss_2->time_attack && boss_2->time_attack <= 80)
            al_draw_bitmap_region (boss_2->img_attack, 720, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 60 < boss_2->time_attack && boss_2->time_attack <= 70)
            al_draw_bitmap_region (boss_2->img_attack, 960, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 50 < boss_2->time_attack && boss_2->time_attack <= 60)
            al_draw_bitmap_region (boss_2->img_attack, 1200, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 40 < boss_2->time_attack && boss_2->time_attack <= 50)
            al_draw_bitmap_region (boss_2->img_attack, 1440, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);

        else if ( 30 < boss_2->time_attack && boss_2->time_attack <= 40) /** attack */
        {
            CheckAOEBoss_2 (boss_2, rockman);
            al_draw_bitmap_region (boss_2->img_attack, 1680, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);
        }

        else if ( 20 < boss_2->time_attack && boss_2->time_attack <= 30) /** attack */
        {
            CheckAOEBoss_2 (boss_2, rockman);
            al_draw_bitmap_region (boss_2->img_attack, 1920, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);
        }

        else if ( 10 < boss_2->time_attack && boss_2->time_attack <= 20) /** attack */
        {
            CheckAOEBoss_2 (boss_2, rockman);
            al_draw_bitmap_region (boss_2->img_attack, 2160, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);
        }

        else if ( 0 < boss_2->time_attack && boss_2->time_attack <= 10) /** attack */
        {
            CheckAOEBoss_2 (boss_2, rockman);
            al_draw_bitmap_region (boss_2->img_attack, 2400, 0, 240, 192, boss_2->x, boss_2->y, boss_2->direction);
        }
        break;

    }
}



void BulletCollideBoss_2 (Rockman *rockman, Boss_2 *boss_2)
{
    int x = boss_2->x + 60;
    int y = boss_2->y + 53;

    for (int i = 0; i < NUM_BULLET; i++)
    {
        if ( rockman->bullet[i].activity && boss_2->state == 0 )
        {
            if ( abs(x - rockman->bullet[i].x - 10) < 10 && abs(y - rockman->bullet[i].y - 10) < 10 )
            {
                rockman->bullet[i].activity = false;
                boss_2->HP--;
            }
        }

    }
}


void DrawBoss_2HP (Boss_2 *boss_2)
{
    al_draw_filled_rectangle (663, 55, 723, 203, al_map_rgb(0, 0, 0));
    for (int i = 0; i < boss_2->HP; i++)
    {
        al_draw_filled_rectangle (668, 193 - (i*7), 718, 198 - (i*7), al_map_rgb(255, 0, 0));
    }
}



void CheckBoss_2Alive (Boss_2 *boss_2, Allegro *allegro)
{
    if (boss_2->HP <= 0)
    {
        allegro->STATE = LOADING;
        allegro->frame_flag = allegro->FRAME;
        allegro->pass_stage2 = true;
         al_set_sample_instance_playing(allegro->instance3, false); // close game music
    }
}



void InitRockmanInBoss_2 (Rockman *rockman)
{
    rockman->x = 0;
    rockman->y = 595;
    for (int i = 0; i < NUM_BULLET; i++)
    {
        rockman->bullet[i].activity = false;
    }
}



void CheckAOEBoss_2 (Boss_2 *boss_2, Rockman *rockman)
{
    int x = rockman->x + 45; // rockman
    int y = rockman->y + 50; // position

    if (boss_2->direction)
    {
        if ( abs(x - boss_2->x - 180) < 105 && abs(x - boss_2->y - 144) < 98 )
            rockman->HP--;
    }

    else
    {
        if ( abs(x - boss_2->x - 60) < 105 && abs(x - boss_2->y - 48) < 98 )
            rockman->HP--;
    }
}



// rockman collide boss2, and minus rockman'HP
void RockmanCollideBoss_2 (Rockman *rockman, Boss_2 *boss_2)
{
    if ( abs(rockman->x + 45 - boss_2->x - 120) < 80 && abs(rockman->y + 52 - boss_2->y - 50) < 74 )
    {
        rockman->HP--;
    }
}



void StageBoss_2 (Boss_2 *boss_2, Rockman *rockman, Allegro *allegro)
{
    RockmanJumpInBoss (rockman, allegro);
    RockmanStateInBoss (rockman, allegro);
    MoveRockmanInBoss (rockman, allegro);
    MoveBullet (rockman);
    CheckBulletOver (rockman);
    StateBoss_2 (boss_2, allegro, rockman);
    BulletCollideBoss_2 (rockman, boss_2);
    LimitRockmanInBoss (rockman);
    RockmanCollideBoss_2 (rockman, boss_2);
    RockmanHurtInBoss (rockman);

    al_draw_bitmap (boss_2->background, 0, 0, 0);
    DrawBoss_2HP (boss_2);
    DrawBullet (rockman);
    DrawRockman (rockman, allegro);
    DrawRockmanHP (rockman);
    DrawBoss_2 (boss_2, allegro, rockman);

    CheckAlive (rockman, allegro);
    CheckBoss_2Alive (boss_2, allegro);
}
