#include "resource.h"
/** The Boss 1 is called " XaiYa " */


/** Function : Memery allocation for struct of Boss_3 */
Boss_3 *CallocBoss_3()
{
    Boss_3 *addr = (Boss_3 *)calloc(1, sizeof(Boss_3));
    return addr;
}


void InitBoss_3 (Boss_3 *boss_3)
{
    boss_3->x = 500;
    boss_3->y = 0;
    boss_3->speed_x = 2;
    boss_3->speed_y = 2;
    boss_3->HP = 20;
    boss_3->HP_2 = 1;
    boss_3->state = 0;
    boss_3->bullet.activity = false;
    boss_3->time_crazy_attack = 180;

    boss_3->direction_x = true;
    boss_3->direction_y = true;
    boss_3->img_idle = al_load_bitmap ("./picture/XaiYa.png");
    boss_3->img_attack = al_load_bitmap ("./picture/XaiYa_crazy.png");
    boss_3->explosion = al_load_bitmap ("./picture/123.png");
    boss_3->background1 = al_load_bitmap ("./picture/night.png");
    boss_3->background2 = al_load_bitmap ("./picture/night_crazy.png");
}



void DrawBoss_3 (Boss_3 *boss_3, Allegro *allegro)
{
    int range = allegro->FRAME%120;
    int x = boss_3->x;
    int y = boss_3->y;

    if ( boss_3->state == 0 )
        al_draw_bitmap (boss_3->img_idle, x, y, 0);

    else if ( boss_3->state == 1 )
        al_draw_bitmap (boss_3->img_attack, x, y, 0);
}


// Function : move boss 3 in normal state.
void MoveNormalYA (Boss_3 *boss_3)
{
    if (boss_3->direction_x) // 1
        boss_3->x = boss_3->x + boss_3->speed_x;
    else  if (!boss_3->direction_x) // 1
        boss_3->x = boss_3->x - boss_3->speed_x;

    if (boss_3->direction_y) // 1
        boss_3->y = boss_3->y + boss_3->speed_y;
    else  if (!boss_3->direction_y) // 1
        boss_3->y = boss_3->y - boss_3->speed_y;
    /** limit for move */
    if (boss_3->x < 10 || boss_3->x > 610)
    {
        boss_3->direction_x = !boss_3->direction_x;
    }
    if (boss_3->y < 10 || boss_3->y > 515)
    {
        boss_3->direction_y = !boss_3->direction_y;
        boss_3->speed_y = rand()%5 + 1;
        if (boss_3->y < 10) boss_3->y = 10;
        else if (boss_3->y > 515) boss_3->y = 515;
    }
}


// Function : move boss 3 in crazy state.
void MoveCrazyYA (Boss_3 *boss_3, Rockman *rockman)
{
    int x = rockman->x + 45;
    int y = rockman->y + 52;
    if ( (x - (boss_3->x + 75)) > 0 )
        boss_3->x = boss_3->x + boss_3->speed_x;

    else if ( (x - (boss_3->x + 75)) < 0 )
        boss_3->x = boss_3->x - boss_3->speed_x;

    if ( (y - (boss_3->y + 100)) > 0 )
        boss_3->y = boss_3->y + boss_3->speed_y;

    else if ( (y - (boss_3->y + 100)) < 0 )
        boss_3->y = boss_3->y - boss_3->speed_y;
}


void CreateExplosion (Boss_3 *boss_3)
{
    int number = 0;
    int time = 0;
    do
    {
        if (boss_3->boom[number].times > 0)
        {
            number++;
        }
        else if (boss_3->boom[number].times <= 0)
        {
            boss_3->boom[number].times = 80; // initialize boom
            boss_3->boom[number].x = boss_3->bullet.x - 48;
            boss_3->boom[number].y = boss_3->bullet.y - 48;
            time++;
        }
    }
    while (time == 0);
}

