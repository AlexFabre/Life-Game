#include <stdio.h>
#include <stdlib.h>
#include "life_game.h"
#include "board.h"

void evolution(cell** p_board, cell_tab_t p_changing_cell);
void review_changes(unsigned long p_nb_cell, cell** p_board, cell_tab_t p_changing_cell);
void print_picture(unsigned long p_step, unsigned long p_nb_cell, cell_t** p_board);

cell* review_changes(unsigned long p_nb_cell, cell** p_board, cell_tab_t p_changing_cell)
{
    unsigned long i,j;
    char change;
    cell_tab_t change_tab;

    for (i = 0; i < p_nb_cell; ++i)
    {
        for (j = 0; j < p_nb_cell; ++j)
        {
            if (p_board[i][j].status == Alive)
            {
                /* We only look at the living cell's neighbours */
                change = check_neighbourhood(p_board, p_board[i][j]);
                if (change)
                {
                    add(change_tab.list, p_board[i][j]);
                    change_tab.size++;
                }
            }
        }
    }
}

void evolution(cell** p_board, cell_tab_t p_changing_cell)
{
    unsigned long i;
    for (i = 0; i < p_changing_cell.size; ++i)
    {
        x = p_changing_cell.list[i].x_axis;
        y = p_changing_cell.list[i].y_axis;
        p_board[x][y].status = p_board[x][y].new_status;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    unsigned long nb_cell = 20;
    unsigned long nb_step = 2;

    /* Init the game with grid size and Alive cells positions */
    cell** board = init_Board(nb_cell);
    add_template(board, template, pos_x, pos_y);

    cell_tab_t changing_cell;

    while(i) 
    {
        print_picture(i, nb_cell, board);
        review_changes(nb_cell, board, changing_cell); /* Review all the cells that will have to change */
        evolution(board, changing_cell); /* Makes all the cells changes */
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
