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
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

#define CUBE3D 1



#define GUN_W 877
#define GUN_H 580

#define FIRE_W 898
#define FIRE_H 570

#define RELOAD_W 1394
#define RELOAD_H 736


#define PI 3.141592653589793
#define FOV 1.1519
#define NUMBER_OF_RAYS 2040
// #define CUBE3D 0
#define OUT_OF_RANGE 2147483647
#define SPEED 4

// 8 21
#define M_HEIGHT 210
#define M_WIDTH 250
#define M_H_HEIGHT 105
#define M_H_WIDTH 125

#define TILE 1280

#define WIDTH 2040
#define HEIGHT 1280

#define ROTATION_FACTOR M_PI_4 / WIDTH

#define MAX_VIEW TILE * 10
#define FOG_START 0

#define MAX_VIEW_FLASH TILE * 20
#define FOG_START_FLASH TILE * 4

#define RIGHT 1
#define LEFT 0


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif




// #define WIDTH 29 * TILE
// #define HEIGHT 8 * TILE
#define BPP sizeof(int32_t)

typedef struct matrix_s
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	int		i;
	int		j;
	int		rx;
	int		ry;
	int		dx;
	int		dy;
}				matrix_t;

typedef struct offset_s
{
	double e_offset;
	double s_offset;
	double w_offset;
	double n_offset;
	double d_offset;
}	t_offset;


typedef struct constant_s
{
	int p;
	double scaler;
	double fov_half;
	double angle_i;
	int half_window;
} t_constant;

typedef struct mlx_data_s{
	mlx_t *mlx;
	mlx_image_t *view_3d;
	mlx_image_t *gun_view;
	mlx_image_t *muzzle;
	mlx_image_t *reload_view;
	mlx_image_t *fire_view;
	mlx_image_t *mini_map;
	mlx_image_t *north;
	mlx_image_t *south;
	mlx_image_t *east;
	mlx_texture_t *gun_sheet;
	mlx_texture_t *reload_sheet;
	mlx_texture_t *fire_sheet;
	mlx_image_t *west;
	mlx_image_t *door;
	mlx_image_t *fps;
} t_mlx_data;

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
}	t_raycaster;

typedef struct data_s{
	double player_x;
	double player_y;
	int		map_x;
	int		map_y;
	double p_angle;
	int	 fog_start;
	int	 fog_m;
	double dir_x;
	double dir_y;
	int width;
	int height;
	char **map;
	float *cos;
	int walking;
	int firing;
	int reload;
	t_constant con;
	t_offset offset;
	uint32_t ceiling;
	uint32_t floor;
	uint32_t v_color;
	uint32_t h_color;
	t_mlx_data *mlx_data;
} t_data;

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
	int door_v;
	int door_h;
}	t_view_3d;


typedef struct line_s{
	int x0;
	int y0;
	int y1;
}	t_line;

typedef struct moves_s{
    int		update;
    double	next_y;
    double	next_x;
    double	speed;
}			t_moves;

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
} t_wall_3d;


char		*ft_itoa(int n);
double		shoot_horizontal(t_data *d, double ray_angle, t_view_3d *d_3d);
double		shoot_vertical(t_data *data, double angle, t_view_3d *d_3d);
void		hook_handler(void *param);
void		draw_3d(void *data);
uint32_t	apply_fog(t_data *d, uint32_t o_color, double dis);
void		put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		draw_filled_disk(mlx_image_t *img, int xc, int yc, int r);
uint32_t	rgb(int r, int g, int b, int a);
void		end_game(t_data *d, char *message);
void		vertical_movement(t_data *data, t_moves *m_d, int *moving);
char		*get_next_line(int fd);
char		*ft_strdup(char *s1, int b);
int			ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);
void		ft_bzero(void *s, size_t n);
int			new_line_check(char *str, int *len);
void		map_refresh(t_data *d, t_moves *m);
void		re_put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		draw_ceiling(t_data *d, int x0, int y0);
void		draw_wall_hor(t_data *data, t_line *line, t_view_3d *d_3d);
void		draw_wall_ver(t_data *data, t_line *line, t_view_3d *d_3d);
void		move_right(t_data *data, t_moves *m_d);
void		move_left(t_data *data, t_moves *m_d);
void		move_up(t_data *data, t_moves *m_d);
void		move_down(t_data *data, t_moves *m_d);
void		player_movement(t_data *data, t_moves *m_d);
void		end_game(t_data *d, char *message);
void		free_parsing(map_context_h *p_data);
void		find_player(t_data *data);
void		link_parsing(t_data *d, map_context_h *p_data, t_mlx_data *mlx_data);
void		pre_compute(t_data *data);
void		update_position(t_data *data, char c, int i, int j);
void		start_mlx(t_data *d, map_context_h *p_data);
void		textured_line(t_data *d, t_view_3d *d_3d, t_line *line, int i);
void		gun_animation(void *param);
void		reload_frame(t_data *data, int x, int y);
void		gun_frame(t_data *data, int x, int y);
void		fire_frame(t_data *data, int x, int y);
void		gun_animation(void *param);
void		open_fire(mouse_key_t butt, action_t act, modifier_key_t mods, void* p);
void		rotate_mouse(double xpos, double ypos, void* param);
void		flashlight(struct mlx_key_data keydata, void *param);
void		put_images(t_data *d);
void		set_hooks(t_data *data);
void		minimap_3d(t_data *data);
#endif

