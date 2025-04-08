#ifndef HAMZA_H
#define HAMZA_H
#include "youssef.h"
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

typedef struct var_size_s
{
    int x;
    int i;
	int y;
	int max;
	char *array;
}var_size_h;



int    ft_count_words( char *s1, int c);
void parsing(int argc, char **argv, map_context_h *parsing_data);
char    **ft_split(char  *s, char c);
char *ft_strdup_n(char *str, int a, map_context_h *map);
char	*ft_strjoin_n(char *s1, char *s2, map_context_h *map);
int	ft_cmpr(char *s, char *s1);
int	ft_strcmp(char **s, char *s1);
long	ft_atoi(const char *str);
void ft_free_map(map_context_h *map);
void ft_display_error(char *s, map_context_h *map);
void	ft_look_cub(char *s, map_context_h *map);
int size_of_line(char **str);
void ft_set_map(map_context_h *map);
char *ft_get_string(int num);
void	ft_adjust_map_size(map_context_h *map);
void  ft_read_file(char *line, map_context_h *map);
void ft_read_map(map_context_h *map, char *line);
void ft_fill_struct(map_context_h *map, char **str, int s);
void	ft_check_line(char *line, map_context_h *map);
int ft_check_space(char *str);
void ft_check_for_error(char *str, map_context_h *map);
void ft_fill_color_array(map_context_h *map,char **array,int i);
void ft_convert_color(map_context_h *map, char *str, int i);
void ft_check_first_last_line(map_context_h *map);
void ft_check_player(map_context_h *map);
void ft_valid_path(map_context_h *map);
void ft_double_array(map_context_h *map);

#endif