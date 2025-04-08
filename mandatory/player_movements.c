/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:22:47 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/08 18:22:48 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_data *d, t_moves *m_d)
{
	int	c;

	c = 350;
	if (d->p_angle <= M_PI)
		c = -350;
	if (d->map[(int)m_d->next_y / TILE][d->map_x] == '1'
		|| d->map[(int)(m_d->next_y + c) / TILE][d->map_x] == '1')
	{
		if (c == -350)
			m_d->next_y = (d->map_y * TILE) + 350;
		else
			m_d->next_y = ((d->map_y * TILE) + ((TILE - 350)));
	}
	c = -350;
	if ((d->p_angle <= (M_PI_2)) || (d->p_angle >= (3 * (M_PI_2))))
		c = 350;
	if (d->map[d->map_y][(int)m_d->next_x / TILE] == '1'
		|| (d->map[d->map_y][(int)(m_d->next_x + c) / TILE] == '1'))
	{
		if (c == 350)
			m_d->next_x = (d->map_x * TILE) + (TILE - 350);
		else
			m_d->next_x = (d->map_x * TILE) + 350;
	}
	map_refresh(d, m_d);
}

void	move_down(t_data *data, t_moves *m_d)
{
	int	check;

	check = -350;
	if (data->p_angle < M_PI)
		check = 350;
	if (data->map[(int)(m_d->next_y) / TILE][data->map_x] == '1'
		|| data->map[(int)(m_d->next_y + check) / TILE][data->map_x] == '1')
	{
		if (check == 350)
			m_d->next_y = (data->map_y * TILE) + ((TILE - 350));
		else
			m_d->next_y = (data->map_y * TILE) + 350;
	}
	check = 350;
	if (data->p_angle <= (M_PI_2) || data->p_angle >= (3 * (M_PI_2)))
		check = -350;
	if (data->map[data->map_y][(int)(m_d->next_x) / TILE] == '1'
		|| (data->map[data->map_y][(int)(m_d->next_x + check) / TILE] == '1'))
	{
		if (check == -350)
			m_d->next_x = (data->map_x * TILE) + 350;
		else
			m_d->next_x = (data->map_x * TILE) + (TILE - 350);
	}
	map_refresh(data, m_d);
}

void	move_left(t_data *data, t_moves *m_d)
{
	int	check;

	check = -350;
	if (data->p_angle >= (M_PI_2) && data->p_angle <= (3 * (M_PI_2)))
		check = 350;
	if (data->map[(int)(m_d->next_y) / TILE][data->map_x] == '1'
		|| data->map[(int)(m_d->next_y + check) / TILE][data->map_x] == '1')
	{
		if (check == 350)
			m_d->next_y = (data->map_y * TILE) + ((TILE - 350));
		else
			m_d->next_y = (data->map_y * TILE) + 350;
	}
	check = 350;
	if (data->p_angle >= 0 && data->p_angle <= M_PI)
		check = -350;
	if (data->map[data->map_y][(int)(m_d->next_x) / TILE] == '1'
		|| (data->map[data->map_y][(int)(m_d->next_x + check) / TILE] == '1'))
	{
		if (check == -350)
			m_d->next_x = (data->map_x * TILE) + 350;
		else
			m_d->next_x = (data->map_x * TILE) + (TILE - 350);
	}
	map_refresh(data, m_d);
}

void	move_right(t_data *data, t_moves *m_d)
{
	int	check;

	check = 350;
	if (data->p_angle >= (M_PI_2) && data->p_angle <= (3 * (M_PI_2)))
		check = -350;
	if (data->map[(int)(m_d->next_y) / TILE][data->map_x] == '1'
		|| data->map[(int)(m_d->next_y + check) / TILE][data->map_x] == '1')
	{
		if (check == -350)
			m_d->next_y = ((data->map_y) * TILE) + 350;
		else
			m_d->next_y = ((data->map_y) * TILE) + ((TILE - 350));
	}
	check = -350;
	if (data->p_angle >= 0 && data->p_angle <= M_PI)
		check = 350;
	if (data->map[data->map_y][(int)(m_d->next_x) / TILE] == '1'
		|| (data->map[data->map_y][(int)(m_d->next_x + check) / TILE] == '1'))
	{
		if (check == 350)
			m_d->next_x = (data->map_x * TILE) + (TILE - 350);
		else
			m_d->next_x = (data->map_x * TILE) + 350;
	}
	map_refresh(data, m_d);
}
