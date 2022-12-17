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
    boss_3->HP = 10;
    boss_3->state = 1;

    boss_3->direction_x = true;
    boss_3->direction_y = true;
    boss_3->img_idle = al_load_bitmap ("./picture/XaiYa.png");
    boss_3->img_attack = al_load_bitmap ("./picture/XaiYa_crazy.png");
    boss_3->explosion = al_load_bitmap ("./picture/123.png");
}



void DrawBoss_3 (Boss_3 *boss_3, Allegro *allegro)
{
    int range = allegro->FRAME%120;
    int x = boss_3->x;
    int y = boss_3->y;

    if ( 0 <= range && range < 30)
        al_draw_bitmap (boss_3->img_idle, x, y, 0);

    else if ( 30 <= range && range < 120)
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

    if (boss_3->x < 0 || boss_3->x > 617)
    {
        boss_3->direction_x = !boss_3->direction_x;
    }
    if (boss_3->y < 0 || boss_3->y > 525)
    {
        boss_3->direction_y = !boss_3->direction_y;
        boss_3->speed_y = rand()%5 + 1;
    }
}


void DrawExplosion (Boss_3 *boss_3, Allegro *allegro)
{
    int range = allegro->FRAME%80;
    int x = 100;
    int y = 100;

    if ( 0 <= range && range < 10)
        al_draw_bitmap_region (boss_3->explosion, 0, 0, 96, 96, x, y, 0);

    else if ( 10 <= range && range < 20)
        al_draw_bitmap_region (boss_3->explosion, 96, 0, 96, 96, x, y, 0);

    else if ( 20 <= range && range < 30)
        al_draw_bitmap_region (boss_3->explosion, 192, 0, 96, 96, x, y, 0);

    else if ( 30 <= range && range < 40)
        al_draw_bitmap_region (boss_3->explosion, 288, 0, 96, 96, x, y, 0);

    else if ( 40 <= range && range < 50)
        al_draw_bitmap_region (boss_3->explosion, 384, 0, 96, 96, x, y, 0);

    else if ( 50 <= range && range < 60)
        al_draw_bitmap_region (boss_3->explosion, 480, 0, 96, 96, x, y, 0);

    else if ( 60 <= range && range < 70)
        al_draw_bitmap_region (boss_3->explosion, 576, 0, 96, 96, x, y, 0);

    else if ( 70 <= range && range < 80)
        al_draw_bitmap_region (boss_3->explosion, 672, 0, 96, 96, x, y, 0);
}
