/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_toggles_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:50 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/16 18:56:57 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	rotate_mouse(double xpos, double ypos, void *param)
{
	double	dx;
	double	angle;
	t_data	*data;

	data = (t_data *)param;
	dx = WIDTH / 2 - xpos;
	ypos = ypos - 1;
	if (fabs(dx) < 40)
		return ;
	angle = dx * ROTATION_FACTOR;
	angle = 0.05 * (angle / 0.05);
	data->p_angle += angle;
	if (data->p_angle > ((double)2 * M_PI))
		data->p_angle -= (2 * M_PI);
	if (data->p_angle < 0)
		data->p_angle += (2 * M_PI);
	data->dir_x = cos(data->p_angle);
	data->dir_y = sin(data->p_angle);
	mlx_set_mouse_pos(data->mlx_data->mlx, WIDTH / 2, HEIGHT / 2);
}

void	fire(mouse_key_t butt, action_t act, modifier_key_t mods, void *p)
{
	t_data	*data;

	data = (t_data *)p;
	mods--;
	if (butt == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS)
	{
		if (!data->reload)
		{
			data->firing = 1;
			data->holding = 1;
		}
	}
	if (butt == MLX_MOUSE_BUTTON_LEFT && act == MLX_RELEASE)
	{
		data->holding = 0;
		data->firing = 0;
	}
}

void	open_vertical_doors(t_data *data)
{
	if ((data->p_angle >= M_PI_4) && data->p_angle < (3 * M_PI_4))
	{
		if (data->map[data->map_y - 1][data->map_x] == 'O')
			data->map[data->map_y - 1][data->map_x] = 'D';
		else if (data->map[data->map_y - 1][data->map_x] == 'D')
			data->map[data->map_y - 1][data->map_x] = 'O';
	}
	if ((data->p_angle >= (5 * M_PI_4)) && data->p_angle < (7 * M_PI_4))
	{
		if (data->map[data->map_y + 1][data->map_x] == 'O')
			data->map[data->map_y + 1][data->map_x] = 'D';
		else if (data->map[data->map_y + 1][data->map_x] == 'D')
			data->map[data->map_y + 1][data->map_x] = 'O';
	}
}

void	open_horizontal_doors(t_data *data)
{
	if (data->p_angle >= (3 * M_PI_4) && data->p_angle < (5 * M_PI_4))
	{
		if (data->map[data->map_y][data->map_x - 1] == 'O')
			data->map[data->map_y][data->map_x - 1] = 'D';
		else if (data->map[data->map_y][data->map_x - 1] == 'D')
			data->map[data->map_y][data->map_x - 1] = 'O';
	}
	if ((data->p_angle >= 0 && data->p_angle < M_PI_4)
		|| (data->p_angle >= (7 * M_PI_4)))
	{
		if (data->map[data->map_y][data->map_x + 1] == 'O')
			data->map[data->map_y][data->map_x + 1] = 'D';
		else if (data->map[data->map_y][data->map_x + 1] == 'D')
			data->map[data->map_y][data->map_x + 1] = 'O';
	}
}

void	flashlight(struct mlx_key_data keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
	{
		if (data->fog_start == FOG_START)
		{
			data->fog_start = FOG_START_FLASH;
			data->fog_m = MAX_VIEW_FLASH;
		}
		else
		{
			data->fog_start = FOG_START;
			data->fog_m = MAX_VIEW;
		}
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		data->reload = 1;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		open_vertical_doors(data);
		open_horizontal_doors(data);
	}
}
