#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> // graph
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h> // communicate windows
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h> // draw line



#define WINDOWS_W 768
#define WINDOWS_H 725
#define FPS 60
#define SPEED 4
#define NUM_BULLET 50
#define JUMP_TIME 60
#define ATTACK_TIME 15
#define NUM_STAR 50
#define ROCKMAN_W 90
#define ROCKMAN_H 105
#define NUM_MONSTER 10


typedef struct Minion
{
    int x;
    int y;
    int speed_x;
    int speed_y;
    bool direction_x;
    bool direction_y;
    ALLEGRO_BITMAP *img;

} Minion;


typedef struct Map
{
    int x;
    int y;
    int pre_x;
    int pre_y;
    int speed;
    ALLEGRO_BITMAP *img;

} Map;


typedef struct Star
{
    int x;
    int y;
    int r;
} Star;


typedef struct Bullet
{
    int x;
    int y;
    bool activity;
    bool direction;

} Bullet;

typedef struct Monster
{
    int x;
    int y;
    int standard_x;
    int standard_y;
    int speed;
    int delta_x;
    bool direction;
    bool direction_y;
    bool alive;
    int role;

    ALLEGRO_BITMAP *img;
} Monster;

typedef struct Rockman
{
    int x;
    int y;
    int speed;
    int state;
    int jump_time;
    int attack_time;
    int HP;

    bool direction;
    ALLEGRO_BITMAP *img;
    Bullet bullet[NUM_BULLET];

} Rockman;


typedef struct Boss_1
{
    int x;
    int y;
    int speed;
    int state;
    int jump_time;
    int HP;

    bool direction;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *background;
    Bullet bullet[NUM_BULLET];

    Minion minion;

} Boss_1;


typedef struct Boss_2
{
    int x;
    int y;
    int speed;
    int state;
    int HP;
    bool direction;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *background;
} Boss_2;


typedef struct Start
{
    ALLEGRO_BITMAP *mark_megaman;
    ALLEGRO_BITMAP *earth;

} Start;

typedef struct Menu
{
    int state;
    int stage; // the boss stage
    ALLEGRO_BITMAP *icon_right;
    ALLEGRO_BITMAP *saturn;

} Menu;

typedef struct Allegro
{
    ALLEGRO_EVENT events;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_KEYBOARD_STATE keyboardState;
    ALLEGRO_TIMER *timer;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font_24;
    bool finish;
    int FRAME;
    int STATE;
    int frame_flag;
    int boss_stage;

    Start start;
    Menu menu;
    Star star[NUM_STAR];
    Map map;
    int matrix_map[725][6200];

} Allegro;



typedef enum
{
    STAND,
    RUN_RIGHT,
    RUN_LEFT,
    JUMP,
    ATTACK

} State_rockman;

typedef enum
{
    START,
    MENU,
    RULE,
    STAGE,
    GAME,
    SMALL_STAGE,
    BOSS_1,
    LOADING,
    CONTINUE

} State_game;


typedef enum
{
    M_CHOOSE_STAGE,
    M_RULE,
    M_EXIT

} State_menu;

typedef enum
{
    CLONE,
    BOSS_2,
    BOSS_3

} State_Stage;



/** allegro */
Allegro *CallocAllegro();
void AllegroDriverInit(Allegro *allegro);
void EventCheck(Allegro *allegro, Rockman *rockman, Boss_1 *boss_1, Monster *monster);


/** rockman */
Rockman *CallocRockman();
void InitRockman (Rockman *rockman);
void DrawRockman (Rockman *rockman, Allegro *allegro);
void RockmanStateInBoss (Rockman *rockman, Allegro *allegro);
void MoveRockmanInBoss(Rockman *rockman, Allegro *allegro);
void RockmanJumpInBoss (Rockman *rockman, Allegro *allegro);
void DrawRockmanHP (Rockman *rockman);
void CheckAlive (Rockman *rockman, Allegro *allegro);


void CreateBullet (Rockman *rockman);
void DrawBullet (Rockman *rockman);
void MoveBullet (Rockman *rockman);
void CheckBulletOver (Rockman *rockman);


/** CopyMan / Boss1 */
Boss_1 *CallocBoss_1();
void InitBoss_1 (Boss_1 *boss_1);
void DrawBoss_1 (Boss_1 *boss_1, Allegro *allegro);
void MoveBoss_1 (Boss_1 *boss_1);
void BulletCrushBoss_1 (Boss_1 *boss_1, Rockman *rockman);
void InitRockmanInBoss_1 (Rockman * rockman);
void RockmanCollideBoss_1 (Rockman *rockman, Boss_1 *boss_1);
void DrawMinion (Boss_1 *boss_1, Allegro *allegro);
void MoveMinion (Boss_1 *boss_1);
void DrawBoss_1HP (Boss_1 *boss_1);
void CheckBoss_1Alive (Boss_1 *boss_1, Allegro *allegro);
void RockmanCollideMinion (Rockman *rockman, Boss_1 *boss_1);


/** Start */
void DrawRockmanInStart (Rockman *rockman, Allegro *allegro);
void DrawTextInStart (Allegro *allegro);
void InitStart (Allegro *allegro);
void DrawStart (Rockman *rockman, Allegro *allegro);
void DrawEarth (Allegro *allegro);
void InitStar (int number, Allegro *allegro);
void DrawStar (int number, Allegro *allegro);


/** Menu */
void DrawMenu (Allegro *allegro);
void MoveArrowInMenu (Allegro *allegro);
void InitMenu (Allegro *allegro);
void DrawArrowInMenu (Allegro *allegro);
void DrawSaturn (Allegro *allegro);
void EnterInMenu (Allegro *allegro);


/** choose stage */
void DrawChooseStage (Allegro *allegro, Boss_1 *boss_1);
void MoveArrowInStage (Allegro *allegro);
void DrawArrowInStage (Allegro *allegro, Boss_1 *boss_1);
void EnterInStage (Allegro *allegro, Rockman *rockman, Boss_1 *boss_1);
void DrawCopymanInStage (Boss_1 *boss_1, Allegro *allegro);



/** Map */
void InitMap (Allegro *allegro);
void ReadMapData (Allegro *allegro);
void Gravity (Allegro *allegro, Rockman *rockman);
void MoveMap(Allegro *allegro, Rockman *rockman);


/** small stage */
void MoveRockmanInSS(Rockman *rockman, Allegro *allegro);
void RockmanStateInSS (Rockman *rockman, Allegro *allegro);
void DropInAbyss (Rockman *rockman, Allegro *allegro);
void DrawDoorInSS (Allegro* allegro);
void PassSmallStage (Rockman *rockman, Allegro *allegro);


/** Loading */
void DrawLoading (Allegro *allegro);
void DrawProgressBar (Allegro *allegro);
void LoadingFinish (Allegro *allegro);



/** Game finish */
void DrawGameFinish (Allegro *allegro, Rockman *rockman);
void DrawContinue (Allegro *allegro);



/** Monster */
Monster *CallocMonster (int number);
void InitMonster (Monster *monster);
void DrawMonster (Monster *monster, Allegro *allegro);
void MoveSkull (Monster *monster);
void DrawSkull (Monster *monster, Allegro *allegro);
void MoveFireSkull (Monster *monster);
void DrawFireSkull (Monster *monster, Allegro *allegro);
void BulletCrushMonster (Monster *monster, Rockman *rockman, Allegro *allegro);
void MonsterCrushRockman (Monster *monster, Rockman *rockman, Allegro *allegro);

