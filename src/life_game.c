#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "life_game.h"

/********************************************************************
Function
********************************************************************/
void evolution(unsigned long p_nb_cell, cell_t** p_board);
void prepare_evolution(unsigned long p_nb_cell, cell_t** p_board);
void print_picture(unsigned long p_step, unsigned long p_nb_cell, cell_t** p_board);
void add_template(cell_t** p_board, template_t template, unsigned long pos_x, unsigned long pos_y);

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

void add_template(cell_t** p_board, template_t template, unsigned long pos_x, unsigned long pos_y)
{
    switch(template)
    {
        case FIGURE_1:
            unsigned long tab_x[4];
            unsigned long tab_y[4];
            p_board[pos_x+1][pos_y+2].status = Alive;
            p_board[pos_x+2][pos_y+2].status = Alive;
            p_board[pos_x+3][pos_y+2].status = Alive;
            p_board[pos_x+3][pos_y+1].status = Alive;
            inform_neighbour(p_board, nb_cell, pos_x+1, pos_y+2);
            inform_neighbour(p_board, nb_cell, pos_x+2, pos_y+2);
            inform_neighbour(p_board, nb_cell, pos_x+3, pos_y+2);
            inform_neighbour(p_board, nb_cell, pos_x+3, pos_y+1);
            break;
        default:
            break;
    }
}
/********************************************************************
Code
********************************************************************/
int main(int argc, char const *argv[])
{
    /* code */
    unsigned long nb_cell = 5;
    unsigned long nb_step = 2;
    unsigned long i = 0;

    /* Init the game with grid size and Alive cells positions */
    cell_t** board = init_Board(nb_cell);
    add_template(board, FIGURE_1, 1, 2);
    // board[1][2].status = Alive;
    // board[2][2].status = Alive;
    // board[3][2].status = Alive;
    // board[3][1].status = Alive;
    // inform_neighbour(board, nb_cell, 1, 2);
    // inform_neighbour(board, nb_cell, 2, 2);
    // inform_neighbour(board, nb_cell, 3, 2);
    // inform_neighbour(board, nb_cell, 3, 1);

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
