/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:05:20 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/17 12:34:48 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_images(t_data *d)
{
	draw_filled_disk(d->mlx_data->mini_map, d->mlx_data->mini_map->width / 2,
		d->mlx_data->mini_map->height / 2, 104);
	mlx_image_to_window(d->mlx_data->mlx, d->mlx_data->view_3d, 0, 0);
	mlx_image_to_window(d->mlx_data->mlx, d->mlx_data->mini_map,
		0, HEIGHT - d->mlx_data->mini_map->height);
	mlx_image_to_window(d->mlx_data->mlx, d->mlx_data->muzzle,
		(WIDTH / 2) - 110, HEIGHT - FIRE_H + 10);
	d->mlx_data->muzzle->instances->enabled = false;
	mlx_image_to_window(d->mlx_data->mlx, d->mlx_data->gun_view,
		(WIDTH / 2) - 350, HEIGHT - GUN_H);
	mlx_image_to_window(d->mlx_data->mlx, d->mlx_data->reload_view,
		(WIDTH / 2) - 600, HEIGHT - RELOAD_H);
	mlx_image_to_window(d->mlx_data->mlx, d->mlx_data->fire_view,
		(WIDTH / 2) - 350, HEIGHT - FIRE_H);
}
