/********************************************************************
Enumeration
********************************************************************/
typedef enum state_s
{
    Dead = 255,
    Alive = 0
} state_t;

/********************************************************************
Structure
********************************************************************/
typedef struct cell_s
{
    unsigned long           x_axis;
    unsigned long           y_axis;
    char has_to_change      0;
    char living_neighbour   0; /*< Number of living neighbours around that cell. Min 0 max 8 */
    status_t                 status;
    status_t                 new_status;
} cell_t;

typedef struct cell_tab_s
{
    cell*           list;
    unsigned long   size;
} cell_tab_t;

/********************************************************************
Function
********************************************************************/
cell_t** init_Board(unsigned long p_nb_cell);
void change_status(cell_t** p_board, unsigned long x, unsigned long y, status_t status);
void check_neighbourhood(cell** p_board, cell p_cell);
