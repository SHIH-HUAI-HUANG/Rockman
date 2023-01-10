#include "resource.h"
/** The Boss 1 is called "CopyMan - X" */


/** Function : Memery allocation for struct of Boss_1 */
Boss_1 *CallocBoss_1()
{
    Boss_1 *addr = (Boss_1 *)calloc(1, sizeof(Boss_1));
    return addr;
}


void InitBoss_1 (Boss_1 *boss_1)
{
    boss_1->x = 500;
    boss_1->y = 525;
    boss_1->speed = SPEED;
    boss_1->state = STAND;
    boss_1->HP = 20;

    boss_1->direction = false;
    boss_1->img = al_load_bitmap ("./picture/rockman.png");
    boss_1->background = al_load_bitmap ("./picture/jupiterstage.png");
    /** minion */
    boss_1->minion.x = rand()%650;
    boss_1->minion.y = 0;
    boss_1->minion.speed_x = 4;
    boss_1->minion.speed_y = 2;
    boss_1->minion.img =  al_load_bitmap ("./picture/fire_skull.png");
}


void DrawBoss_1 (Boss_1 *boss_1, Allegro *allegro)
{
    int range = allegro->FRAME%32;
    int range_stand = allegro->FRAME%120;

    switch (boss_1->state)
    {
    case STAND:
        if ( 0 <= range_stand && range_stand < 100)
            al_draw_bitmap_region (boss_1->img, 6, 3, 74, 105, boss_1->x, boss_1->y, boss_1->direction);

        else if ( 100 <= range_stand && range_stand < 120)
            al_draw_bitmap_region (boss_1->img, 122, 3, 73, 105, boss_1->x, boss_1->y, boss_1->direction);
        break;

    case RUN_RIGHT:
        if ( 0 <= range && range < 8)
            al_draw_bitmap_region (boss_1->img, 125, 233, 101, 105, boss_1->x, boss_1->y, boss_1->direction);

        else if ( 8 <= range && range < 16)
            al_draw_bitmap_region (boss_1->img, 251, 233, 91, 105, boss_1->x, boss_1->y, boss_1->direction);

        else if ( 16 <= range && range < 24)
            al_draw_bitmap_region (boss_1->img, 352, 233, 105, 105, boss_1->x, boss_1->y, boss_1->direction);

        else if ( 24 <= range && range < 32)
            al_draw_bitmap_region (boss_1->img, 251, 233, 91, 105, boss_1->x, boss_1->y, boss_1->direction);
        break;

    case RUN_LEFT:
        if ( 0 <= range && range < 8)
            al_draw_bitmap_region (boss_1->img, 125, 233, 101, 105, boss_1->x, boss_1->y, boss_1->direction);

        else if ( 8 <= range && range < 16)
            al_draw_bitmap_region (boss_1->img, 251, 233, 91, 105, boss_1->x, boss_1->y, boss_1->direction);

        else if ( 16 <= range && range < 24)
            al_draw_bitmap_region (boss_1->img, 352, 233, 105, 105, boss_1->x, boss_1->y, boss_1->direction);

        else if ( 24 <= range && range < 32)
            al_draw_bitmap_region (boss_1->img, 251, 233, 91, 105, boss_1->x, boss_1->y, boss_1->direction);
        break;

    case JUMP:
        al_draw_bitmap_region (boss_1->img, 0, 233, 101, 105, boss_1->x, boss_1->y, boss_1->direction);
        break;

    case ATTACK:
        al_draw_bitmap_region (boss_1->img, 467, 118, 109, 105, boss_1->x, boss_1->y, boss_1->direction);
        break;
    }
}



void MoveBoss_1 (Boss_1 *boss_1)
{
    if (!boss_1->direction)
    {
        boss_1->x = boss_1->x + boss_1->speed;
        boss_1->state = RUN_RIGHT;
    }

    else if (boss_1->direction)
    {
        boss_1->x = boss_1->x - boss_1->speed;
        boss_1->state = RUN_LEFT;
    }

    if (boss_1->x < 0)
        boss_1->direction = false;
    if (boss_1->x > (WINDOWS_W - 50))
        boss_1->direction = true;
}



void BulletCrushBoss_1 (Boss_1 *boss_1, Rockman *rockman)
{
    int x = boss_1->x + 50;
    int y = boss_1->y + 50;

    for (int i = 0; i < NUM_BULLET; i++)
    {
        if (rockman->bullet[i].activity)
        {
            if ( abs(rockman->bullet[i].x - x) < 50 && abs(rockman->bullet[i].y - y) < 50 )
            {
                rockman->bullet[i].activity = false;
                boss_1->HP--;
            }
        }
    }
}


void InitRockmanInBoss_1 (Rockman *rockman)
{
    rockman->x = 0;
    rockman->y = 525;
    for (int i = 0; i < NUM_BULLET; i++)
    {
        rockman->bullet[i].activity = false;
    }
}


// rockman collide boss, and minus rockman'HP
void RockmanCollideBoss_1 (Rockman *rockman, Boss_1 *boss_1)
{
    if ( abs(rockman->x - boss_1->x) < 70 && abs(rockman->y - boss_1->y) < 80 )
        rockman->HP--;
}


// rockman collide minion, and minus rockman'HP
void RockmanCollideMinion (Rockman *rockman, Boss_1 *boss_1)
{
    if ( abs(rockman->x + 45 - boss_1->minion.x - 96) < 30 && abs(rockman->y + 50 - boss_1->minion.y - 56) < 61 )
        rockman->HP--;
}



