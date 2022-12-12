#include "resource.h"

void DrawSmallStage (Allegro *allegro, Rockman *rockman)
{



}


// Function : move rockman in small stage
void MoveRockmanInSS(Rockman *rockman, Allegro *allegro)
{
    al_get_keyboard_state(&allegro->keyboardState);

    if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_RIGHT))
    {
        rockman->direction = false;
        if ( (allegro->map.pre_x == allegro->map.x) && (allegro->matrix_map[rockman->y + ROCKMAN_H - 10][rockman->x + abs(allegro->map.x) + ROCKMAN_W + 5] == 0))
            rockman->x = rockman->x + rockman->speed;
    }

    else if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_LEFT))
    {
        rockman->direction = true;
        if ( (allegro->map.pre_x == allegro->map.x) && (allegro->matrix_map[rockman->y + ROCKMAN_H][rockman->x + abs(allegro->map.x) - 5] == 0))
            rockman->x = rockman->x - rockman->speed;
    }
    if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_UP))
        rockman->y = rockman->y - rockman->speed;
}



void RockmanStateInSS (Rockman *rockman, Allegro *allegro)
{
    al_get_keyboard_state(&allegro->keyboardState);
    int onLand = 0;
    for (int i = 0; i < ROCKMAN_W; i++)// the 90 is rockman's delta x.
    {
        if (allegro->matrix_map[rockman->y + 106][rockman->x + abs(allegro->map.x) + i] == 0)
            onLand++;
    }
    if(onLand == ROCKMAN_W)
        rockman->state = JUMP;

    else
    {
        if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_RIGHT))
        {
            rockman->state = RUN_RIGHT;
            rockman->direction = false;
        }


        else if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_LEFT))
        {
            rockman->state = RUN_LEFT;
            rockman->direction = true;
        }
    }



}
