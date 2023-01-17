#include "resource.h"

void DrawChooseStage (Allegro *allegro, Boss_1 *boss_1, Boss_2 *boss_2, Boss_3 *boss_3)
{
    al_clear_to_color (al_map_rgb (0, 0, 0));
    DrawSaturn (allegro);
    DrawStar (NUM_STAR, allegro);
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 250, 350, 0, "Clone");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 250, 450, 0, "Necromancer");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 250, 550, 0, "Xai Ya");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 650, 50, 0, "Back");
    DrawArrowInStage (allegro, boss_1, boss_2, boss_3);
    DrawClearStage (allegro);
}

void MoveArrowInStage (Allegro *allegro)
{
    al_get_keyboard_state(&allegro->keyboardState);
    if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_UP) )
    {
        allegro->menu.stage--;
        al_set_sample_instance_playing(allegro->instance6, false); // button music
        al_set_sample_instance_playing(allegro->instance6, true); // button music
    }


    else if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_DOWN) )
    {
        allegro->menu.stage++;
        al_set_sample_instance_playing(allegro->instance6, false); // button music
        al_set_sample_instance_playing(allegro->instance6, true); // button music
    }


    if (allegro->menu.stage > 2)
        allegro->menu.stage = 2;

    if (allegro->menu.stage < 0)
        allegro->menu.stage = 0;

}


void DrawArrowInStage (Allegro *allegro, Boss_1 *boss_1, Boss_2 *boss_2, Boss_3 *boss_3)
{
    switch (allegro->menu.stage)
    {
    case CLONE:
        al_draw_bitmap(allegro->menu.icon_right, 100, 350, 0); // use menu's arrow
        DrawCopymanInStage (boss_1, allegro);
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 500, 550, 0, "Name : X");
        al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 500, 600, 0, "JUST LIKE ROCKMAN.");
        break;

    case 1:
        al_draw_bitmap(allegro->menu.icon_right, 100, 450, 0);
        DrawNecromancerInStage (boss_2, allegro);
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 500, 550, 0, "Name : Simon");
        al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 500, 600, 0, "DEMON ONLY HAS ONE HEART.");
        break;

    case 2:
        al_draw_bitmap(allegro->menu.icon_right, 100, 550, 0);
        DrawXaiYaInStage (boss_3, allegro);
        al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 500, 550, 0, "Name : XaiYa");
        al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 500, 600, 0, "WHAT DID YOU SAY ?");
        break;

    }
}


void EnterInStage (Allegro *allegro, Rockman *rockman, Monster *monster)
{
    al_get_keyboard_state(&allegro->keyboardState);
    if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_ENTER) )
    {
        al_set_sample_instance_playing(allegro->instance8, false);  // turn off taiwan song
        al_set_sample_instance_playing(allegro->instance6, true); // button music
        switch (allegro->menu.stage)
        {
        case CLONE:
            allegro->STATE = SMALL_STAGE;
            allegro->boss_stage = CLONE;
            InitRockman(rockman);
            InitMonster (monster);
            InitMap (allegro);
            al_set_sample_instance_playing(allegro->instance1, true); // open game music
            break;

        case 1:
            allegro->STATE = SMALL_STAGE;
            allegro->boss_stage = NECROMANCER;
            InitRockman(rockman);
            InitMonster (monster);
            InitMap (allegro);
            al_set_sample_instance_playing(allegro->instance1, true); // open game music
            break;

        case 2:
            allegro->STATE = SMALL_STAGE;
            allegro->boss_stage = XAIYA;
            InitRockman(rockman);
            InitMonster (monster);
            InitMap (allegro);
            al_set_sample_instance_playing(allegro->instance1, true); // open game music
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




void DrawNecromancerInStage (Boss_2 *boss_2, Allegro *allegro)
{
    int range1 = allegro->FRAME%60;
    int x = 500;
    int y = 300;

    if ( 0 <= range1 && range1 < 10)
        al_draw_bitmap_region (boss_2->img_idle, 0, 0, 160, 144, x, y, 1);

    else if ( 10 <= range1 && range1 < 20)
        al_draw_bitmap_region (boss_2->img_idle, 160, 0, 160, 144, x, y, 1);

    else if ( 20 <= range1 && range1 < 30)
        al_draw_bitmap_region (boss_2->img_idle, 320, 0, 160, 144, x, y, 1);

    else if ( 30 <= range1 && range1 < 40)
        al_draw_bitmap_region (boss_2->img_idle, 480, 0, 160, 144, x, y, 1);

    else if ( 40 <= range1 && range1 < 50)
        al_draw_bitmap_region (boss_2->img_idle, 640, 0, 160, 144, x, y, 1);

    else if (50 <= range1 && range1 < 60)
        al_draw_bitmap_region (boss_2->img_idle, 800, 0, 160, 144, x, y, 1);
}


void DrawXaiYaInStage (Boss_3 *boss_3, Allegro *allegro)
{
    int range = allegro->FRAME%120;
    int x = 500;
    int y = 300;

    if ( 0 <= range && range < 30)
        al_draw_bitmap (boss_3->img_idle, x, y, 0);

    else if ( 30 <= range && range < 120)
        al_draw_bitmap (boss_3->img_attack, x, y, 0);
}



// Function : draw "new" if stage no passing, or draw "clear";
void DrawClearStage (Allegro *allegro)
{
    switch (allegro->menu.stage)
    {
    case CLONE:
        if (!allegro->pass_stage1)
            al_draw_textf(allegro->font_12, al_map_rgb(220, 0, 0), 220, 370, 1, "NEW");
        else
        {
            al_draw_textf(allegro->font_12, al_map_rgb(0, 200, 200), 220, 370, 1, "CLEAR");
        }
        break;

    case 1:
        if (!allegro->pass_stage2)
            al_draw_textf(allegro->font_12, al_map_rgb(220, 0, 0), 220, 470, 1, "NEW");
        else
        {
            al_draw_textf(allegro->font_12, al_map_rgb(0, 200, 200), 220, 470, 1, "CLEAR");
        }
        break;

    case 2:
        if (!allegro->pass_stage3)
            al_draw_textf(allegro->font_12, al_map_rgb(220, 0, 0), 220, 570, 1, "NEW");
        else
        {
            al_draw_textf(allegro->font_12, al_map_rgb(0, 200, 200), 220, 570, 1, "CLEAR");
        }
        break;

    }
}

