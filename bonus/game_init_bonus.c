/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:34 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/10 17:48:42 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_position(t_data *data, char c, int i, int j)
{
	if (c == 'N')
		data->p_angle = M_PI_2;
	if (c == 'S')
		data->p_angle = 3 * (M_PI_2);
	if (c == 'E')
		data->p_angle = 0;
	if (c == 'W')
		data->p_angle = M_PI;
	data->player_y = (i * TILE) + (TILE / 2);
	data->player_x = (j * TILE) + (TILE / 2);
}

void	find_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				update_position(data, data->map[i][j], i, j);
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	data->width = j;
	data->height = i;
}

void	link_parsing(t_data *d, t_map_context_h *p_data, t_mlx_data *mlx_data)
{
	d->map = p_data->map;
	d->mlx_data = mlx_data;
	find_player(d);
	d->cos = malloc(sizeof(double) * NUMBER_OF_RAYS);
	if (!d->cos)
		parsing_end(d, "Malloc Failure\n", p_data);
	start_mlx(d, p_data);
	d->ceiling = rgb(p_data->sky[0], p_data->sky[1], p_data->sky[2], 255);
	d->floor = rgb(p_data->floor[0], p_data->floor[1], p_data->floor[2], 255);
	d->map_x = d->player_x / TILE;
	d->map_y = d->player_y / TILE;
	d->dir_x = cos(d->p_angle);
	d->dir_y = sin(d->p_angle);
	d->offset.n_offset = d->mlx_data->north->width / TILE;
	d->offset.d_offset = d->mlx_data->door->width / TILE;
	d->offset.s_offset = d->mlx_data->south->width / TILE;
	d->offset.e_offset = d->mlx_data->east->width / TILE;
	d->offset.w_offset = d->mlx_data->west->width / TILE;
}

void	pre_compute(t_data *d)
{
	int		i;
	double	r_angle;

	i = 0;
	d->con.angle_i = FOV / NUMBER_OF_RAYS;
	d->con.p = (WIDTH / 2) / tan(FOV / 2);
	d->con.scaler = d->con.p * TILE;
	d->con.fov_half = FOV / 2;
	d->con.half_window = HEIGHT / 2;
	while (i < NUMBER_OF_RAYS)
	{
		r_angle = (d->p_angle - d->con.fov_half) + (i * d->con.angle_i);
		d->cos[i] = cos(r_angle - d->p_angle);
		i++;
	}
	d->fog_start = FOG_START;
	d->fog_m = MAX_VIEW;
}
