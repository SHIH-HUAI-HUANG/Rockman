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
#define WINDOWS_H 720
#define FPS 60
#define SPEED 4
#define NUM_BULLET 30
#define JUMP_TIME 60



typedef struct Bullet
{
    int x;
    int y;
    bool activity;
    bool direction;

} Bullet;


typedef struct Rockman
{
    int x;
    int y;
    int speed;
    int state;
    int jump_time;
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
    Bullet bullet[NUM_BULLET];

} Boss_1;

typedef struct Allegro
{
    ALLEGRO_EVENT events;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_KEYBOARD_STATE keyboardState;
    ALLEGRO_TIMER *timer;

    ALLEGRO_DISPLAY *display;
    bool finish;
    int FRAME;
    int STATE;

} Allegro;



typedef enum
{
    STAND,
    RUN_RIGHT,
    RUN_LEFT,
    JUMP

} State_rockman;

typedef enum
{
    MENU,
    RULE,
    GAME,
    BOSS_1

} State_game;


/** allegro */
Allegro *CallocAllegro();
void AllegroDriverInit(Allegro *allegro);
void EventCheck(Allegro *allegro, Rockman *rockman, Boss_1 *boss_1);


/** rockman */
Rockman *CallocRockman();
void InitRockman (Rockman *rockman);
void DrawRockman (Rockman *rockman, Allegro *allegro);
void MoveRockmanInBoss(Rockman *rockman, Allegro *allegro);


void CreateBullet (Rockman *rockman);
void DrawBullet (Rockman *rockman);
void MoveBullet (Rockman *rockman);
void CheckBulletOver (Rockman *rockman);


/** CopyMan */
Boss_1 *CallocBoss_1();
void InitBoss_1 (Boss_1 *boss_1);
void DrawBoss_1 (Boss_1 *boss_1, Allegro *allegro);
void MoveBoss_1 (Boss_1 *boss_1);
