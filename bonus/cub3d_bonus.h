/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:01:57 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/16 18:42:41 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../MLX/include/MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <strings.h>
# include <time.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>

# define CUBE3D 1
# define GUN_W 877
# define GUN_H 580
# define FIRE_W 898
# define FIRE_H 570
# define RELOAD_W 1394
# define RELOAD_H 736
# define FOV 1.1519
# define NUMBER_OF_RAYS 2040
# define OUT_OF_RANGE 2147483647
# define M_HEIGHT 210
# define M_WIDTH 250
# define M_H_HEIGHT 105
# define M_H_WIDTH 125
# define TILE 1280
# define WIDTH 2040
# define HEIGHT 1280
# define ROTATION_FACTOR 0.000385
# define MAX_VIEW 12800
# define FOG_START 0
# define MAX_VIEW_FLASH 25600
# define FOG_START_FLASH 5120
# define TILE_SIZE 40
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct map_context_s
{
	char	**map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*array;
	char	*floor_s;
	char	*sky_s;
	int		count;
	int		sky[3];
	int		floor[3];
	int		read_map;

}	t_map_context_h;

typedef struct mini_map_s
{
	mlx_image_t		*mini_map_img;
	mlx_image_t		*player;
	mlx_texture_t	*texture;
	int				player_x;
	int				player_y;

}	t_mini_map_h;

typedef struct var_size_s
{
	int		x;
	int		i;
	int		y;
	int		max;
	char	*array;
}	t_var_size_h;

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
}			t_matrix;

typedef struct offset_s
{
	double	e_offset;
	double	s_offset;
	double	w_offset;
	double	n_offset;
	double	d_offset;
}			t_offset;

typedef struct constant_s
{
	int		p;
	double	scaler;
	double	fov_half;
	double	angle_i;
	int		half_window;
}			t_constant;

typedef struct mlx_data_s{
	mlx_t			*mlx;
	mlx_image_t		*view_3d;
	mlx_image_t		*gun_view;
	mlx_image_t		*muzzle;
	mlx_image_t		*reload_view;
	mlx_image_t		*fire_view;
	mlx_image_t		*mini_map;
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*east;
	mlx_texture_t	*gun_sheet;
	mlx_texture_t	*reload_sheet;
	mlx_texture_t	*fire_sheet;
	mlx_image_t		*west;
	mlx_image_t		*door;
	mlx_image_t		*fps;
}					t_mlx_data;

typedef struct raycaster_s{
	double	hit_x;
	double	hit_y;
	double	direction_x;
	double	direction_y;
	double	scaling_factor;
	int		map_y;
	int		map_x;
	int		step;
	int		offset;
}			t_raycaster;

typedef struct data_s{
	int			map_x;
	int			map_y;
	int			fog_start;
	int			fog_m;
	int			width;
	int			height;
	int			walking;
	int			firing;
	int			reload;
	double		player_x;
	double		player_y;
	double		p_angle;
	double		dir_x;
	double		dir_y;
	float		*cos;
	uint32_t	ceiling;
	uint32_t	floor;
	uint32_t	v_color;
	int			holding;
	uint32_t	h_color;
	char		**map;
	t_constant	con;
	t_offset	offset;
	t_mlx_data	*mlx_data;
}				t_data;

typedef struct view_3d_s{
	int		w_height;
	int		s_y;
	int		e_y;
	int		wall_half;
	int		ver_ray;
	int		door_v;
	int		door_h;
	double	hor;
	double	ver;
	double	r_angle;
	double	hor_x;
	double	hor_y;
	double	ver_x;
	double	ver_y;
}			t_view_3d;

typedef struct line_s{
	int	x0;
	int	y0;
	int	y1;
}		t_line;

typedef struct moves_s{
	int		update;
	double	next_y;
	double	next_x;
	double	speed;
}			t_moves;

typedef struct wall_3d_s
{
	int			i;
	int			v_i;
	int			col_i;
	int			tex_x;
	double		step;
	double		tex_i;
	uint32_t	col;
	mlx_image_t	*tx;
}				t_wall_3d;

