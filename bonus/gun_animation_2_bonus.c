/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_animation_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:40 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/08 18:20:41 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	fire_animation(t_data *data, int *f, int *i)
{
	if (*f == 0)
	{
		data->mlx_data->gun_view->instances[0].enabled = false;
		data->mlx_data->fire_view->instances[0].enabled = true;
	}
	fire_frame(data, (*f) % 6, (*f) / 6);
	(*f)++;
	if (*f == 1)
		data->mlx_data->muzzle->instances[0].enabled = true;
	if (*f == 7)
		data->mlx_data->muzzle->instances[0].enabled = false;
	if (*f == 23)
	{
		*f = 0;
		data->mlx_data->gun_view->instances[0].enabled = true;
		data->mlx_data->fire_view->instances[0].enabled = false;
		*i = 0;
	}
}

void	reload_animation(t_data *data, int *i, int *r, double *last_time)
{
	if (*r == 0)
	{
		data->mlx_data->reload_view->instances[0].enabled = true;
		data->mlx_data->gun_view->instances[0].enabled = false;
	}
	reload_frame(data, (*r) % 8, (*r) / 8);
	(*r)++;
	if (*r == 44)
	{
		data->reload = 0;
		*r = 0;
		data->mlx_data->gun_view->instances[0].enabled = true;
		data->mlx_data->reload_view->instances[0].enabled = false;
		*i = 0;
	}
	*last_time = mlx_get_time();
}

void	gun_animation(void *param)
{
	static int		i;
	static int		r;
	static int		f;
	static double	last_time;
	t_data			*data;

	data = (t_data *)param;
	if (!last_time)
		last_time = mlx_get_time();
	if (data->firing || (!data->firing && f != 0))
		fire_animation(data, &f, &i);
	if (mlx_get_time() - last_time >= 0.035f)
	{
		if (data->walking && !data->reload && (!data->firing && f == 0))
		{
			if (i == 44)
				i = 0;
			gun_frame(data, i % 8, i / 8);
			i++;
			last_time = mlx_get_time();
		}
		if (data->reload && (!data->firing && f == 0))
			reload_animation(data, &i, &r, &last_time);
	}
}
