#include "resource.h"

void DrawChooseStage (Allegro *allegro, Boss_1 *boss_1)
{
    al_clear_to_color (al_map_rgb (0, 0, 0));
    DrawStar (NUM_STAR, allegro);
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 250, 350, 0, "CLONE");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 250, 450, 0, "BOSS 2");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 250, 550, 0, "BOSS 3");
    DrawArrowInStage (allegro, boss_1);
    DrawSaturn (allegro);
}

void MoveArrowInStage (Allegro *allegro)
{
    al_get_keyboard_state(&allegro->keyboardState);
    if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_UP) )
        allegro->menu.stage--;

    else if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_DOWN) )
        allegro->menu.stage++;

    if (allegro->menu.stage > 2)
        allegro->menu.stage = 2;

    if (allegro->menu.stage < 0)
        allegro->menu.stage = 0;

}


void DrawArrowInStage (Allegro *allegro, Boss_1 *boss_1)
{
    switch (allegro->menu.stage)
    {
    case CLONE:
        al_draw_bitmap(allegro->menu.icon_right, 200, 350, 0); // use menu's arrow
        DrawCopymanInStage (boss_1, allegro);
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 500, 450, 1, "Name : X");
        break;

    case 1:
        al_draw_bitmap(allegro->menu.icon_right, 200, 450, 0);
        break;

    case 2:
        al_draw_bitmap(allegro->menu.icon_right, 200, 550, 0);
        break;

    }
}


void EnterInStage (Allegro *allegro, Rockman *rockman, Boss_1 *boss_1)
{
    al_get_keyboard_state(&allegro->keyboardState);
    if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_ENTER) )
    {
        switch (allegro->menu.stage)
        {
        case CLONE:
            allegro->STATE = SMALL_STAGE;
            allegro->boss_stage = CLONE;
            InitRockman(rockman);
            InitBoss_1 (boss_1);
            InitMap (allegro);
            break;

        case 1:

            break;

        case 2:

            break;
        }
    }
}


void DrawCopymanInStage (Boss_1 *boss_1, Allegro *allegro)
{
    int range_stand = allegro->FRAME%120;
    int x = 500;
    int y = 300;

    if ( 0 <= range_stand && range_stand < 100)
        al_draw_bitmap_region (boss_1->img, 6, 3, 74, 105, x, y, 0);

    else if ( 100 <= range_stand && range_stand < 120)
        al_draw_bitmap_region (boss_1->img, 122, 3, 73, 105, x, y, 0);
}