char		*ft_itoa(int n);
void		draw_3d(void *data);
int			ft_strlen(char *str);
void		put_images(t_data *d);
void		put_fps(t_data *data);
char		*get_next_line(int fd);
void		set_hooks(t_data *data);
char		*ft_get_string(int num);
long		ft_atoi(const char *str);
int			size_of_line(char **str);
void		minimap_3d(t_data *data);
void		cross_close(void *param);
void		hook_handler(void *param);
int			ft_check_space(char *str);
void		find_player(t_data *data);
void		pre_compute(t_data *data);
void		gun_animation(void *param);
void		gun_animation(void *param);
int			ft_cmpr(char *s, char *s1);
char		*ft_strdup(char *s1, int b);
char		**ft_split(char *s, char c);
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(char **s, char *s1);
char		*ft_strjoin(char *s1, char *s2);
uint32_t	rgb(int r, int g, int b, int a);
void		ft_set_map(t_map_context_h *map);
int			ft_count_words( char *s1, int c);
void		ft_free_map(t_map_context_h *map);
void		map_refresh(t_data *d, t_moves *m);
void		end_game(t_data *d, char *message);
void		end_game(t_data *d, char *message);
void		ft_valid_path(t_map_context_h *map);
void		ft_valid_door(t_map_context_h *map);
int			new_line_check(char *str, int *len);
void		move_up(t_data *data, t_moves *m_d);
void		ft_check_player(t_map_context_h *map);
void		ft_double_array(t_map_context_h *map);
void		free_parsing(t_map_context_h *p_data);
void		gun_frame(t_data *data, int x, int y);
void		move_left(t_data *data, t_moves *m_d);
void		move_down(t_data *data, t_moves *m_d);
void		move_right(t_data *data, t_moves *m_d);
void		fire_frame(t_data *data, int x, int y);
void		draw_ceiling(t_data *d, int x0, int y0);
void		reload_frame(t_data *data, int x, int y);
void		ft_adjust_map_size(t_map_context_h *map);
void		ft_look_cub(char *s, t_map_context_h *map);
void		player_movement(t_data *data, t_moves *m_d);
void		start_mlx(t_data *d, t_map_context_h *p_data);
void		ft_read_map(t_map_context_h *map, char *line);
void		ft_check_first_last_line(t_map_context_h *map);
void		ft_read_file(char *line, t_map_context_h *map);
void		ft_check_line(char *line, t_map_context_h *map);
void		ft_display_error(char *s, t_map_context_h *map);
uint32_t	apply_fog(t_data *d, uint32_t o_color, double dis);
void		update_position(t_data *data, char c, int i, int j);
void		rotate_mouse(double xpos, double ypos, void *param);
void		ft_check_for_error(char *str, t_map_context_h *map);
char		*ft_strdup_n(char *str, int a, t_map_context_h *map);
void		flashlight(struct mlx_key_data keydata, void *param);
char		*ft_strjoin_n(char *s1, char *s2, t_map_context_h *map);
void		ft_fill_struct(t_map_context_h *map, char **str, int s);
void		ft_convert_color(t_map_context_h *map, char *str, int i);
void		draw_filled_disk(mlx_image_t *img, int xc, int yc, int r);
void		put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		draw_wall_hor(t_data *data, t_line *line, t_view_3d *d_3d);
void		vertical_movement(t_data *data, t_moves *m_d, int *moving);
void		draw_wall_ver(t_data *data, t_line *line, t_view_3d *d_3d);
double		shoot_vertical(t_data *data, double angle, t_view_3d *d_3d);
void		re_put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		parsing_end(t_data *data, char *str, t_map_context_h *p_data);
void		parsing(int argc, char **argv, t_map_context_h *parsing_data);
void		textured_line(t_data *d, t_view_3d *d_3d, t_line *line, int i);
double		shoot_horizontal(t_data *d, double ray_angle, t_view_3d *d_3d);
void		ft_fill_color_array(t_map_context_h *map, char **array, int i);
void		link_parsing(t_data *d, t_map_context_h *p_data, t_mlx_data *m_d);
void		fire(mouse_key_t butt, action_t act, modifier_key_t mods, void *p);

#endif