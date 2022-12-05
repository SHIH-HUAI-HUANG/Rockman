#include "resource.h"

int main()
{
    /** enum */

    Allegro *allegro = CallocAllegro();
    AllegroDriverInit (allegro);
    Rockman *rockman = CallocRockman ();
    InitRockman (rockman);
    Boss_1 *boss_1 = CallocBoss_1();
    InitBoss_1 (boss_1);



    while(!allegro->finish)
    {

        EventCheck(allegro, rockman, boss_1);
        al_flip_display();
    }


    free(allegro);
    free(rockman);
    return 0;
}
