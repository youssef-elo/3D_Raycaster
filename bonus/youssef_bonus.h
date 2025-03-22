#ifndef YOUSSEF_H
 # define YOUSSEF_H

#include "../MLX/include/MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "hamza_bonus.h"
#include <strings.h>
#include <time.h>
#include <sys/time.h>

#define CUBE3D 1


#define PI 3.141592653589793
#define FOV 1.1519
#define NUMBER_OF_RAYS 2040
// #define CUBE3D 0
#define OUT_OF_RANGE 2147483647
#define SPEED 4

// 8 21
#define TILE 1280

#define WIDTH_3D 2040
#define HEIGHT_3D 1280

#define MAX_VIEW TILE * 10
#define FOG_START TILE * 3

#define MAX_VIEW_FLASH TILE * 20
#define FOG_START_FLASH TILE * 4

#define RIGHT 1
#define LEFT 0


#define WIDTH 29 * TILE
#define HEIGHT 8 * TILE
#define BPP sizeof(int32_t)


typedef struct offset_s
{
	double e_offset;
	double s_offset;
	double w_offset;
	double n_offset;

}	offset_t;


typedef struct constant_s
{
	int p;
	double scaler;
	double fov_half;
	double angle_i;
	int half_window;
} constant_t;

typedef struct mlx_data_s{
	mlx_t *mlx;
	mlx_image_t *view;
	mlx_image_t *view_3d; 
	mlx_image_t *floor_ceiling;
	mlx_image_t *empty;
	mlx_image_t *wall;
	mlx_image_t *rays_image;
	mlx_image_t *mini_map;
	mlx_image_t *north;
	mlx_image_t *south;
	mlx_image_t *east;
	mlx_image_t *west;
} mlx_data_t;

typedef struct raycaster_s{
	double hit_x;
	double hit_y;
	double direction_x;
	double direction_y;
	double scaling_factor;
	int map_y;
	int map_x;
	int step;
	int offset;
}	raycaster_t;

typedef struct data_s{
	double player_x;
	double player_y;
	int		map_x;
	int		map_y;
	double p_angle;
	int	 fog_start;
	int	 fog_max;
	double dir_x;
	double dir_y;
	int width;
	int height;
	char **map;
	float *cos;
	constant_t consts;
	offset_t offset;
	uint32_t ceiling;
	uint32_t floor;
	uint32_t v_color;
	uint32_t h_color;
	mlx_data_t *mlx_data;
} data_t;

typedef struct view_3d_s{
	int	w_height;
	int s_y;
	int e_y;
	int wall_half;
	double hor;
	double ver;
	double r_angle;
	double hor_x;
	double hor_y;
	double ver_x;
	double ver_y;
	int ver_ray;
}	view_3d_t;


typedef struct line_s{
	int x0;
	int y0;
	int y1;
}	line_t;

typedef struct moves_s{
    int update;
    double next_y;
    double next_x;
    double speed;
}   moves_t;

typedef struct wall_3d_s
{
	int i;
	int	v_i;
	int tex_x;
	double step;
	double tex_i;
	int col_i;
	uint32_t col;
	mlx_image_t *tx;
} wall_3d_t;



char	*ft_itoa(int n);
// void draw_3d(data_t *data);
double shoot_horizontal(data_t *d, double ray_angle, view_3d_t *d_3d);
double shoot_vertical(data_t *data, double angle, view_3d_t *d_3d);
double shoot_horizontal_2d(data_t *d, double angle, double *h_x, double *h_y);
double shoot_vertical_2d(data_t *data, double angle, double *v_x, double *v_y);
void hook_handler(void *param);
void draw_3d(void *data);
void minimap(data_t *data, mlx_data_t *mlx_data);
void put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void draw_filled_disk(mlx_image_t *img, int xc, int yc, int r);
uint32_t rgb(int r, int g, int b, int a);

void end_game(data_t *d, char *message);


// 2D view
int *shoot_rays(data_t *data);
void draw_minimap(data_t *data);
void minimap(data_t *data, mlx_data_t *mlx_data);
void	draw_line_2(mlx_image_t *img, int x0, int y0, int x1, int y1, int color);
void	pre_horizontal(raycaster_t *ray_d, double angle, data_t *data);
void	pre_vertical(raycaster_t *ray_d, double angle, data_t *data);

//3D view
void	map_refresh(data_t *d, moves_t *m);
void	re_put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void	draw_ceiling(data_t *d, int x0, int y0);
void	draw_wall_hor(data_t *data, line_t *line, view_3d_t *d_3d);
void	draw_wall_ver(data_t *data, line_t *line, view_3d_t *d_3d);
void	move_right(data_t *data, moves_t *m_d);
void	move_left(data_t *data, moves_t *m_d);
void	move_up(data_t *data, moves_t *m_d);
void	move_down(data_t *data, moves_t *m_d);


void end_game(data_t *d, char *message);
void free_parsing(map_context_h *p_data);
void find_player(data_t *data);
void link_parsing(data_t *d, map_context_h *p_data, mlx_data_t *mlx_data);
void pre_compute(data_t *data);
void update_position(data_t *data, char c, int i, int j);
void start_mlx(data_t *d, map_context_h *p_data);


void ft_draw_map(data_t *data);
#endif

