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
    al_reserve_samples(9);
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
    allegro->time_story001 = 300;

    allegro->font_96 = al_load_font("./data/m5x7.ttf", 60, 0);
    allegro->font_24 = al_load_font("./data/m5x7.ttf", 48, 0);
    allegro->font_36 = al_load_font("./data/m5x7.ttf", 36, 0);
    allegro->font_12 = al_load_font("./data/m5x7.ttf", 24, 0);
    InitStart (allegro);
    InitMenu (allegro);
    InitStar (NUM_STAR, allegro);
    InitMap (allegro);
    ReadMapData (allegro);
    allegro->rule.left  = al_load_bitmap ("./picture/left_normal.png");
    allegro->rule.right  = al_load_bitmap ("./picture/right_normal.png");
    allegro->rule.up  = al_load_bitmap ("./picture/up_normal.png");
    allegro->rule.space  = al_load_bitmap ("./picture/space.png");
    allegro->rule.right_light  = al_load_bitmap ("./picture/right_light.png");
    allegro->rule.left_light  = al_load_bitmap ("./picture/left_light.png");
    allegro->rule.up_light  = al_load_bitmap ("./picture/up_light.png");
    allegro->rule.space_light  = al_load_bitmap ("./picture/space_light.png");
    allegro->defeat  = al_load_bitmap ("./picture/loser.png");
    allegro->victory  = al_load_bitmap ("./picture/win.png");
    allegro->johnwu001 = al_load_bitmap ("./picture/johnwu001.png");
    allegro->johnwu002 = al_load_bitmap ("./picture/johnwu002.png");
    allegro->jyunwei = al_load_bitmap ("./picture/jyunwei.png");
    allegro->yangjyun = al_load_bitmap ("./picture/yangjyun.png");

    allegro->sample_stage = al_load_sample("./data/music/Elec-Man-Stage.wav");
    allegro->instance1 = al_create_sample_instance (allegro->sample_stage);
    voice_init( allegro->instance1, &(allegro->mixer1), &(allegro->voice1));
    al_set_sample_instance_gain(allegro->instance1, 1);
    al_set_sample_instance_playmode(allegro->instance1, ALLEGRO_PLAYMODE_LOOP);
    allegro->sample_boss1 = al_load_sample("./data/music/WilyFortres 1.wav");
    allegro->instance2 = al_create_sample_instance (allegro->sample_boss1);
    voice_init( allegro->instance2, &(allegro->mixer2), &(allegro->voice2));
    al_set_sample_instance_gain(allegro->instance2, 1);
    al_set_sample_instance_playmode(allegro->instance2, ALLEGRO_PLAYMODE_LOOP);
    allegro->sample_boss2 = al_load_sample("./data/music/WilyFortres 2.wav");
    allegro->instance3 = al_create_sample_instance (allegro->sample_boss2);
    voice_init( allegro->instance3, &(allegro->mixer3), &(allegro->voice3));
    al_set_sample_instance_gain(allegro->instance3, 1);
    al_set_sample_instance_playmode(allegro->instance3, ALLEGRO_PLAYMODE_LOOP);
    allegro->sample_boss3 = al_load_sample("./data/music/WilyFortres 3.wav");
    allegro->instance4 = al_create_sample_instance (allegro->sample_boss3);
    voice_init( allegro->instance4, &(allegro->mixer4), &(allegro->voice4));
    al_set_sample_instance_gain(allegro->instance4, 1);
    al_set_sample_instance_playmode(allegro->instance4, ALLEGRO_PLAYMODE_LOOP);
    allegro->sample_win = al_load_sample("./data/music/victory.wav");
    allegro->instance5 = al_create_sample_instance (allegro->sample_win);
    voice_init( allegro->instance5, &(allegro->mixer5), &(allegro->voice5));
    al_set_sample_instance_gain(allegro->instance5, 1);
    al_set_sample_instance_playmode(allegro->instance5, ALLEGRO_PLAYMODE_ONCE);
    allegro->sample_button = al_load_sample("./data/music/button.wav");
    allegro->instance6 = al_create_sample_instance (allegro->sample_button);
    voice_init( allegro->instance6, &(allegro->mixer6), &(allegro->voice6));
    al_set_sample_instance_gain(allegro->instance6, 1);
    al_set_sample_instance_playmode(allegro->instance6, ALLEGRO_PLAYMODE_ONCE);
    allegro->sample_beep = al_load_sample("./data/music/beep.wav");
    allegro->instance7 = al_create_sample_instance (allegro->sample_beep);
    voice_init( allegro->instance7, &(allegro->mixer7), &(allegro->voice7));
    al_set_sample_instance_gain(allegro->instance7, 1);
    al_set_sample_instance_playmode(allegro->instance7, ALLEGRO_PLAYMODE_LOOP);
    allegro->sample_taiwan = al_load_sample("./data/music/Taiwan.wav");
    allegro->instance8 = al_create_sample_instance (allegro->sample_taiwan);
    voice_init( allegro->instance8, &(allegro->mixer8), &(allegro->voice8));
    al_set_sample_instance_gain(allegro->instance8, 0.6);
    al_set_sample_instance_playmode(allegro->instance8, ALLEGRO_PLAYMODE_LOOP);
    allegro->story001 = al_load_sample("./data/music/Conan001.wav");
    allegro->instance9 = al_create_sample_instance (allegro->story001);
    voice_init( allegro->instance9, &(allegro->mixer9), &(allegro->voice9));
    al_set_sample_instance_gain(allegro->instance9, 1);
    al_set_sample_instance_playmode(allegro->instance9, ALLEGRO_PLAYMODE_LOOP);
    allegro->story002 = al_load_sample("./data/music/Conan002.wav");
    allegro->instance10 = al_create_sample_instance (allegro->story002);
    voice_init( allegro->instance10, &(allegro->mixer10), &(allegro->voice10));
    al_set_sample_instance_gain(allegro->instance10, 1);
    al_set_sample_instance_playmode(allegro->instance10, ALLEGRO_PLAYMODE_LOOP);

    al_set_sample_instance_playing(allegro->instance7, true);  //music for start
    ReadScoreCSV (allegro);
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
                EventCheckKeyDown (allegro, rockman, monster);
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
                    al_clear_to_color (al_map_rgb(0, 0, 0));
                    DrawRule (allegro, rockman);

                    RockmanJumpInBoss (rockman, allegro);
                    RockmanStateInBoss (rockman, allegro);
                    MoveRockmanInBoss (rockman, allegro);
                    MoveBullet (rockman);
                    CheckBulletOver (rockman);
                    LimitRockmanInBoss (rockman);

                    DrawBullet (rockman);
                    DrawRockman (rockman, allegro);
                    break;

                case SMALL_STAGE:
                    StageSmall (rockman, allegro, boss_1, boss_2, boss_3, monster);
                    break;

                case BOSS_1:
                    StageBoss_1 (boss_1, rockman, allegro);
                    break;

                case BOSS_2:
                    StageBoss_2 (boss_2, rockman, allegro);
                    break;

                case BOSS_3:
                    StageBoss_3 (boss_3, rockman, allegro);
                    break;

                case LOADING:
                    LoadingFinish (allegro, rockman);
                    DrawLoading (allegro);

                    break;

                case CONTINUE:
                    DrawGameFinish (allegro, rockman);
                    break;

                case STORY:
                    DrawStory (allegro, rockman);
                    break;

                case SCOREBOARD:
                    DrawScoreBoard (allegro);
                    break;

                case TYPE:
                    DrawTypeName (allegro);
                    break;
                }


                break;
            }
        }
    }
}



