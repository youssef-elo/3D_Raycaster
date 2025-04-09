/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:22:38 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/09 15:11:22 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_images(t_data *d, t_map_context_h *p_data)
{
	mlx_texture_t	*tmp;

	d->mlx_data->view_3d = mlx_new_image(d->mlx_data->mlx, WIDTH, HEIGHT);
	if (!d->mlx_data->view_3d)
		end_game(d, "Error\nCant load images\n");
	tmp = mlx_load_png(p_data->south);
	if (!tmp)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->south = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
	tmp = mlx_load_png(p_data->east);
	if (!tmp)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->east = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
	tmp = mlx_load_png(p_data->west);
	if (!tmp)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->west = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
	tmp = mlx_load_png(p_data->north);
	if (!tmp)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->north = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
}

void	start_mlx(t_data *d, t_map_context_h *p_data)
{
	d->mlx_data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", false);
	if (!d->mlx_data->mlx)
		end_game(d, "Error\nCant establish connection with the mlx library\n");
	load_images(d, p_data);
	if (!d->mlx_data->south || !d->mlx_data->north
	|| !d->mlx_data->east || !d->mlx_data->west)
		end_game(d, "Error\nCant load images\n");
	mlx_resize_image(d->mlx_data->south, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->north, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->east, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->west, HEIGHT, HEIGHT);
}
