#include "stdio.h"
#include "stdlib.h"
#include "board.h"

void change_status(cell_t** p_board, long x, long y)
{
	p_board[x][y].status = p_board[x][y].new_status;
  p_board[x][y].change = 0;
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
          c[i][j].status = Dead;
        }
    }
    return c;
}

void check_neighbourhood(cell** p_board, cell p_cell)
{
  unsigned long x
}