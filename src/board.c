#include "stdio.h"
#include "stdlib.h"
#include "board.h"

void change_color(cell_t** p_board, long x, long y, color_t p_color)
{
	p_board[x][y].color = p_color;
}

cell_t** init_Board(long p_nb_cell)
{
    /* p_nb_cell is the number of rows  */
    /* note: c is cell_t** */
    cell_t** c;
    long i;
    if (( c = malloc( p_nb_cell*sizeof( cell_t* ))) == NULL )
    { /* error */ }

    for ( i = 0; i < p_nb_cell; i++ )
    {
      /* p_nb_cell here is the size of given row, no need to
       * multiply by sizeof( cell_t ), it's always 1
       */
      if (( c[i] = malloc( p_nb_cell*sizeof( cell_t ) )) == NULL )
      { /* error */ }
        long j;
        for (j = 0; j < p_nb_cell; j++)
        {
          c[i][j].color=White;
        }
    }
    return c;
}