/********************************************************************
Enumeration
********************************************************************/
typedef enum state_s
{
    Dead = 255, /* Correspond to a white cell */
    Alive = 0 /* Correspond to a black cell */
} state_t;

/********************************************************************
Structure
********************************************************************/
typedef struct cell_s
{
    unsigned long           x_axis;
    unsigned long           y_axis;
    char                    changing;
    char                    living_neighbour; /*< Number of living neighbours around that cell. Min 0 max 8 */
    state_t                 status;
} cell_t;

typedef struct cell_tab_s
{
    cell_t*           list;
    unsigned long   size;
} cell_tab_t;

/********************************************************************
Function
********************************************************************/
cell_t** init_Board(long p_nb_cell);
void change_status(cell_t* p_cell);
void inform_neighbour(cell_t** p_board, unsigned long p_nb_cell, unsigned long x, unsigned long y);
