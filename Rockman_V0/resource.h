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
#define NUM_BULLET 20


typedef struct Bullet
{
    int x;
    int y;
    bool activity;

} Bullet;


typedef struct Rockman
{
    int x;
    int y;
    int speed;
    int state;
    int jump_time;

    bool direction;
    ALLEGRO_BITMAP *img;
    // struct Laser **laser;

} Rockman;

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
void EventCheck(Allegro *allegro, Rockman *rockman);


/** rockman */
Rockman *CallocRockman();
void InitRockman (Rockman *rockman);
void DrawRockman (Rockman *rockman, Allegro *allegro);
void MoveRockmanInBoss(Rockman *rockman, Allegro *allegro);