void voice_init(ALLEGRO_SAMPLE_INSTANCE *instance, ALLEGRO_MIXER **mixer, ALLEGRO_VOICE **voice)
{
    *mixer = al_create_mixer(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    *voice = al_create_voice(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    al_attach_sample_instance_to_mixer(instance, *mixer);
    al_attach_mixer_to_voice(*mixer, *voice);
}



void EventCheckKeyDown (Allegro *allegro, Rockman *rockman, Monster *monster)
{
    al_get_keyboard_state(&allegro->keyboardState);
    switch (allegro->STATE)
    {
    case START:
        if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_ENTER) )
        {
            allegro->STATE = MENU;
            al_set_sample_instance_playing(allegro->instance7, false); // turn off beep song
            al_set_sample_instance_playing(allegro->instance8, true);  // turn on taiwan song
            al_set_sample_instance_playing(allegro->instance6, true);
        }
        break;

    case MENU:
        MoveArrowInMenu (allegro);
        EnterInMenu (allegro, rockman);
        break;

    case STAGE:
        MoveArrowInStage (allegro);
        EnterInStage (allegro, rockman, monster);
        if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_BACKSPACE) )
        {
            allegro->STATE = MENU;
            al_set_sample_instance_playing(allegro->instance6, true);
        }
        break;

    case STORY:
        if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_BACKSPACE) )
        {
            allegro->STATE = MENU;
            al_set_sample_instance_playing(allegro->instance6, true);
            al_set_sample_instance_playing(allegro->instance8, true);  // turn on taiwan song
            al_set_sample_instance_playing(allegro->instance9, false);  //turn off music
            al_set_sample_instance_playing(allegro->instance10, false);  //turn off music
        }
        break;

    case SCOREBOARD:
        if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_BACKSPACE) )
        {
            allegro->STATE = MENU;
            al_set_sample_instance_playing(allegro->instance6, true);
        }
        if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_ENTER) && (allegro->can_type_name==1) )
        {
            allegro->STATE = TYPE;
            allegro->can_type_name = -1;
        }

        break;

    case TYPE:
        CheckKeyboardDown (allegro);
        break;

    case RULE:
        if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_BACKSPACE) )
        {
            allegro->STATE = MENU;
            al_set_sample_instance_playing(allegro->instance6, true);
        }

        if( al_key_down(&allegro->keyboardState, ALLEGRO_KEY_SPACE) )
            CreateBullet (rockman);
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
}