void DrawExplosion (Boss_3 *boss_3)
{
    for (int i = 0; i < 20; i++)
    {
        boss_3->boom[i].times--;

        if (boss_3->boom[i].times > 0)
        {
            if ( 70 < boss_3->boom[i].times && boss_3->boom[i].times <= 80)
                al_draw_bitmap_region (boss_3->explosion, 0, 0, 96, 96, boss_3->boom[i].x, boss_3->boom[i].y, 0);

            else if ( 60 < boss_3->boom[i].times && boss_3->boom[i].times <= 70)
                al_draw_bitmap_region (boss_3->explosion, 96, 0, 96, 96, boss_3->boom[i].x, boss_3->boom[i].y, 0);

            else if ( 50 < boss_3->boom[i].times && boss_3->boom[i].times <= 60)
                al_draw_bitmap_region (boss_3->explosion, 192, 0, 96, 96, boss_3->boom[i].x, boss_3->boom[i].y, 0);

            else if ( 40 < boss_3->boom[i].times && boss_3->boom[i].times <= 50)
                al_draw_bitmap_region (boss_3->explosion, 288, 0, 96, 96, boss_3->boom[i].x, boss_3->boom[i].y, 0);

            else if ( 30 < boss_3->boom[i].times && boss_3->boom[i].times <= 40)
                al_draw_bitmap_region (boss_3->explosion, 384, 0, 96, 96, boss_3->boom[i].x, boss_3->boom[i].y, 0);

            else if ( 20 < boss_3->boom[i].times && boss_3->boom[i].times <= 30)
                al_draw_bitmap_region (boss_3->explosion, 480, 0, 96, 96, boss_3->boom[i].x, boss_3->boom[i].y, 0);

            else if ( 10 < boss_3->boom[i].times && boss_3->boom[i].times <= 20)
                al_draw_bitmap_region (boss_3->explosion, 576, 0, 96, 96, boss_3->boom[i].x, boss_3->boom[i].y, 0);

            else if ( 0 < boss_3->boom[i].times && boss_3->boom[i].times <= 10)
                al_draw_bitmap_region (boss_3->explosion, 672, 0, 96, 96, boss_3->boom[i].x, boss_3->boom[i].y, 0);
        }
    }
}


void ComputeBulletDirection (Boss_3 *boss_3, Rockman *rockman)
{
    float unit_x = 0, unit_y = 0, unit = 0;
    int x0 = boss_3->x + 75;
    int y0 = boss_3->y + 100;
    int x1 = rockman->x + 45;
    int y1 = rockman->y + 52;
    if (boss_3->bullet.activity) // activity is false
    {
        unit_x =  x1 - x0;
        unit_y =  y1 - y0;
        unit = sqrt(unit_x*unit_x + unit_y*unit_y);
        boss_3->bullet.speed_x = ((unit_x/unit) * 5);
        boss_3->bullet.speed_y = ((unit_y/unit) * 5);
    }
}



void CheckBoss_3Bullet (Boss_3 *boss_3, Rockman *rockman)
{
    if (!boss_3->bullet.activity && boss_3->state == 0)
    {
        boss_3->bullet.activity = !boss_3->bullet.activity;
        boss_3->bullet.x = boss_3->x + 75;
        boss_3->bullet.y = boss_3->y + 100;
        ComputeBulletDirection (boss_3, rockman);
    }
}



void DrawBoss_3Bullet (Boss_3 *boss_3)
{
    if (boss_3->bullet.activity)
        al_draw_filled_circle (boss_3->bullet.x, boss_3->bullet.y, 15, al_map_rgb(255, 0, 0));
}



void MoveBoss_3Bullet (Boss_3 *boss_3)
{
    if (boss_3->bullet.activity)
    {
        boss_3->bullet.x = boss_3->bullet.x + boss_3->bullet.speed_x;
        boss_3->bullet.y = boss_3->bullet.y + boss_3->bullet.speed_y;
    }
}


void CheckBoss_3BulletOver (Boss_3 *boss_3, Rockman *rockman)
{
    int x = rockman->x + 45;
    int y = rockman->y + 52;
    /** out of range */
    if (boss_3->bullet.activity)
    {
        if (boss_3->bullet.x < 0 || 768 < boss_3->bullet.x || boss_3->bullet.y < 0 || 725 < boss_3->bullet.y)
        {
            boss_3->bullet.activity = false;
            /** anime of explision */
            CreateExplosion (boss_3);
        }
    }
    /** collide player */
    if ( abs(x - boss_3->bullet.x) < 45 && abs(y - boss_3->bullet.y) < 52 && boss_3->bullet.activity )
    {
        boss_3->bullet.activity = false;
        rockman->HP--;
        /** anime of explision */
        CreateExplosion (boss_3);
    }
}


