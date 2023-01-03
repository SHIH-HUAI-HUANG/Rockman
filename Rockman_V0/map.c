#include "resource.h"


void InitMap (Allegro *allegro)
{
    allegro->map.x = -40;
    allegro->map.y = 0;
    allegro->map.pre_x = -999; // any impossile number
    allegro->map.speed = SPEED;
    allegro->map.img = al_load_bitmap ("./picture/map.png");
}

void Gravity (Allegro *allegro, Rockman *rockman)
{
    int onLand = 0;
    if ( (rockman->y) < (725 - ROCKMAN_H - 5) )// avoid to check out of the matrix_map, and keeping fall.
    {
        for (int i = 0; i < 90; i++)// the 90 is rockman's delta x.
        {
            if (allegro->matrix_map[rockman->y + 106][rockman->x + abs(allegro->map.x) + i] == 0)
                onLand++;
        }
        if(onLand == 90)
            rockman->y = rockman->y + 1;

        else if (allegro->matrix_map[rockman->y + 106][rockman->x + abs(allegro->map.x)] == 1)
            rockman->jump_time = 0; // test for jump
        else if ( (allegro->matrix_map[rockman->y + 106][rockman->x + abs(allegro->map.x)] != 0) && (allegro->matrix_map[rockman->y + 106][rockman->x + abs(allegro->map.x)] != 1) )
            rockman->y = rockman->y + 1;
    }
}



void ReadMapData (Allegro *allegro)
{
    FILE *csv;
    csv = fopen("./data/map.csv", "r");

    if (!csv)
    {
        fprintf(stderr, "failed to open file for reading\n");
        return 1;
    }

    char line[15000];
    char *result = NULL;
    int row = 0;
    int col = 0;

    while(fgets(line, 15000, csv) != NULL)
    {
        col = 0;
        result = strtok(line, ",");
        while (result != NULL)
        {
            allegro->matrix_map[row][col] = atoi(result); //(y,x)
            result = strtok(NULL, ",");
            col++;
        }
        row++;
    }

    fclose (csv);
}


void MoveMap(Allegro *allegro, Rockman *rockman)
{
    al_get_keyboard_state(&allegro->keyboardState);

    if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_RIGHT))
    {
        if ( 360 < rockman->x && rockman->x < 400 )
        {
            allegro->map.pre_x = allegro->map.x;
            if ((allegro->matrix_map[rockman->y + ROCKMAN_H - 10][rockman->x + abs(allegro->map.x) + ROCKMAN_W + 5] == 0)) // limit of obstacle
                allegro->map.x = allegro->map.x - allegro->map.speed;
            if (allegro->map.x < -6200)
                allegro->map.x = -6200;
        }
    }

    if (al_key_down(&allegro->keyboardState, ALLEGRO_KEY_LEFT))
    {
        if ( 360 < rockman->x && rockman->x < 400)
        {
            allegro->map.pre_x = allegro->map.x;
            if (allegro->matrix_map[rockman->y + ROCKMAN_H][rockman->x + abs(allegro->map.x) - 5] == 0)
                allegro->map.x = allegro->map.x + allegro->map.speed;
            if (allegro->map.x > -40)
                allegro->map.x = -40;
        }
    }
}


