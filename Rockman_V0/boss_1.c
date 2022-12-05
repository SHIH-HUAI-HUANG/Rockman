#include "resource.h"
/** The Boss 1 is called "CopyMan" */


/** Function : Memery allocation for struct of Boss_1 */
Boss_1 *CallocBoss_1()
{
    Boss_1 *addr = (Boss_1 *)calloc(1, sizeof(Boss_1));
    return addr;
}


void InitBoss_1 (Boss_1 *boss_1)
{
    boss_1->x = 300;
    boss_1->y = 400;
    boss_1->speed = SPEED;
    boss_1->state = STAND;

    boss_1->direction = false;
    boss_1->img = al_load_bitmap ("./picture/rockman.png");

}


void DrawBoss_1 (Boss_1 *boss_1, Allegro *allegro)
{
    int range = allegro->FRAME%32;
    int range_stand = allegro->FRAME%120;

    if ( 0 <= range_stand && range_stand < 100)
        al_draw_bitmap_region (boss_1->img, 6, 3, 74, 105, boss_1->x, boss_1->y, boss_1->direction);

    else if ( 100 <= range_stand && range_stand < 120)
        al_draw_bitmap_region (boss_1->img, 122, 3, 73, 105, boss_1->x, boss_1->y, boss_1->direction);
}



void MoveBoss_1 (Boss_1 *boss_1)
{
    if (!boss_1->direction)
        boss_1->x = boss_1->x + boss_1->speed;

    else if (boss_1->direction)
        boss_1->x = boss_1->x - boss_1->speed;
    if (boss_1->x < 0)
        boss_1->direction = false;
    if (boss_1->x > (WINDOWS_W - 50))
        boss_1->direction = true;

}
