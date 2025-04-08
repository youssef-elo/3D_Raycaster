/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:21:09 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/08 18:21:10 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	pre_hor_r(t_raycaster *ray_d, double angle, t_data *d, t_view_3d *d_3d)
{
	ray_d->direction_x = cos(angle);
	ray_d->direction_y = sin(angle);
	if (ray_d->direction_y < 0)
	{
		ray_d->step = TILE;
		ray_d->offset = 1;
		ray_d->hit_y = ((int)(d->player_y / TILE) + 1) * TILE;
	}
	else
	{
		ray_d->step = -TILE;
		ray_d->offset = -1;
		ray_d->hit_y = (int)(d->player_y / TILE) * TILE;
	}
	d_3d->door_h = 0;
}

double	shoot_horizontal(t_data *d, double angle, t_view_3d *d_3d)
{
	t_raycaster	r_d;

	pre_hor_r(&r_d, angle, d, d_3d);
	while (1)
	{
		r_d.scaling_factor = (d->player_y - r_d.hit_y) / r_d.direction_y;
		r_d.hit_x = d->player_x + (r_d.scaling_factor * r_d.direction_x);
		r_d.map_y = (r_d.hit_y + r_d. offset) / TILE;
		r_d.map_x = r_d.hit_x / TILE;
		if (r_d.hit_x < TILE || r_d.hit_x > ((d->width * TILE) - TILE))
			return (OUT_OF_RANGE);
		if (strchr("1D", d->map[r_d.map_y][r_d.map_x]))
		{
			d_3d->hor_x = r_d.hit_x;
			d_3d->hor_y = r_d.hit_y;
			if (d->map[r_d.map_y][r_d.map_x] == 'D')
				d_3d->door_h = 1;
			return (sqrt((r_d.hit_x - d->player_x) * (r_d.hit_x - d->player_x)
					+ (r_d.hit_y - d->player_y) * (r_d.hit_y - d->player_y)));
		}
		r_d.hit_y += r_d.step;
		if (r_d.hit_y < TILE || r_d.hit_y > ((d->height * TILE) - TILE))
			return (OUT_OF_RANGE);
	}
	return (OUT_OF_RANGE);
}

void	pre_ver_r(t_raycaster *ray_d, double angle, t_data *d, t_view_3d *d_3d)
{
	ray_d->direction_x = cos(angle);
	ray_d->direction_y = sin(angle);
	if (ray_d->direction_x < 0)
	{
		ray_d->step = -TILE;
		ray_d->offset = -1;
		ray_d->hit_x = (int)(d->player_x / TILE) * TILE;
	}
	else
	{
		ray_d->step = TILE;
		ray_d->offset = 1;
		ray_d->hit_x = ((int)(d->player_x / TILE) + 1) * TILE;
	}
	d_3d->door_v = 0;
}

double	shoot_vertical(t_data *d, double angle, t_view_3d *d_3d)
{
	t_raycaster	r_d;

	pre_ver_r(&r_d, angle, d, d_3d);
	while (1)
	{
		r_d.scaling_factor = (d->player_x - r_d.hit_x) / r_d.direction_x;
		r_d.hit_y = d->player_y + (r_d.scaling_factor * r_d.direction_y);
		if (r_d.hit_y < TILE || r_d.hit_y > ((d->height * TILE)))
			return (OUT_OF_RANGE);
		r_d.map_y = r_d.hit_y / TILE;
		r_d.map_x = (r_d.hit_x + r_d.offset) / TILE;
		if (strchr("1D", d->map[r_d.map_y][r_d.map_x]))
		{
			d_3d->ver_x = r_d.hit_x;
			d_3d->ver_y = r_d.hit_y;
			if (d->map[r_d.map_y][r_d.map_x] == 'D')
				d_3d->door_v = 1;
			return (sqrt((r_d.hit_x - d->player_x) * (r_d.hit_x - d->player_x)
					+ (r_d.hit_y - d->player_y) * (r_d.hit_y - d->player_y)));
		}
		r_d.hit_x += r_d.step;
		if (r_d.hit_x < 0 || r_d.hit_x > (d->width * TILE))
			return (OUT_OF_RANGE);
	}
	return (OUT_OF_RANGE);
}
