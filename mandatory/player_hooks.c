/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:22:45 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/08 18:22:46 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_angle(t_data *data)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_RIGHT))
	{
		data->p_angle -= 0.05f;
		if (data->p_angle < 0)
			data->p_angle += (2 * M_PI);
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
	{
		data->p_angle += 0.05f;
		if (data->p_angle > ((double)2 * M_PI))
			data->p_angle -= (2 * M_PI);
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
	}
}

void	player_movement(t_data *data, t_moves *m_d)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_W))
	{
		m_d->next_x = data->player_x + (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_y * m_d->speed);
		move_up(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_S))
	{
		m_d->next_x = data->player_x - (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_y * m_d->speed);
		move_down(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_A))
	{
		m_d->next_x = data->player_x - (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_x * m_d->speed);
		move_left(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_D))
	{
		m_d->next_x = data->player_x + (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_x * m_d->speed);
		move_right(data, m_d);
	}
}

void	map_refresh(t_data *data, t_moves *m_d)
{
	int		map_x;
	int		map_y;
	double	pre_y;

	pre_y = data->player_y;
	map_x = (int)(m_d->next_x) / TILE;
	map_y = (int)(m_d->next_y) / TILE;
	if (data->map[map_y][data->map_x] == '0')
	{
		data->player_y = m_d->next_y;
		data->map_y = map_y;
	}
	if (data->map[data->map_y][map_x] == '0')
	{
		data->player_x = m_d->next_x;
		data->map_x = map_x;
	}
	if (data->map[data->map_y][data->map_x] == '1')
	{
		data->player_y = pre_y;
		data->map_y = pre_y / TILE;
	}
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
