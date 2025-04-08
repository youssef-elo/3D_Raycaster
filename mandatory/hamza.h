/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hamza.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:04:29 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/08 21:07:16 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HAMZA_H
# define HAMZA_H
# include "youssef.h"
# include <fcntl.h>

# define TILE_SIZE 40

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

int		ft_count_words( char *s1, int c);
void	parsing(int argc, char **argv, t_map_context_h *parsing_data);
char	**ft_split(char *s, char c);
char	*ft_strdup_n(char *str, int a, t_map_context_h *map);
char	*ft_strjoin_n(char *s1, char *s2, t_map_context_h *map);
int		ft_cmpr(char *s, char *s1);
int		ft_strcmp(char **s, char *s1);
long	ft_atoi(const char *str);
void	ft_free_map(t_map_context_h *map);
void	ft_display_error(char *s, t_map_context_h *map);
void	ft_look_cub(char *s, t_map_context_h *map);
int		size_of_line(char **str);
void	ft_set_map(t_map_context_h *map);
char	*ft_get_string(int num);
void	ft_adjust_map_size(t_map_context_h *map);
void	ft_read_file(char *line, t_map_context_h *map);
void	ft_read_map(t_map_context_h *map, char *line);
void	ft_fill_struct(t_map_context_h *map, char **str, int s);
void	ft_check_line(char *line, t_map_context_h *map);
int		ft_check_space(char *str);
void	ft_check_for_error(char *str, t_map_context_h *map);
void	ft_fill_color_array(t_map_context_h *map, char **array, int i);
void	ft_convert_color(t_map_context_h *map, char *str, int i);
void	ft_check_first_last_line(t_map_context_h *map);
void	ft_check_player(t_map_context_h *map);
void	ft_valid_path(t_map_context_h *map);
void	ft_double_array(t_map_context_h *map);

#endif