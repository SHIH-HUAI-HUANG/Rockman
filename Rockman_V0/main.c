#include "resource.h"

int main()
{
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
    free(boss_1);
    return 0;
}
