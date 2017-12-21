#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "life_game.h"

#define     MAX_SIZE_TEMPLATE   50 /*< Maximum size of a template in number of cell*/
#define     X                   0
#define     Y                   1
#define     DEFAULT_GRID_SIZE   50
#define     DEFAULT_STEP        60

/********************************************************************
Function
********************************************************************/
void evolution(unsigned long p_nb_cell, cell_t** p_board);
void prepare_evolution(unsigned long p_nb_cell, cell_t** p_board);
void print_picture(unsigned long p_step, unsigned long p_nb_cell, cell_t** p_board);
void add_template(cell_t** p_board, unsigned long p_nb_cell, template_t template, unsigned long p_pos_x, unsigned long p_pos_y);

/********************************************************************
Function
********************************************************************/
void prepare_evolution(unsigned long p_nb_cell, cell_t** p_board)
{
    unsigned long i,j;

    for (i = 0; i < p_nb_cell; ++i)
    {
        for (j = 0; j < p_nb_cell; ++j)
        {

            if (p_board[i][j].status == Alive)
            {

                /* This cell is Alive */
                switch(p_board[i][j].living_neighbour)
                {
                    case 2:
                    case 3:
                        /* Nothing happens for this cell*/
                        break;
                    default:
                        p_board[i][j].changing = 1;
                        break;
                }
            }
            else /* Dead cells */
            {
                if(p_board[i][j].living_neighbour == 3)
                {
                    p_board[i][j].changing = 1;
                }
            }
        }
    }
}

void evolution(unsigned long p_nb_cell, cell_t** p_board)
{
    unsigned long i,j;

    for (i = 0; i < p_nb_cell; ++i)
    {
        for (j = 0; j < p_nb_cell; ++j)
        {
            if (p_board[i][j].changing)
            {
                change_status(&p_board[i][j]);
                p_board[i][j].changing = 0;
                inform_neighbour(p_board, p_nb_cell, i ,j);
            }
        }
    }
}

