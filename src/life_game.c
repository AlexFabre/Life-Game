#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "langton_ant.h"
#include "board.h"

#define     DEFAULT_GRID_SIZE   20
#define     DEFAULT_STEP        1

void print_picture(ant_t* p_ant, long nb_cell, cell_t** p_board);
void  look(ant_t* a, cell_t** p_board);

/********************************************************************
Function
********************************************************************/
ant_t new_ant(char* p_name, long p_startx, long p_starty) 
{
    ant_t a;
    a.name = p_name;
    a.step = 0;
    a.direction[0] = 0;
    a.direction[1] = 1;
    a.x_axis = p_startx;
    a.y_axis = p_starty;
    return a;
}

void turn_left(ant_t* p_ant)
{
    char tab_tmp[2];

    tab_tmp[0] = p_ant->direction[0];
    tab_tmp[1] = p_ant->direction[1];

    p_ant->direction[0] = -tab_tmp[1];
    p_ant->direction[1] = tab_tmp[0];
}

void turn_right(ant_t* p_ant)
{
    char tab_tmp[2];
    
    tab_tmp[0] = p_ant->direction[0];
    tab_tmp[1] = p_ant->direction[1];

    p_ant->direction[0] = tab_tmp[1];
    p_ant->direction[1] = -tab_tmp[0];
}

void move(ant_t* p_ant)
{
    p_ant->x_axis+=p_ant->direction[0];
    p_ant->y_axis+=p_ant->direction[1];
    p_ant->step++;
}

void look(ant_t* p_ant, cell_t** p_board)
{
    if (p_board[p_ant->x_axis][p_ant->y_axis].color == Black)
    {
        turn_left(p_ant);
        change_color(p_board, p_ant->x_axis, p_ant->y_axis, White);
    }
    else {
        turn_right(p_ant);
        change_color(p_board, p_ant->x_axis, p_ant->y_axis, Black);
    }
}

/********************************************************************
Code
********************************************************************/
void print_picture(ant_t* p_ant, long nb_cell, cell_t** p_board)
{
    char filename[10];
  	sprintf(filename, "%ld", p_ant->step);
    char comment[32] = "# Langton's Ant at step \0";
    strcat(comment, filename);
    char *name = ".pgm";
    strcat(filename, name);

    
    unsigned char data[nb_cell][nb_cell]; /* 2D array for colors (shades of gray) */
    const int MaxColorComponentValue = 255; /* color component is coded from 0 to 255 ;  it is 8 bit color file */
    FILE * fp;

    long x,y;
    for (x = 0; x < nb_cell; ++x) {
        for (y = 0; y < nb_cell; ++y) {
            data[x][y] = p_board[y][nb_cell-x-1].color;
        }
    }
    /* Printing ant's position in grey*/
    data[nb_cell-(p_ant->y_axis)-1][p_ant->x_axis] = 125;

    fp = fopen(filename, "wb");
    fprintf(fp, "P5\n %s\n %ld\n %ld\n %d\n", comment, nb_cell, nb_cell, MaxColorComponentValue); /* write header to the file */
    fwrite(data, sizeof(data), 1, fp); /* write image data bytes to the file */
    fclose(fp);
}

int main(int argc, char const *argv[])
{
	int exit_code = 0;
    unsigned long nb_cell; /**< Unsigned long integer. Size of the grid: nb_cell*nb_cell */
    unsigned long nb_step; /**< Unsigned long integer. Number of step to compute. */

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

    cell_t** board = init_Board(nb_cell);
    
    ant_t maguie = new_ant("Maguie", nb_cell/2, nb_cell/2); /**< New ant. Start position x: nb_cell/2 y: nb_cell/2*/
    
    printf("Go for %ld step\n", nb_step);
    unsigned long i = 0; /**< unsigned long integer. Loop time counter */
    
    if (!i) /* Check first move */
    {
        change_color(board, maguie.x_axis, maguie.y_axis, Black); /* Invert the cell under the ant before her first move */
    }
    while(i < nb_step)  
    {
    	if ((maguie.x_axis && maguie.x_axis < nb_cell) && (maguie.y_axis && maguie.y_axis < nb_cell))
        {
        	print_picture( &maguie, nb_cell, board);
        	move( &maguie);
        	look( &maguie, board);
        	i++;
        }
        else
        {
        	printf("Warning! Simulation stopped at step %ld. Reached grid limit %ldx%ld\n", i, nb_cell, nb_cell);
        	exit_code = 1;
        	break;
        }
    }

    print_picture(&maguie, nb_cell, board);
    printf("Done\n");

    return exit_code;
}
