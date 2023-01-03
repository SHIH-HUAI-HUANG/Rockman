#include "resource.h"
/**
the Small Stage
kill the monster to pass the stage.
*/


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
    if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_UP) && rockman->y > 5)//avoid to over the celling
    {
        if ( (allegro->matrix_map[rockman->y - 5][rockman->x + abs(allegro->map.x)]==0) && (allegro->matrix_map[rockman->y - 5][rockman->x + abs(allegro->map.x) + 90]==0) ) // avoid to crush the head
            rockman->y = rockman->y - rockman->speed;
    }
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



void DropInAbyss (Rockman *rockman, Allegro *allegro)
{
    if (rockman->y +ROCKMAN_H > 715)
    {
        allegro->STATE = LOADING;
        allegro->frame_flag = allegro->FRAME;
        rockman->HP = 0;
    }
}

/** the door to the boss stage */
void DrawDoorInSS (Allegro* allegro)
{
    int range = allegro->FRAME%60;
    if ( 0 <= range && range < 30)
        al_draw_filled_rectangle (allegro->map.x + 6110, 35, allegro->map.x + 6200, 185, al_map_rgb(255, 255, 255));

    al_draw_textf(allegro->font_24, al_map_rgb(0, 0, 0), allegro->map.x + 6155, 80, 1, "UP !!");
}



void PassSmallStage (Rockman *rockman, Allegro *allegro, Boss_1 *boss_1, Boss_2 *boss_2, Boss_3 *boss_3)
{
    al_get_keyboard_state(&allegro->keyboardState);
    int x = rockman->x + ROCKMAN_W/2;
    int y = rockman->y + ROCKMAN_H/2;
    if ( abs(x - (allegro->map.x + 6110)) < (45 + ROCKMAN_W/2) && abs(y - 110) < (75 + ROCKMAN_H/2) )
    {
        if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_UP))
        {
            switch(allegro->boss_stage)
            {
            case CLONE:
                allegro->STATE = BOSS_1;
                InitRockmanInBoss_1 (rockman);
                InitBoss_1 (boss_1);
                al_set_sample_instance_playing(allegro->instance1, false); // close game music
                al_set_sample_instance_playing(allegro->instance2, true); // open game music
                break;

            case NECROMANCER:
                allegro->STATE = BOSS_2;
                InitRockmanInBoss_2 (rockman);
                InitBoss_2 (boss_2);
                al_set_sample_instance_playing(allegro->instance1, false); // close game music
                al_set_sample_instance_playing(allegro->instance3, true); // open game music
                break;

            case XAIYA:
                allegro->STATE = BOSS_3;
                InitRockmanInBoss_3 (rockman);
                InitBoss_3 (boss_3);
                al_set_sample_instance_playing(allegro->instance1, false); // close game music
                al_set_sample_instance_playing(allegro->instance4, true); // open game music
                break;
            }
        }
    }
}


void StageSmall (Rockman *rockman, Allegro *allegro, Boss_1 *boss_1, Boss_2 *boss_2, Boss_3 *boss_3, Monster *monster)
{
    rockman->state = STAND;
    Gravity (allegro, rockman);
    DropInAbyss (rockman, allegro);

    MoveMap (allegro, rockman);
    RockmanStateInSS (rockman, allegro);
    MoveRockmanInSS (rockman, allegro);
    MoveBullet (rockman);
    CheckBulletOver (rockman);
    MoveSkull (monster);
    MoveFireSkull (monster);
    BulletCrushMonster (monster, rockman, allegro);
    MonsterCrushRockman (monster, rockman, allegro);
    RockmanSufferDamage (rockman);

    al_draw_bitmap (allegro->map.img, allegro->map.x, allegro->map.y, 0);
    DrawDoorInSS (allegro);
    DrawBullet (rockman);
    DrawRockman (rockman, allegro);
    DrawSkull (monster, allegro);
    DrawFireSkull (monster, allegro);
    DrawRockmanHP (rockman);
    PassSmallStage (rockman, allegro, boss_1, boss_2, boss_3);
    CheckAlive (rockman, allegro);
}

