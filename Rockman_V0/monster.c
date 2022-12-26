#include "resource.h"
/**
All monster in small stage like creeper...
1. Creeper : only walk back and forth.
*/

/** Function : Memery allocation for struct of Monster */
Monster *CallocMonster (int number)
{
    Monster *addr = (Monster *)calloc(number, sizeof(Monster));
    return addr;
}


void InitMonster (Monster *monster)
{
    /** skull */
    monster[0].x = 855;
    monster[0].y = 452 - 100; // 100 is Creeper's High

    monster[1].x = 2040;
    monster[1].y = 549 - 100; // 100 is Creeper's High

    monster[2].x = 3582;
    monster[2].y = 277 - 100; // 100 is Creeper's High

    monster[3].x = 4843;
    monster[3].y = 370 - 100; // 100 is Creeper's High

    monster[4].x = 5940;
    monster[4].y = 220 - 100; // 100 is Creeper's High

    monster[0].delta_x = 258;
    monster[1].delta_x = 252;
    monster[2].delta_x = 433;
    monster[3].delta_x = 950;
    monster[4].delta_x = 210;
    /** fire skull */
    monster[5].x = 1040;
    monster[5].y = 0;

    monster[6].x = 1800;
    monster[6].y = 50;

    monster[7].x = 2800;
    monster[7].y = 100;

    monster[8].x = 4150;
    monster[8].y = 0;

    monster[9].x = 5200;
    monster[9].y = 0;

    for (int i = 0; i < 5; i++)
    {
        monster[i].alive = true;
        monster[i].standard_x = monster[i].x;
        monster[i].standard_y = monster[i].y;
        monster[i].speed = SPEED;
        monster[i].direction = true;
        monster[i].img = al_load_bitmap ("./picture/skull.png");
    }
    for (int i = 5; i < 10; i++)
    {
        monster[i].alive = true;
        monster[i].standard_x = monster[i].x;
        monster[i].standard_y = monster[i].y;
        monster[i].speed = SPEED;
        monster[i].direction = true;
        monster[i].direction_y = true;
        monster[i].img = al_load_bitmap ("./picture/fire_skull.png");
    }
}


/** no use now */
void DrawMonster (Monster *monster, Allegro *allegro)
{
    for (int i = 0; i < 3; i++)
    {
        if (monster[i].alive)
        {
            al_draw_bitmap (monster[i].img, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);
        }
    }
    printf("x = %d, y = %d\n", monster[0].x, monster[0].y);
}



void MoveSkull (Monster *monster)
{
    for (int i = 0; i < 5; i++)
    {
        if (monster[i].direction) // 1
            monster[i].x = monster[i].x + monster[i].speed;

        else if (!monster[i].direction) // 0
            monster[i].x = monster[i].x - monster[i].speed;

        if (monster[i].x < monster[i].standard_x || (monster[i].standard_x + monster[i].delta_x) < monster[i].x)
            monster[i].direction = !monster[i].direction;
    }

}


void DrawSkull (Monster *monster, Allegro *allegro)
{
    int range = allegro->FRAME%80;

    for (int i = 0; i < 5; i++)
    {
        if (monster[i].alive)
        {
            if ( 0 <= range && range < 20)
                al_draw_bitmap_region (monster[i].img,  0, 0, 54, 70, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);

            else if ( 20 <= range && range < 40)
                al_draw_bitmap_region (monster[i].img,  54, 0, 54, 70, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);

            else if ( 40 <= range && range < 60)
                al_draw_bitmap_region (monster[i].img,  108, 0, 54, 70, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);

            else if ( 60 <= range && range < 80)
                al_draw_bitmap_region (monster[i].img,  162, 0, 54, 70, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);
        }
    }
}


void MoveFireSkull (Monster *monster)
{
    for (int i = 5; i < 10; i++)
    {
        if (monster[i].direction) // 1
            monster[i].x = monster[i].x + monster[i].speed;
        else if (!monster[i].direction) // 0
            monster[i].x = monster[i].x - monster[i].speed;

        if (monster[i].direction_y) // 1
            monster[i].y = monster[i].y + monster[i].speed;
        else if (!monster[i].direction_y) // 0
            monster[i].y = monster[i].y - monster[i].speed;

        if (monster[i].x < monster[i].standard_x || (monster[i].standard_x + 500) < monster[i].x)
            monster[i].direction = !monster[i].direction;
        if (monster[i].y < monster[i].standard_y || (monster[i].standard_y + 400) < monster[i].y)
            monster[i].direction_y = !monster[i].direction_y;
    }
}


void DrawFireSkull (Monster *monster, Allegro *allegro)
{
    int range = allegro->FRAME%160;

    for (int i = 5; i < 10; i++)
    {
        if (monster[i].alive)
        {
            if ( 0 <= range && range < 20)
                al_draw_bitmap_region (monster[i].img,  0, 0, 96, 112, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);

            else if ( 20 <= range && range < 40)
                al_draw_bitmap_region (monster[i].img,  96, 0, 96, 112, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);

            else if ( 40 <= range && range < 60)
                al_draw_bitmap_region (monster[i].img,  192, 0, 96, 112, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);

            else if ( 60 <= range && range < 80)
                al_draw_bitmap_region (monster[i].img,  288, 0, 96, 112, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);

            else if ( 80 <= range && range < 100)
                al_draw_bitmap_region (monster[i].img,  384, 0, 96, 112, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);

            else if ( 100 <= range && range < 120)
                al_draw_bitmap_region (monster[i].img,  480, 0, 96, 112, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);

            else if ( 120 <= range && range < 140)
                al_draw_bitmap_region (monster[i].img,  576, 0, 96, 112, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);

            else if ( 140 <= range && range < 160)
                al_draw_bitmap_region (monster[i].img,  672, 0, 96, 112, allegro->map.x + monster[i].x, monster[i].y, monster[i].direction);
        }
    }
}



void BulletCrushMonster (Monster *monster, Rockman *rockman, Allegro *allegro)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < NUM_BULLET; j++)
        {
            if (rockman->bullet[j].activity)
            {
                if ( abs(rockman->bullet[j].x - monster[i].x - 54 - allegro->map.x) < 44 && abs(rockman->bullet[j].y - monster[i].y - 35 - allegro->map.y) < 25 )
                    monster[i].alive = false;
            }
        }
    }

    for (int i = 5; i < 10; i++)
    {
        for (int j = 0; j < NUM_BULLET; j++)
        {
            if (rockman->bullet[j].activity)
            {
                if ( abs(rockman->bullet[j].x - monster[i].x - 96 - allegro->map.x) < 86 && abs(rockman->bullet[j].y - monster[i].y - 56 - allegro->map.y) < 46 )
                    monster[i].alive = false;
            }
        }
    }
}


void MonsterCrushRockman (Monster *monster, Rockman *rockman, Allegro *allegro)
{
    int x = rockman->x + ROCKMAN_W/2;
    int y = rockman->y + ROCKMAN_H/2;

    for (int i = 0; i < 5; i++)
    {
        if ( abs(x - monster[i].x - 54 - allegro->map.x) < (15 + 15) && abs(y - monster[i].y - 35 - allegro->map.y) < (23 + 38) && monster[i].alive)
        {
            rockman->HP--;
            monster[i].alive = false;
        }
    }
    for (int i = 5; i < 10; i++)
    {
        if ( abs(x - monster[i].x - 96 - allegro->map.x) < (15 + 15) && abs(y - monster[i].y - 56 - allegro->map.y) < (23 + 38) && monster[i].alive)
        {
            rockman->HP--;
            monster[i].alive = false;
        }
    }
}
