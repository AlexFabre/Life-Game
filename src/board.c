#include "stdio.h"
#include "stdlib.h"
#include "board.h"

/********************************************************************
Functions
********************************************************************/
void change_status(cell_t* p_cell)
{
        if (p_cell->status) /* Any other value than 0 means Dead*/
        {
                p_cell->status = Alive; /* 0 */
        }
        else
        {
                p_cell->status = Dead; /* 255 */
        }
}

cell_t** init_Board(long p_nb_cell)
{
    printf("%ld\n", p_nb_cell);
        cell_t** c;
        long i;
        if (( c = malloc( p_nb_cell*sizeof( cell_t* ))) == NULL )
        { printf("Error in malloc 1 ! init_Board()\n"); }

        for ( i = 0; i < p_nb_cell; i++ )
        {
            if (( c[i] = malloc( p_nb_cell*sizeof( cell_t ) )) == NULL )
            { printf("Error in malloc  2! init_Board()\n"); }
                long j;
                for (j = 0; j < p_nb_cell; j++)
                {
                    c[i][j].status = Dead;
                }
        }
        return c;
}

void inform_neighbour(cell_t** p_board, unsigned long p_nb_cell, unsigned long x, unsigned long y)
{
    unsigned long start_x, start_y, stop_x, stop_y, i, j;
    char cell_state = 1; /*< Will increment or decrement the number of living cell around each neighbour cell*/

    p_nb_cell--;

    if (p_board[x][y].status) /* If the current cell is dying*/
    {
        cell_state = -1; /* We decrement*/
    }

    if (x)
    {
        start_x = x-1;
        if (x < p_nb_cell) { stop_x = x+1; }
        else { stop_x = x; }
    }
    else {
        start_x = x;
        stop_x = x+1;
    }

    if (y)
    {
        start_y = y-1;
        if (y < p_nb_cell) { stop_y = y+1; }
        else { stop_y = y; }
    }
    else {
        start_y = y;
        stop_y = x+1;
    }

    for (i = start_x; i <= stop_x; ++i)
    {
        for (j = start_y; j <= stop_y; ++j)
        {
            if (i!=x || j!=y)
            {
                p_board[i][j].living_neighbour += cell_state;
            }
        }
    }
}