void add_template(cell_t** p_board, unsigned long p_nb_cell, template_t template, unsigned long p_pos_x, unsigned long p_pos_y)
{
    unsigned long   tab_xy[2][MAX_SIZE_TEMPLATE];
    unsigned int    size=0, i;

    switch(template)
    {
        case FIGURE_1:
            tab_xy[X][size] = 0; tab_xy[Y][size++] = 0;
            tab_xy[X][size] = 1; tab_xy[Y][size++] = 0;
            tab_xy[X][size] = 1; tab_xy[Y][size++] = 1;
            tab_xy[X][size] = 0; tab_xy[Y][size++] = 1;

            tab_xy[X][size] = 3; tab_xy[Y][size++] = 1;
            tab_xy[X][size] = 4; tab_xy[Y][size++] = 0;
            tab_xy[X][size] = 4; tab_xy[Y][size++] = 2;
            tab_xy[X][size] = 5; tab_xy[Y][size++] = 0;
            tab_xy[X][size] = 5; tab_xy[Y][size++] = 2;
            tab_xy[X][size] = 6; tab_xy[Y][size++] = 1;

            tab_xy[X][size] = 9; tab_xy[Y][size++] = 1;
            tab_xy[X][size] = 9; tab_xy[Y][size++] = -1;
            tab_xy[X][size] = 9; tab_xy[Y][size++] = -2;
            tab_xy[X][size] = 9; tab_xy[Y][size++] = 3;
            tab_xy[X][size] = 9; tab_xy[Y][size++] = 4;
            tab_xy[X][size] = 10; tab_xy[Y][size++] = -2;
            tab_xy[X][size] = 10; tab_xy[Y][size++] = 4;
            tab_xy[X][size] = 11; tab_xy[Y][size++] = -1;
            tab_xy[X][size] = 11; tab_xy[Y][size++] = 3;
            tab_xy[X][size] = 12; tab_xy[Y][size++] = 0;
            tab_xy[X][size] = 12; tab_xy[Y][size++] = 1;
            tab_xy[X][size] = 12; tab_xy[Y][size++] = 2;

            tab_xy[X][size] = 26; tab_xy[Y][size++] = 3;
            tab_xy[X][size] = 26; tab_xy[Y][size++] = 4;
            tab_xy[X][size] = 26; tab_xy[Y][size++] = 5;
            tab_xy[X][size] = 26; tab_xy[Y][size++] = 2;
            tab_xy[X][size] = 26; tab_xy[Y][size++] = 1;
            tab_xy[X][size] = 27; tab_xy[Y][size++] = 3;
            tab_xy[X][size] = 27; tab_xy[Y][size++] = 4;
            tab_xy[X][size] = 27; tab_xy[Y][size++] = 2;
            tab_xy[X][size] = 27; tab_xy[Y][size++] = 6;
            tab_xy[X][size] = 27; tab_xy[Y][size++] = 0;
            tab_xy[X][size] = 28; tab_xy[Y][size++] = 5;
            tab_xy[X][size] = 28; tab_xy[Y][size++] = 1;
            tab_xy[X][size] = 29; tab_xy[Y][size++] = 3;
            tab_xy[X][size] = 29; tab_xy[Y][size++] = 4;
            tab_xy[X][size] = 29; tab_xy[Y][size++] = 2;
            tab_xy[X][size] = 30; tab_xy[Y][size++] = 3;

            tab_xy[X][size] = 34; tab_xy[Y][size++] = 2;
            tab_xy[X][size] = 34; tab_xy[Y][size++] = 3;
            tab_xy[X][size] = 35; tab_xy[Y][size++] = 2;
            tab_xy[X][size] = 35; tab_xy[Y][size++] = 3;
            break;
        default:
            break;
    }
    for (i = 0; i < size; ++i)
    {
        p_board[ p_pos_x + tab_xy[X][i] ][ p_pos_y + tab_xy[Y][i] ].status = Alive;
        inform_neighbour(p_board, p_nb_cell, p_pos_x + tab_xy[X][i], p_pos_y + tab_xy[Y][i]);
    }
}
/********************************************************************
Code
********************************************************************/
int main(int argc, char const *argv[])
{
    

    /* code */
    unsigned long nb_cell; /**< Unsigned long integer. Size of the grid: nb_cell*nb_cell */
    unsigned long nb_step; /**< Unsigned long integer. Number of step to compute. */
    unsigned long i;

    if(argc>1){
        /* The size of the grid is specified */
        nb_cell = atoi(argv[1]);
        if (nb_cell < DEFAULT_GRID_SIZE){
            nb_cell = DEFAULT_GRID_SIZE;
        }
        if (argc > 2) {
            /* The number of step is specified */
            nb_step = atoi(argv[2]);
            if (nb_step < DEFAULT_STEP) {
                nb_step = DEFAULT_STEP;
            }
        }
    }

    /* Init the game with grid size and Alive cells positions */
    cell_t** board = init_Board(nb_cell);

    add_template(board, nb_cell, FIGURE_1, 1, 40);

    while(i<nb_step) 
    {
        print_picture(i, nb_cell, board);
        prepare_evolution(nb_cell, board); /* Review all the cells that will have to change */
        evolution(nb_cell, board); /* Makes all the cells changes */
        i++;
    }

    print_picture(i, nb_cell, board);

    return 0;
}

void print_picture(unsigned long p_step, unsigned long p_nb_cell, cell_t** p_board)
{
    char filename[10];
    sprintf(filename, "%ld", p_step);
    char comment[32] = "# Life game at step \0";
    strcat(comment, filename);
    char *name = ".pgm";
    strcat(filename, name);

    
    unsigned char data[p_nb_cell][p_nb_cell]; /* 2D array for statuss (shades of gray) */
    const int MaxstatusComponentValue = 255; /* status component is coded from 0 to 255 ;  it is 8 bit status file */
    FILE * fp;

    long x,y;
    for (x = 0; x < p_nb_cell; ++x) {
        for (y = 0; y < p_nb_cell; ++y) {
            data[x][y] = p_board[y][p_nb_cell-x-1].status;
        }
    }

    fp = fopen(filename, "wb");
    fprintf(fp, "P5\n %s\n %ld\n %ld\n %d\n", comment, p_nb_cell, p_nb_cell, MaxstatusComponentValue); /* write header to the file */
    fwrite(data, sizeof(data), 1, fp); /* write image data bytes to the file */
    fclose(fp);
}