// Function : including checking boss 3 dide
void BulletCollideBoss_3 (Rockman *rockman, Boss_3 *boss_3, Allegro *allegro)
{
    int x = boss_3->x + 75;
    int y = boss_3->y + 100;

    for (int i = 0; i < NUM_BULLET; i++)
    {
        if ( rockman->bullet[i].activity )
        {
            if ( abs(x - rockman->bullet[i].x) < 55 && abs(y - rockman->bullet[i].y) < 80 )
            {
                rockman->bullet[i].activity = false;
                if (boss_3->state == 0)
                    boss_3->HP--;
                else  if (boss_3->state == 1)
                    boss_3->HP_2--;
            }
        }
    }

    if (boss_3->HP <= 0 && boss_3->state == 0) /** change to crazy mode */
    {
        boss_3->state = 1;
        boss_3->x = 309;
        boss_3->y = 0;
    }
    if (boss_3->HP_2 <= 0 && boss_3->state == 1) /** change to crazy mode */
    {
        allegro->STATE = LOADING;
        allegro->frame_flag = allegro->FRAME;
        allegro->pass_stage3 = true;
        al_set_sample_instance_playing(allegro->instance4, false); // close game music
    }
}



void DrawBoss_3HP (Boss_3 *boss_3)
{
    al_draw_filled_rectangle (663, 55, 723, 203, al_map_rgb(0, 0, 0));
    if (boss_3->state == 0)
    {
        for (int i = 0; i < boss_3->HP; i++)
        {
            al_draw_filled_rectangle (668, 193 - (i*7), 718, 198 - (i*7), al_map_rgb(255, 0, 0));
        }
    }
    else  if (boss_3->state == 1)
    {
        for (int i = 0; i < boss_3->HP_2; i++)
        {
            al_draw_filled_rectangle (668, 193 - (i*7), 718, 198 - (i*7), al_map_rgb(255, 0, 0));
        }
    }
}



// rockman collide boss2, and minus rockman'HP
void RockmanCollideBoss_3 (Rockman *rockman, Boss_3 *boss_3)
{
    if ( abs(rockman->x + 45 - boss_3->x - 75) < 56 && abs(rockman->y + 52 - boss_3->y - 100) < 109 && boss_3->state == 0 )
    {
        rockman->HP--;
    }

    else if ( abs(rockman->x + 45 - boss_3->x - 75) < 56 && abs(rockman->y + 52 - boss_3->y - 100) < 109 && boss_3->state == 1 )
    {
        if (boss_3->time_crazy_attack == 180)
        {
            rockman->HP--;
            boss_3->time_crazy_attack--;
        }
    }

    if (boss_3->time_crazy_attack < 180) boss_3->time_crazy_attack--;
    else if (boss_3->time_crazy_attack < 0) boss_3->time_crazy_attack = 180;
}



void InitRockmanInBoss_3 (Rockman *rockman)
{
    rockman->x = 0;
    rockman->y = 400;
    for (int i = 0; i < NUM_BULLET; i++)
    {
        rockman->bullet[i].activity = false;
    }
}


void StageBoss_3 (Boss_3 *boss_3, Rockman *rockman, Allegro *allegro)
{
    RockmanJumpInBoss (rockman, allegro);
    RockmanStateInBoss (rockman, allegro);
    MoveRockmanInBoss (rockman, allegro);
    MoveBullet (rockman);
    CheckBulletOver (rockman);
    LimitRockmanInBoss (rockman);
    RockmanCollideBoss_3 (rockman, boss_3);
    CheckAlive (rockman, allegro);
    RockmanHurtInBoss (rockman);

    BulletCollideBoss_3 (rockman, boss_3, allegro);
    if (boss_3->state == 0) MoveNormalYA (boss_3);
    else if (boss_3->state == 1) MoveCrazyYA (boss_3, rockman);

    CheckBoss_3Bullet (boss_3, rockman);
    MoveBoss_3Bullet (boss_3);
    CheckBoss_3BulletOver (boss_3, rockman);

    if (boss_3->state == 0)  al_draw_bitmap (boss_3->background1, 0, 0, 0);
    else if (boss_3->state == 1)  al_draw_bitmap (boss_3->background2, 0, 0, 0);
    DrawBoss_3HP (boss_3);
    DrawBullet (rockman);
    DrawRockman (rockman, allegro);
    DrawRockmanHP (rockman);
    DrawBoss_3 (boss_3, allegro);
    DrawExplosion (boss_3);
    DrawBoss_3Bullet (boss_3);
}

