/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:51:05 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/09 14:51:06 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX/include/MLX42/MLX42.h"
# include <fcntl.h>
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

# define CUBE3D 1
# define FOV 1.1519
# define NUMBER_OF_RAYS 2040
# define TILE_SIZE 40
# define OUT_OF_RANGE 2147483647
# define TILE 1280
# define WIDTH 2040
# define HEIGHT 1280
# define MAX_VIEW 12800
# define FOG_START 0
# define MAX_VIEW_FLASH 25600
# define FOG_START_FLASH 5120
# define RIGHT 1
# define LEFT 0
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct offset_s
{
	double	e_offset;
	double	s_offset;
	double	w_offset;
	double	n_offset;

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
	mlx_t		*mlx;
	mlx_image_t	*view;
	mlx_image_t	*view_3d;
	mlx_image_t	*floor_ceiling;
	mlx_image_t	*empty;
	mlx_image_t	*wall;
	mlx_image_t	*rays_image;
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*east;
	mlx_image_t	*west;
}				t_mlx_data;

typedef struct raycaster_s{
	int		map_y;
	int		map_x;
	int		step;
	int		offset;
	double	hit_x;
	double	hit_y;
	double	direction_x;
	double	direction_y;
	double	scaling_factor;
}			t_raycaster;

typedef struct data_s{
	int			map_x;
	int			map_y;
	int			fog_start;
	int			fog_m;
	int			width;
	int			height;
	char		**map;
	double		player_x;
	double		player_y;
	double		p_angle;
	double		dir_x;
	double		dir_y;
	float		*cos;
	t_constant	con;
	t_offset	offset;
	uint32_t	ceiling;
	uint32_t	floor;
	uint32_t	v_color;
	uint32_t	h_color;
	t_mlx_data	*mlx_data;
}				t_data;

typedef struct view_3d_s{
	int		w_height;
	int		s_y;
	int		e_y;
	int		wall_half;
	int		ver_ray;
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

typedef struct moves_s
{
	int		update;
	double	next_y;
	double	next_x;
	double	speed;
}			t_moves;

typedef struct wall_3d_s
{
	int			i;
	int			v_i;
	int			tex_x;
	int			col_i;
	double		step;
	double		tex_i;
	uint32_t	col;
	mlx_image_t	*tx;
}				t_wall_3d;

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

char		*ft_itoa(int n);
void		draw_3d(void *data);
int			ft_strlen(char *str);
char		*get_next_line(int fd);
char		*ft_get_string(int num);
long		ft_atoi(const char *str);
int			size_of_line(char **str);
void		pre_compute(t_data *data);
void		hook_handler(void *param);
void		find_player(t_data *data);
int			ft_check_space(char *str);
int			ft_cmpr(char *s, char *s1);
void		ft_bzero(void *s, size_t n);
char		**ft_split(char *s, char c);
int			ft_strcmp(char **s, char *s1);
char		*ft_strjoin(char *s1, char *s2);
uint32_t	rgb(int r, int g, int b, int a);
int			ft_count_words( char *s1, int c);
void		ft_set_map(t_map_context_h *map);
void		ft_free_map(t_map_context_h *map);
void		end_game(t_data *d, char *message);
void		end_game(t_data *d, char *message);
void		map_refresh(t_data *d, t_moves *m);
void		ft_valid_path(t_map_context_h *map);
void		move_up(t_data *data, t_moves *m_d);
int			new_line_check(char *str, int *len);
void		free_parsing(t_map_context_h *p_data);
void		ft_double_array(t_map_context_h *map);
void		ft_check_player(t_map_context_h *map);
void		move_left(t_data *data, t_moves *m_d);
void		move_down(t_data *data, t_moves *m_d);
void		move_right(t_data *data, t_moves *m_d);
void		draw_ceiling(t_data *d, int x0, int y0);
void		ft_adjust_map_size(t_map_context_h *map);
void		ft_look_cub(char *s, t_map_context_h *map);
void		start_mlx(t_data *d, t_map_context_h *p_data);
void		ft_read_map(t_map_context_h *map, char *line);
void		ft_read_file(char *line, t_map_context_h *map);
void		ft_check_first_last_line(t_map_context_h *map);
void		ft_display_error(char *s, t_map_context_h *map);
void		ft_check_line(char *line, t_map_context_h *map);
void		ft_check_for_error(char *str, t_map_context_h *map);
void		update_position(t_data *data, char c, int i, int j);
void		flashlight(struct mlx_key_data keydata, void *param);
char		*ft_strdup_n(char *str, int a, t_map_context_h *map);
char		*ft_strjoin_n(char *s1, char *s2, t_map_context_h *map);
void		ft_fill_struct(t_map_context_h *map, char **str, int s);
void		ft_convert_color(t_map_context_h *map, char *str, int i);
void		put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		draw_filled_disk(mlx_image_t *img, int xc, int yc, int r);
void		draw_wall_hor(t_data *data, t_line *line, t_view_3d *d_3d);
void		draw_wall_ver(t_data *data, t_line *line, t_view_3d *d_3d);
double		shoot_vertical(t_data *data, double angle, t_view_3d *d_3d);
void		re_put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		parsing(int argc, char **argv, t_map_context_h *parsing_data);
void		textured_line(t_data *d, t_view_3d *d_3d, t_line *line, int i);
void		ft_fill_color_array(t_map_context_h *map, char **array, int i);
double		shoot_horizontal(t_data *d, double ray_angle, t_view_3d *d_3d);
uint32_t	apply_fog(t_data *data, uint32_t original_color, double distance);
void		link_parsing(t_data *d, t_map_context_h *p_data, t_mlx_data *m_d);

#endif