/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_animation_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:44 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/15 19:02:24 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	gun_frame(t_data *data, int x, int y)
{
	int	i;
	int	j;
	int	k;
	int	v_index;
	int	g_index;

	i = 0;
	j = y * GUN_H;
	k = x * GUN_W;
	while (i < GUN_H)
	{
		g_index = (((j) * data->mlx_data->gun_sheet->width) + (k));
		v_index = (i * data->mlx_data->gun_view->width);
		memcpy((uint32_t *) data->mlx_data->gun_view->pixels + v_index,
			(uint32_t *) data->mlx_data->gun_sheet->pixels + g_index,
			GUN_W * 4);
		i++;
		j++;
	}
}

void	reload_frame(t_data *data, int x, int y)
{
	int	i;
	int	j;
	int	k;
	int	v_index;
	int	g_index;

	i = 0;
	j = y * RELOAD_H;
	k = x * RELOAD_W;
	while (i < RELOAD_H)
	{
		g_index = (((j) * data->mlx_data->reload_sheet->width) + (k));
		v_index = (i * data->mlx_data->reload_view->width);
		memcpy((uint32_t *)data->mlx_data->reload_view->pixels + v_index,
			(uint32_t *)data->mlx_data->reload_sheet->pixels + g_index,
			RELOAD_W * 4);
		i++;
		j++;
	}
}

void	fire_frame(t_data *data, int x, int y)
{
	int	i;
	int	j;
	int	k;
	int	v_index;
	int	g_index;

	i = 0;
	j = y * FIRE_H;
	k = x * FIRE_W;
	while (i < FIRE_H)
	{
		g_index = (((j) * data->mlx_data->fire_sheet->width) + (k));
		v_index = (i * data->mlx_data->fire_view->width);
		memcpy((uint32_t *) data->mlx_data->fire_view->pixels + v_index,
			(uint32_t *) data->mlx_data->fire_sheet->pixels + g_index,
			FIRE_W * 4);
		i++;
		j++;
	}
}
