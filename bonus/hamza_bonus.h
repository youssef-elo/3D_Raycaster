#ifndef HAMZA_BONUS_H
#define HAMZA_BONUS_H
#include "youssef_bonus.h"
#include <fcntl.h>

#define TILE_SIZE 40


#define MINI_MAP_PLAYER_COLOR rgb(0, 255, 0, 255)
#define MINI_MAP_WALL_COLOR rgb(0, 0, 0, 255)
#define MINI_MAP_EMPTY_COLOR rgb(0, 0, 255, 255)
#define MINI_MAP_OUT_OF_BOUND_COLOR rgb(0,180,255,255)
#define MINI_MAP_PLAYER_RADIUS 5

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

typedef struct mini_map_s
{
    mlx_image_t *mini_map_img;
    mlx_image_t *player;
    mlx_texture_t *texture;
    int            player_x;
    int            player_y;

} mini_map_h;


int    ft_count_words( char *s1, int c);
void parsing(int argc, char **argv, map_context_h *parsing_data);
char    **ft_split(char  *s, char c);





#endif