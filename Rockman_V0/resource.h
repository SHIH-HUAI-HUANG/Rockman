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


typedef struct Player
{
    char name[20];

} Player;

typedef struct Explosion
{
    float x;
    float y;
    int times;

} Explosion;

typedef struct Rule
{
    ALLEGRO_BITMAP *right;
    ALLEGRO_BITMAP *left;
    ALLEGRO_BITMAP *up;
    ALLEGRO_BITMAP *space;
    ALLEGRO_BITMAP *right_light;
    ALLEGRO_BITMAP *left_light;
    ALLEGRO_BITMAP *up_light;
    ALLEGRO_BITMAP *space_light;

} Rule;

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
    float x;
    float y;
    float speed_x;
    float speed_y;
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
    int record_HP;
    int time_hurt;

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
    ALLEGRO_BITMAP *img_idle;
    ALLEGRO_BITMAP *img_attack;
    ALLEGRO_BITMAP *background;

    int time_idle;
    int time_attack;
} Boss_2;



typedef struct Boss_3
{
    int x;
    int y;
    int speed_x;
    int speed_y;
    int state;
    int HP;
    int HP_2;
    bool direction_x;
    bool direction_y;
    int time_crazy_attack;
    ALLEGRO_BITMAP *img_idle;
    ALLEGRO_BITMAP *img_attack;
    ALLEGRO_BITMAP *background1;
    ALLEGRO_BITMAP *background2;
    ALLEGRO_BITMAP *explosion;

    Bullet bullet;
    Explosion boom[20]; // buffer of boom

} Boss_3;


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
    ALLEGRO_FONT *font_96;
    ALLEGRO_FONT *font_24;
    ALLEGRO_FONT *font_36;
    ALLEGRO_FONT *font_12;
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
    int state_story;
    int time_story001;
    int time_story002;
    int time_story003;
    bool pass_stage1;
    bool pass_stage2;
    bool pass_stage3;
    Rule rule;
    ALLEGRO_BITMAP *defeat;
    ALLEGRO_BITMAP *victory;
    ALLEGRO_BITMAP *johnwu001;
    ALLEGRO_BITMAP *johnwu002;
    ALLEGRO_BITMAP *jyunwei;
    ALLEGRO_BITMAP *yangjyun;

    ALLEGRO_SAMPLE *sample_stage;
    ALLEGRO_SAMPLE_INSTANCE *instance1;
    ALLEGRO_MIXER *mixer1;
    ALLEGRO_VOICE *voice1;
    ALLEGRO_SAMPLE *sample_boss1;
    ALLEGRO_SAMPLE_INSTANCE *instance2;
    ALLEGRO_MIXER *mixer2;
    ALLEGRO_VOICE *voice2;
    ALLEGRO_SAMPLE *sample_boss2;
    ALLEGRO_SAMPLE_INSTANCE *instance3;
    ALLEGRO_MIXER *mixer3;
    ALLEGRO_VOICE *voice3;
    ALLEGRO_SAMPLE *sample_boss3;
    ALLEGRO_SAMPLE_INSTANCE *instance4;
    ALLEGRO_MIXER *mixer4;
    ALLEGRO_VOICE *voice4;
    ALLEGRO_SAMPLE *sample_win;
    ALLEGRO_SAMPLE_INSTANCE *instance5;
    ALLEGRO_MIXER *mixer5;
    ALLEGRO_VOICE *voice5;
    ALLEGRO_SAMPLE *sample_button;
    ALLEGRO_SAMPLE_INSTANCE *instance6;
    ALLEGRO_MIXER *mixer6;
    ALLEGRO_VOICE *voice6;
    ALLEGRO_SAMPLE *sample_beep;
    ALLEGRO_SAMPLE_INSTANCE *instance7;
    ALLEGRO_MIXER *mixer7;
    ALLEGRO_VOICE *voice7;
    ALLEGRO_SAMPLE *sample_taiwan;
    ALLEGRO_SAMPLE_INSTANCE *instance8;
    ALLEGRO_MIXER *mixer8;
    ALLEGRO_VOICE *voice8;
    ALLEGRO_SAMPLE *story001;
    ALLEGRO_SAMPLE_INSTANCE *instance9;
    ALLEGRO_MIXER *mixer9;
    ALLEGRO_VOICE *voice9;
    ALLEGRO_SAMPLE *story002;
    ALLEGRO_SAMPLE_INSTANCE *instance10;
    ALLEGRO_MIXER *mixer10;
    ALLEGRO_VOICE *voice10;

    Player player[20]; // store from scoreboard.csv
    char name[20];
    int name_length;
    int number_scoreboard;
    int can_type_name;

} Allegro;



typedef enum
{
    STAND,
    RUN_RIGHT,
    RUN_LEFT,
    JUMP,
    ATTACK,
    HURT

} State_rockman;



typedef enum
{
    START,
    MENU,
    RULE,
    STORY,
    STAGE,
    GAME,
    SMALL_STAGE,
    BOSS_1,
    BOSS_2,
    BOSS_3,
    LOADING,
    CONTINUE,
    SCOREBOARD,
    TYPE

} State_game;


typedef enum
{
    M_CHOOSE_STAGE,
    M_RULE,
    M_STORY,
    M_BOARD,
    M_EXIT

} State_menu;

typedef enum
{
    CLONE,
    NECROMANCER,
    XAIYA

} State_Stage;



/** allegro */
Allegro *CallocAllegro();
void AllegroDriverInit(Allegro *allegro);
void EventCheck(Allegro *allegro, Rockman *rockman, Monster *monster, Boss_1 *boss_1, Boss_2 *boss_2, Boss_3 *boss_3);
void EventCheckKeyDown (Allegro *allegro, Rockman *rockman, Monster *monster);

