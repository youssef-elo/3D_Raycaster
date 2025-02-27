#ifndef HAMZA_H
#define HAMZA_H
#include "youssef.h"
#include "get_next_line/get_next_line.h"
#include <fcntl.h>

int	ft_count_words(const char *s1, int c);
void parsing(int argc, char **argv);
char	**ft_split(char const *s, char c);

typedef struct map_context_s
{
    char **map;
    char *nort;
    char *south;
    char *west;
    char *east;

    char *flor_s;
    char *sky_s;

    int sky[3];
    int flor[3];

} map_context_h;



#endif