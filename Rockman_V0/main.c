#include "resource.h"

int main()
{
    /** enum */

    Allegro *allegro = CallocAllegro();
    AllegroDriverInit (allegro);
    Rockman *rockman = CallocRockman ();
    InitRockman (rockman);



    while(!allegro->finish)
    {

        EventCheck(allegro, rockman);
        al_flip_display();
    }


    free(allegro);
    free(rockman);
    return 0;
}
