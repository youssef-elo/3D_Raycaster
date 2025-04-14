/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:22:38 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/13 16:01:48 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing_end(t_data *data, char *str, t_map_context_h *p_data)
{
	free_parsing(p_data);
	end_game(data, str);
}

void	load_images(t_data *d, t_map_context_h *p_data)
{
	mlx_texture_t	*tmp;

	d->mlx_data->view_3d = mlx_new_image(d->mlx_data->mlx, WIDTH, HEIGHT);
	if (!d->mlx_data->view_3d)
		parsing_end(d, "Error\nCant load images\n", p_data);
	tmp = mlx_load_png(p_data->south);
	if (!tmp)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->south = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
	tmp = mlx_load_png(p_data->east);
	if (!tmp)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->east = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
	tmp = mlx_load_png(p_data->west);
	if (!tmp)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->west = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
	tmp = mlx_load_png(p_data->north);
	if (!tmp)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->north = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
}

void	start_mlx(t_data *d, t_map_context_h *p_data)
{
	d->mlx_data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", false);
	if (!d->mlx_data->mlx)
		parsing_end(d, "Error\nMLX init fail\n", p_data);
	load_images(d, p_data);
	if (!d->mlx_data->south || !d->mlx_data->north
		|| !d->mlx_data->east || !d->mlx_data->west)
		parsing_end(d, "Error\nCant load images\n", p_data);
	mlx_resize_image(d->mlx_data->south, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->north, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->east, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->west, HEIGHT, HEIGHT);
}
