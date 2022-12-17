#include "resource.h"


/** Function : Memery allocation for struct of Allegro */
Allegro *CallocAllegro()
{
    Allegro *addr = (Allegro *)calloc(1, sizeof(Allegro));
    return addr;
}


/** Function : Initialize all basic function */
void AllegroDriverInit(Allegro *allegro)
{
    /* first, set up Allegro and the graphics mode */
    al_init();             // initialize Allegro
    al_install_keyboard(); // install the keyboard for Allegro to use
    al_init_image_addon();
    al_install_audio();     // install sound driver
    al_init_acodec_addon();
    al_install_mouse();
    al_init_font_addon(); // install font addons
    al_init_ttf_addon();  // TureType Font addon also support .ttc
    al_init_native_dialog_addon();
    al_init_primitives_addon();
    //al_reserve_samples(2);
    srand( time(NULL) );

    allegro->display = al_create_display(WINDOWS_W, WINDOWS_H);
    al_set_window_title(allegro->display, " Rockman ");
    al_set_window_position(allegro->display, 780, 220);

    /* Envent queue **/
    allegro->timer = al_create_timer(1.0 / FPS);
    allegro->event_queue = al_create_event_queue();
    al_register_event_source(allegro->event_queue, al_get_mouse_event_source());
    al_register_event_source(allegro->event_queue, al_get_display_event_source(allegro->display));
    al_register_event_source(allegro->event_queue, al_get_keyboard_event_source());
    al_register_event_source(allegro->event_queue, al_get_timer_event_source(allegro->timer));
    al_start_timer(allegro->timer);

    allegro->finish = false;
    allegro->FRAME = 0;
    allegro->STATE = START;
    allegro->menu.state = M_CHOOSE_STAGE;
    allegro->menu.stage = CLONE;

    allegro->font_24 = al_load_font("./data/m5x7.ttf", 48, 0);
    InitStart (allegro);
    InitMenu (allegro);
    InitStar (NUM_STAR, allegro);
    InitMap (allegro);
    ReadMapData (allegro);
}



void EventCheck(Allegro *allegro, Rockman *rockman, Monster *monster, Boss_1 *boss_1, Boss_2 *boss_2, Boss_3 *boss_3)
{
    if (!al_is_event_queue_empty(allegro->event_queue))
    {
        while (al_get_next_event(allegro->event_queue, &allegro->events))
        {
            switch (allegro->events.type)
            {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                allegro->finish = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN: /** key down */
                al_get_keyboard_state(&allegro->keyboardState);
                switch (allegro->STATE)
                {
                case START:
                    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_ENTER) )
                        allegro->STATE = MENU;
                    break;

                case MENU:
                    MoveArrowInMenu (allegro);
                    EnterInMenu (allegro);
                    break;

                case STAGE:
                    MoveArrowInStage (allegro);
                    EnterInStage (allegro, rockman, monster);
                    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_BACKSPACE) )
                        allegro->STATE = MENU;
                    break;

                case RULE:
                    break;

                case BOSS_1:
                    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_SPACE) )
                        CreateBullet (rockman);
                    break;

                case BOSS_2:
                    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_SPACE) )
                        CreateBullet (rockman);
                    break;

                case BOSS_3:
                    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_SPACE) )
                        CreateBullet (rockman);
                    break;

                case SMALL_STAGE:
                    if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_SPACE) )
                        CreateBullet (rockman);
                    break;

                }
                break;

            case ALLEGRO_EVENT_KEY_UP:
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                printf("x = %d, y = %d\n", allegro->events.mouse.x, allegro->events.mouse.y);
                printf("map = %d \n", allegro->matrix_map[allegro->events.mouse.y][allegro->events.mouse.x + 40]);
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                break;

            case ALLEGRO_EVENT_TIMER: /** timer */
                allegro->FRAME++; // count the frame

                switch (allegro->STATE)
                {
                case START:
                    DrawStart (rockman, allegro);
                    break;

                case MENU:
                    DrawMenu (allegro);
                    break;

                case STAGE:
                    DrawChooseStage (allegro, boss_1, boss_2, boss_3);
                    break;

                case RULE:
                    break;

                case SMALL_STAGE:
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

                    al_draw_bitmap (allegro->map.img, allegro->map.x, allegro->map.y, 0);
                    DrawDoorInSS (allegro);
                    DrawBullet (rockman);
                    DrawRockman (rockman, allegro);
                    //DrawMonster (monster, allegro);
                    DrawSkull (monster, allegro);
                    DrawFireSkull (monster, allegro);
                    DrawRockmanHP (rockman);
                    PassSmallStage (rockman, allegro);
                    CheckAlive (rockman, allegro);
                    break;

                case BOSS_1:
                    RockmanJumpInBoss (rockman, allegro);
                    RockmanStateInBoss (rockman, allegro);
                    MoveRockmanInBoss (rockman, allegro);
                    MoveBullet (rockman);
                    MoveBoss_1 (boss_1);
                    CheckBulletOver (rockman);
                    BulletCrushBoss_1 (boss_1, rockman);
                    RockmanCollideBoss_1 (rockman, boss_1);
                    MoveMinion (boss_1);
                    LimitRockmanInBoss (rockman);

                    al_draw_bitmap (boss_1->background, 0, 0, 0);
                    DrawBullet (rockman);
                    DrawRockman (rockman, allegro);
                    DrawBoss_1 (boss_1, allegro);
                    DrawRockmanHP (rockman);
                    DrawMinion (boss_1, allegro);
                    DrawBoss_1HP (boss_1);

                    CheckAlive (rockman, allegro);
                    CheckBoss_1Alive (boss_1, allegro);
                    break;

                case BOSS_2:
                    RockmanJumpInBoss (rockman, allegro);
                    RockmanStateInBoss (rockman, allegro);
                    MoveRockmanInBoss (rockman, allegro);
                    MoveBullet (rockman);
                    CheckBulletOver (rockman);
                    StateBoss_2 (boss_2, allegro, rockman);
                    BulletCollideBoss_2 (rockman, boss_2);
                    LimitRockmanInBoss (rockman);

                    al_draw_bitmap (boss_2->background, 0, 0, 0);
                    DrawBoss_2HP (boss_2);
                    DrawBullet (rockman);
                    DrawRockman (rockman, allegro);
                    DrawRockmanHP (rockman);
                    DrawBoss_2 (boss_2, allegro, rockman);

                    CheckAlive (rockman, allegro);
                    CheckBoss_2Alive (boss_2, allegro);
                    break;

                case BOSS_3:
                    RockmanJumpInBoss (rockman, allegro);
                    RockmanStateInBoss (rockman, allegro);
                    MoveRockmanInBoss (rockman, allegro);
                    MoveBullet (rockman);
                    CheckBulletOver (rockman);
                    LimitRockmanInBoss (rockman);
                    MoveNormalYA (boss_3);

                    al_clear_to_color (al_map_rgb(0,0,0));
                    DrawBullet (rockman);
                    DrawRockman (rockman, allegro);
                    DrawRockmanHP (rockman);
                    DrawBoss_3 (boss_3, allegro);
                    DrawExplosion (boss_3, allegro);
                    break;

                case LOADING:
                    LoadingFinish (allegro);
                    DrawLoading (allegro);

                    break;

                case CONTINUE:
                    DrawGameFinish (allegro, rockman);
                    break;
                }


                break;
            }
        }
    }
}



