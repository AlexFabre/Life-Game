/********************************************************************
Structure
********************************************************************/
typedef struct ant_s 
{
    char*       name;
    long        step;
    char        direction[2];
    long        x_axis;
    long        y_axis;
} ant_t;

/********************************************************************
Function
********************************************************************/
ant_t   new_ant(char* p_name, long p_startx, long p_starty) ;
void  turn_left(ant_t* a);
void  turn_right(ant_t* a);
void  move(ant_t* a);