/** rockman */
Rockman *CallocRockman();
void InitRockman (Rockman *rockman);
void DrawRockman (Rockman *rockman, Allegro *allegro);
void RockmanStateInBoss (Rockman *rockman, Allegro *allegro);
void MoveRockmanInBoss(Rockman *rockman, Allegro *allegro);
void RockmanJumpInBoss (Rockman *rockman, Allegro *allegro);
void DrawRockmanHP (Rockman *rockman);
void CheckAlive (Rockman *rockman, Allegro *allegro);
void LimitRockmanInBoss (Rockman *rockman);
void RockmanSufferDamage (Rockman *rockman);
void RockmanHurtInBoss (Rockman *rockman);

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
void StageBoss_1 (Boss_1 *boss_1, Rockman *rockman, Allegro *allegro);

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
void EnterInMenu (Allegro *allegro, Rockman *rockman);


/** choose stage */
void DrawChooseStage (Allegro *allegro, Boss_1 *boss_1, Boss_2 *boss_2, Boss_3 *boss_3);
void MoveArrowInStage (Allegro *allegro);
void DrawArrowInStage (Allegro *allegro, Boss_1 *boss_1, Boss_2 *boss_2, Boss_3 *boss_3);
void EnterInStage (Allegro *allegro, Rockman *rockman, Monster *monster);
void DrawCopymanInStage (Boss_1 *boss_1, Allegro *allegro);
void DrawNecromancerInStage (Boss_2 *boss_2, Allegro *allegro);
void DrawXaiYaInStage (Boss_3 *boss_3, Allegro *allegro);
void DrawClearStage (Allegro *allegro);


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
void PassSmallStage (Rockman *rockman, Allegro *allegro, Boss_1 *boss_1, Boss_2 *boss_2, Boss_3 *boss_3);
void StageSmall (Rockman *rockman, Allegro *allegro, Boss_1 *boss_1, Boss_2 *boss_2, Boss_3 *boss_3, Monster *monster);


/** Loading */
void DrawLoading (Allegro *allegro);
void DrawProgressBar (Allegro *allegro);
void LoadingFinish (Allegro *allegro, Rockman *rockman);



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


/** Necromancer / Boss 2 */
Boss_2 *CallocBoss_2();
void InitBoss_2 (Boss_2 *boss_2);
void DrawBoss_2 (Boss_2 *boss_2, Allegro *allegro, Rockman *rockman);
void MoveBoss_2 (Boss_2 *boss_2, Rockman *rockman);
void StateBoss_2 (Boss_2 *boss_2, Allegro *allegro, Rockman *rockman);
void BulletCollideBoss_2 (Rockman *rockman, Boss_2 *boss_2);
void DrawBoss_2HP (Boss_2 *boss_2);
void CheckBoss_2Alive (Boss_2 *boss_2, Allegro *allegro);
void InitRockmanInBoss_2 (Rockman *rockman);
void CheckAOEBoss_2 (Boss_2 *boss_2, Rockman *rockman);
void RockmanCollideBoss_2 (Rockman *rockman, Boss_2 *boss_2);
void StageBoss_2 (Boss_2 *boss_2, Rockman *rockman, Allegro *allegro);


/** XaiYa / Boss 3 */
Boss_3 *CallocBoss_3();
void InitBoss_3 (Boss_3 *boss_3);
void DrawBoss_3 (Boss_3 *boss_3, Allegro *allegro);
void MoveNormalYA (Boss_3 *boss_3);
void DrawExplosion (Boss_3 *boss_3);
void DrawBoss_3HP (Boss_3 *boss_3);

void ComputeBulletDirection (Boss_3 *boss_3, Rockman *rockman);
void CheckBoss_3Bullet (Boss_3 *boss_3, Rockman *rockman);
void DrawBoss_3Bullet (Boss_3 *boss_3);
void MoveBoss_3Bullet (Boss_3 *boss_3);
void CheckBoss_3BulletOver (Boss_3 *boss_3, Rockman *rockman);
void RockmanCollideBoss_3 (Rockman *rockman, Boss_3 *boss_3);

void BulletCollideBoss_3 (Rockman *rockman, Boss_3 *boss_3, Allegro *allegro);
void MoveCrazyYA (Boss_3 *boss_3, Rockman *rockman);
void CreateExplosion (Boss_3 *boss_3);
void InitRockmanInBoss_3 (Rockman *rockman);
void StageBoss_3 (Boss_3 *boss_3, Rockman *rockman, Allegro *allegro);

/** story */
void DrawStory (Allegro *allegro, Rockman *rockman);
void DrawNotPass (Allegro *allegro);
void DrawPass (Allegro *allegro);
void AnimePassStory (Allegro *allegro);
void DrawJohnWu (Allegro *allegro);
void DrawRockmanInStory (Rockman *rockman, Allegro *allegro);

/** rule */
void DrawRule (Allegro *allegro, Rockman *rockman);
void DrawKeyboardIcon (Allegro *allegro);
void InitRockmanInRule (Rockman *rockman);



/** music */
void voice_init(ALLEGRO_SAMPLE_INSTANCE *instance, ALLEGRO_MIXER **mixer, ALLEGRO_VOICE **voice);



/** socre board */
char **InitPlayerName (int number);
void ReadScoreCSV (Allegro *allegro);
void DrawScoreBoard (Allegro *allegro);
void FillOutScoreBoard (Allegro *allegro);
void CheckKeyboardDown(Allegro *allegro);
void DrawTypeName (Allegro *allegro);

