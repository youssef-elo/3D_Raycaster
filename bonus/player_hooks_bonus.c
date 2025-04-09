/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hooks_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:21:04 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/09 15:15:04 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_angle(t_data *data)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_RIGHT))
	{
		data->p_angle -= 0.05f;
		if (data->p_angle < 0)
			data->p_angle += (2 * M_PI);
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
		minimap_3d(data);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
	{
		data->p_angle += 0.05f;
		if (data->p_angle > ((double)2 * M_PI))
			data->p_angle -= (2 * M_PI);
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
		minimap_3d(data);
	}
}

void	vertical_movement(t_data *data, t_moves *m_d, int *moving)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_W))
	{
		m_d->next_x = data->player_x + (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_y * m_d->speed);
		*moving = 1;
		data->walking = 1;
		move_up(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_S))
	{
		m_d->next_x = data->player_x - (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_y * m_d->speed);
		data->walking = 1;
		*moving = 1;
		move_down(data, m_d);
	}
}

void	map_refresh_2(t_data *d, t_moves *m_d, int *changed, int map_x)
{
	int		map_y;
	double	pre_y;

	pre_y = d->player_y;
	map_y = (int)(m_d->next_y) / TILE;
	if (d->map[map_y][d->map_x] == '0' || d->map[map_y][d->map_x] == 'O')
	{
		d->player_y = m_d->next_y;
		d->map_y = map_y;
		*changed = 1;
	}
	if (d->map[d->map_y][map_x] == '0' || d->map[d->map_y][map_x] == 'O')
	{
		d->player_x = m_d->next_x;
		d->map_x = map_x;
		*changed = 1;
	}
	if (d->map[d->map_y][d->map_x] == '1' || d->map[d->map_y][d->map_x] == 'D')
	{
		d->player_y = pre_y;
		d->map_y = pre_y / TILE;
		*changed = 1;
	}
}

void	map_refresh(t_data *data, t_moves *m_d)
{
	int	map_x;
	int	changed;

	changed = 0;
	map_x = (int)(m_d->next_x) / TILE;
	map_refresh_2(data, m_d, &changed, map_x);
	if (changed)
		minimap_3d(data);
}

void	hook_handler(void *param)
{
	t_data	*data;
	t_moves	moves;

	moves.update = 0;
	moves.speed = 170;
	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT_SHIFT))
		moves.speed = 280;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_ESCAPE))
		end_game(data, "Game ended\n");
	player_movement(data, &moves);
	move_angle(data);
}
