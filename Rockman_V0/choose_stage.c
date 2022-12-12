#include "resource.h"

void DrawChooseStage (Allegro *allegro)
{
    al_clear_to_color (al_map_rgb (0, 0, 0));
    DrawStar (NUM_STAR, allegro);
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 250, 350, 0, "CLONE");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 250, 450, 0, "BOSS 2");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 250, 550, 0, "BOSS 3");
    DrawArrowInStage (allegro);
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


void DrawArrowInStage (Allegro *allegro)
{
    switch (allegro->menu.stage)
    {
    case CLONE:
        al_draw_bitmap(allegro->menu.icon_right, 200, 350, 0); // use menu's arrow
        break;

    case 1:
        al_draw_bitmap(allegro->menu.icon_right, 200, 450, 0);
        break;

    case 2:
        al_draw_bitmap(allegro->menu.icon_right, 200, 550, 0);
        break;

    }
}


void EnterInStage (Allegro *allegro)
{
    al_get_keyboard_state(&allegro->keyboardState);
    if ( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_ENTER) )
    {
        switch (allegro->menu.stage)
        {
        case CLONE:
            allegro->STATE = SMALL_STAGE;
            break;

        case 1:

            break;

        case 2:

            break;
        }
    }
}