void DrawMinion (Boss_1 *boss_1, Allegro *allegro)
{
    int range = allegro->FRAME%160;

    if ( 0 <= range && range < 20)
        al_draw_bitmap_region (boss_1->minion.img,  0, 0, 96, 112, boss_1->minion.x, boss_1->minion.y, boss_1->minion.direction_x);

    else if ( 20 <= range && range < 40)
        al_draw_bitmap_region (boss_1->minion.img,  96, 0, 96, 112, boss_1->minion.x, boss_1->minion.y, boss_1->minion.direction_x);

    else if ( 40 <= range && range < 60)
        al_draw_bitmap_region (boss_1->minion.img,  192, 0, 96, 112, boss_1->minion.x, boss_1->minion.y, boss_1->minion.direction_x);

    else if ( 60 <= range && range < 80)
        al_draw_bitmap_region (boss_1->minion.img,  288, 0, 96, 112, boss_1->minion.x, boss_1->minion.y, boss_1->minion.direction_x);

    else if ( 80 <= range && range < 100)
        al_draw_bitmap_region (boss_1->minion.img,  384, 0, 96, 112, boss_1->minion.x, boss_1->minion.y, boss_1->minion.direction_x);

    else if ( 100 <= range && range < 120)
        al_draw_bitmap_region (boss_1->minion.img,  480, 0, 96, 112, boss_1->minion.x, boss_1->minion.y, boss_1->minion.direction_x);

    else if ( 120 <= range && range < 140)
        al_draw_bitmap_region (boss_1->minion.img,  576, 0, 96, 112, boss_1->minion.x, boss_1->minion.y, boss_1->minion.direction_x);

    else if ( 140 <= range && range < 160)
        al_draw_bitmap_region (boss_1->minion.img,  672, 0, 96, 112, boss_1->minion.x, boss_1->minion.y, boss_1->minion.direction_x);

}



void MoveMinion (Boss_1 *boss_1)
{
    if (boss_1->minion.direction_x) // 1
        boss_1->minion.x = boss_1->minion.x + boss_1->minion.speed_x;
    else if (!boss_1->minion.direction_x) // 0
        boss_1->minion.x = boss_1->minion.x - boss_1->minion.speed_x;

    if (boss_1->minion.direction_y) // 1
        boss_1->minion.y = boss_1->minion.y + boss_1->minion.speed_y;
    else if (!boss_1->minion.direction_y) // 0
        boss_1->minion.y = boss_1->minion.y - boss_1->minion.speed_y;

    if (boss_1->minion.x < 10)
    {
        boss_1->minion.x = 10;
        boss_1->minion.direction_x = !boss_1->minion.direction_x;
        boss_1->minion.speed_x = 2 + rand()%5;// speed = 2 ~ 6
    }
    if (boss_1->minion.x > 620)
    {
        boss_1->minion.x = 620;
        boss_1->minion.direction_x = !boss_1->minion.direction_x;
        boss_1->minion.speed_x = 2 + rand()%5;// speed = 2 ~ 6
    }
    if (boss_1->minion.y < 10)
    {
        boss_1->minion.y = 10;
        boss_1->minion.direction_y = !boss_1->minion.direction_y;
        boss_1->minion.speed_y = 2 + rand()%5;// speed = 2 ~ 6
    }
    if (boss_1->minion.y > 620)
    {
        boss_1->minion.y = 620;
        boss_1->minion.direction_y = !boss_1->minion.direction_y;
        boss_1->minion.speed_y = 2 + rand()%5;// speed = 2 ~ 6
    }
}

void DrawBoss_1HP (Boss_1 *boss_1)
{
    al_draw_filled_rectangle (663, 55, 723, 203, al_map_rgb(0, 0, 0));
    for (int i = 0; i < boss_1->HP; i++)
    {
        al_draw_filled_rectangle (668, 193 - (i*7), 718, 198 - (i*7), al_map_rgb(255, 0, 0));
    }
}


void CheckBoss_1Alive (Boss_1 *boss_1, Allegro *allegro)
{
    if (boss_1->HP <= 0)
    {
        allegro->STATE = LOADING;
        allegro->frame_flag = allegro->FRAME;
        allegro->pass_stage1 = true;
        al_set_sample_instance_playing(allegro->instance2, false); // close game music
    }
}

/** total function */
void StageBoss_1 (Boss_1 *boss_1, Rockman *rockman, Allegro *allegro)
{
    RockmanJumpInBoss (rockman, allegro);
    RockmanStateInBoss (rockman, allegro);
    MoveRockmanInBoss (rockman, allegro);
    MoveBullet (rockman);
    MoveBoss_1 (boss_1);
    CheckBulletOver (rockman);
    BulletCrushBoss_1 (boss_1, rockman);
    RockmanCollideBoss_1 (rockman, boss_1);
    MoveMinion (boss_1);
    LimitRockmanInBoss (rockman);
    RockmanHurtInBoss (rockman);

    al_draw_bitmap (boss_1->background, 0, 0, 0);
    DrawBullet (rockman);
    DrawRockman (rockman, allegro);
    DrawBoss_1 (boss_1, allegro);
    DrawRockmanHP (rockman);
    DrawMinion (boss_1, allegro);
    DrawBoss_1HP (boss_1);

    CheckAlive (rockman, allegro);
    CheckBoss_1Alive (boss_1, allegro);
}

