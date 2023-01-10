#include "resource.h"


/** Function : Use Linkedlist add the bullet */
void CreateBullet (Rockman *rockman)
{
    int number = 0;
    int time = 0;
    do
    {
        if (rockman->bullet[number].activity)
        {
            number++;
        }
        else if (!rockman->bullet[number].activity)
        {
            rockman->bullet[number].activity = true;
            time++;
        }
    }
    while (time == 0);

    rockman->bullet[number].activity = true;
    rockman->bullet[number].x = rockman->x + 50;
    rockman->bullet[number].y = rockman->y + 50;
    rockman->bullet[number].direction = rockman->direction;
}



void DrawBullet (Rockman *rockman)
{
    for (int i = 0; i < NUM_BULLET; i++)
    {
        if (rockman->bullet[i].activity)
        {
             al_draw_bitmap_region (rockman->img, 272, 516, 28, 21,rockman->bullet[i].x, rockman->bullet[i].y, 0);
        }

    }
}


void MoveBullet (Rockman *rockman)
{
    for (int i = 0; i < NUM_BULLET; i++)
    {
        if (rockman->bullet[i].activity)
        {
            if (rockman->bullet[i].direction)
                rockman->bullet[i].x = rockman->bullet[i].x - SPEED*3;

            else
            {
                rockman->bullet[i].x = rockman->bullet[i].x + SPEED*3;
            }
        }
    }
}

void CheckBulletOver (Rockman *rockman)
{
    for (int i = 0; i < NUM_BULLET; i++)
    {
        if ((rockman->bullet[i].x > 768) &&  (rockman->bullet[i].activity == true))
            rockman->bullet[i].activity = false;
        if ((rockman->bullet[i].x < 0) &&  (rockman->bullet[i].activity == true))
            rockman->bullet[i].activity = false;
    }

}
