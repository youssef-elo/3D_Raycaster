/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_animation_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:40 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/16 18:56:43 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	fire_animation(t_data *data, int *f, int *i)
{
	if (*f == 0)
	{
		data->mlx_data->gun_view->instances[0].enabled = false;
		data->mlx_data->fire_view->instances[0].enabled = true;
		data->firing = 0;
	}
	if (data->firing && *f)
	{
		*f = 0;
		data->firing = 0;
		data->mlx_data->muzzle->instances[0].enabled = false;
	}
	fire_frame(data, (*f) % 6, (*f) / 6);
	(*f)++;
	if (*f == 1)
		data->mlx_data->muzzle->instances[0].enabled = true;
	if (*f == 5)
		data->mlx_data->muzzle->instances[0].enabled = false;
	if (*f == 18)
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
	t_data			*d;

	d = (t_data *)param;
	if (!last_time)
		last_time = mlx_get_time();
	if (d->firing || (!d->firing && f != 0) || d->holding)
		fire_animation(d, &f, &i);
	if (mlx_get_time() - last_time >= 0.035f)
	{
		if (d->walking && !d->reload && (!d->firing && f == 0) && !d->holding)
		{
			if (i == 44)
				i = 0;
			gun_frame(d, i % 8, i / 8);
			i++;
			last_time = mlx_get_time();
		}
		if (d->reload && (!d->firing && f == 0) && !d->holding)
			reload_animation(d, &i, &r, &last_time);
	}
}
