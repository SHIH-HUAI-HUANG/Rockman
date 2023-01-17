#include "resource.h"

int main()
{
    Allegro *allegro = CallocAllegro();
    AllegroDriverInit (allegro);
    Rockman *rockman = CallocRockman ();
    InitRockman (rockman);
    Boss_1 *boss_1 = CallocBoss_1();
    InitBoss_1 (boss_1);
    Monster *monster = CallocMonster (NUM_MONSTER);
    InitMonster (monster);
    Boss_2 *boss_2 = CallocBoss_2();
    InitBoss_2 (boss_2);
    Boss_3 *boss_3 = CallocBoss_3();
    InitBoss_3 (boss_3);


    while(!allegro->finish)
    {
        EventCheck(allegro, rockman, monster, boss_1, boss_2, boss_3);
        al_flip_display();
    }


    free(allegro);
    free(rockman);
    free(monster);
    free(boss_1);
    free(boss_2);
    free(boss_3);
    return 0;
}
