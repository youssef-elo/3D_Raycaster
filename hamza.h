#ifndef HAMZA_H
#define HAMZA_H
#include "youssef.h"
#include "get_next_line/get_next_line.h"
#include <fcntl.h>

typedef struct map_context_s
{
    char **map;
    char *north;
    char *south;
    char *west;
    char *east;
    char *array;

    char *floor_s;
    char *sky_s;

    int count;

    int sky[3];
    int floor[3];
    int read_map;

} map_context_h;

int	ft_count_words( char *s1, int c);
void parsing(int argc, char **argv, map_context_h *parsing_data);
char	**ft_split(char  *s, char c);




#endif