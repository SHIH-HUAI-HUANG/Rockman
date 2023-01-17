#include "resource.h"


char **InitPlayerName (int number)
{
    char **name = (char **) malloc(number * sizeof(char *));
    for (int i = 0; i < number; i++)
    {
        name[i] = (char) malloc(sizeof(char));
    }
}



void ReadScoreCSV (Allegro *allegro)
{
    FILE *csv;
    csv = fopen("./data/scoreboard.csv", "r");

    if (!csv)
    {
        fprintf(stderr, "failed to open file for reading\n");
    }

    char line[50];
    char *result = NULL;
    int i = 0;

    while(fgets(line, 50, csv) != NULL)
    {
        result = strtok(line, ",");
        while( result != NULL )
        {
            sscanf(result, "%s", allegro->player[i].name);
            result = strtok(NULL, ",");
        }
        i++;
    }
    allegro->number_scoreboard = i;
    fclose (csv);
}


void DrawTypeName (Allegro *allegro)
{
    al_clear_to_color (al_map_rgb(0, 0, 0));
    DrawStar (NUM_STAR, allegro);
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 50, 1, "TYPE YOUR NAME");

    for (int j = 0; j < allegro->name_length; j++)
    {
        al_draw_textf(allegro->font_96, al_map_rgb(255, 255, 255), 250 + j*20, 300, 1, "%c", allegro->name[j]);
    }
    al_draw_filled_rectangle (200, 348, 568, 352, al_map_rgb(255, 255, 255));
}


void DrawScoreBoard (Allegro *allegro)
{
    /** check can typing name or not */
    if (allegro->pass_stage1 && allegro->pass_stage2 && allegro->pass_stage3 && (allegro->can_type_name==0) )
        allegro->can_type_name = 1;

    al_clear_to_color (al_map_rgb(0, 0, 0));
    DrawStar (NUM_STAR, allegro);
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 384, 50, 1, "SCOREBOARD");
    al_draw_textf(allegro->font_24, al_map_rgb(255, 255, 255), 650, 50, 0, "Back");
    al_draw_bitmap (allegro->yangjyun, 365, 150, 0);
    al_draw_bitmap (allegro->jyunwei, 570, 150, 0);
    al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 365, 400, 0, "The authors wish to give special thanks to");
    al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 365, 430, 0, "Dr.YANG-JYUN and Dr.JYUN-WEI. They are very");
    al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 365, 460, 0, "professional technical adviser in this WAR.");
    al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 365, 490, 0, "The Author on behalf of all members, thanks");
    al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 365, 520, 0, "for your contribution. Therefore, we made this");
    al_draw_textf(allegro->font_12, al_map_rgb(255, 255, 255), 365, 550, 0, "SCOREBOARD to commemorate this history.");

    for (int i = 0; i < allegro->number_scoreboard; i++)
    {
        al_draw_textf(allegro->font_36, al_map_rgb(255, 255, 255), 120, 150 + i * 50, 0, "%s", allegro->player[i].name);
    }
    if (allegro->can_type_name == 1)
    {
        al_draw_textf(allegro->font_24, al_map_rgb(255, 215, 100), 550, 610, 1, "ENGRAVED YOUR NAME");
        al_draw_textf(allegro->font_12, al_map_rgb(255, 215, 100), 550, 660, 1, "PRESS ENTER");
    }
    else
    {
        al_draw_textf(allegro->font_24, al_map_rgb(100, 100, 100), 550, 610, 1, "ENGRAVED YOUR NAME");
        al_draw_textf(allegro->font_12, al_map_rgb(100, 100, 100), 550, 660, 1, "PRESS ENTER");
    }

}


void FillOutScoreBoard (Allegro *allegro)
{
    if (allegro->number_scoreboard > 9) allegro->number_scoreboard = 9; /** ensure scoreboard only ten player */

    FILE *csv;
    if( (csv = fopen("./data/scoreboard.csv", "w+")) == NULL )
    {
        puts("Fail to open file!");
        //exit(0);
    }
    fprintf(csv, "%s\n", allegro->name);
    for (int i = 0; i < allegro->number_scoreboard; i++)
    {
        fprintf(csv, "%s\n", allegro->player[i].name);
    }

    fclose (csv);
}



// Function : type the player's name
void CheckKeyboardDown(Allegro *allegro)
{
    if (allegro->STATE == TYPE)
    {
        switch( allegro->events.keyboard.keycode )
        {
        case ALLEGRO_KEY_ENTER:
            allegro->STATE = SCOREBOARD;
            FillOutScoreBoard (allegro);
            ReadScoreCSV (allegro);
            break;
        case ALLEGRO_KEY_BACKSPACE:
            if(allegro->name_length == 0) break;
            allegro->name_length -= 1;
            allegro->name[allegro->name_length] = 0;
            break;
        case ALLEGRO_KEY_A:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'A';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_B:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'B';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_C:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'C';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_D:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'D';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_E:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'E';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_F:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'F';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_G:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'G';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_H:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'H';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_I:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'I';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_J:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'J';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_K:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'K';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_L:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'L';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_M:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'M';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_N:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'N';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_O:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'O';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_P:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'P';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_Q:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'Q';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_R:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'R';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_S:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'S';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_T:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'T';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_U:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'U';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_V:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'V';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_W:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'W';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_X:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'X';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_Y:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'Y';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_Z:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = 'Z';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_0:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '0';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_1:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '1';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_2:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '2';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_3:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '3';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_4:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '4';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_5:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '5';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_6:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '6';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_7:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '7';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_8:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '8';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_9:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '9';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_FULLSTOP:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '.';
            allegro->name_length += 1;
            break;
        case ALLEGRO_KEY_MINUS:
            if(allegro->name_length >= 15) break;
            allegro->name[allegro->name_length] = '-';
            allegro->name_length += 1;
            break;
        }
    }
}
