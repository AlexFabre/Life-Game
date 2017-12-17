/********************************************************************
Enumeration
********************************************************************/
typedef enum color_e
{
    White = 255,
    Black = 0,
    Grey = 125
} color_t;

/********************************************************************
Structure
********************************************************************/
typedef struct cell_s
{
    unsigned long       x_axis;
    unsigned long       y_axis;
    char change         False;
    color_t             color;
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
void change_color(cell_t** p_board, unsigned long x, unsigned long y, color_t color);
void check_neighbourhood(cell** p_board, cell p_cell);
