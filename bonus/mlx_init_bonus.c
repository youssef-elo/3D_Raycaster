/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:57 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/14 16:05:56 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	parsing_end(t_data *data, char *str, t_map_context_h *p_data)
{
	free_parsing(p_data);
	end_game(data, str);
}

void	load_gun_images(t_data *d, mlx_texture_t *tmp, t_map_context_h *p_data)
{
	d->mlx_data->gun_view = mlx_new_image(d->mlx_data->mlx, GUN_W, GUN_H);
	if (!d->mlx_data->gun_view)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->fire_view = mlx_new_image(d->mlx_data->mlx, FIRE_W, FIRE_H);
	if (!d->mlx_data->fire_view)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->reload_view = mlx_new_image(d->mlx_data->mlx,
			RELOAD_W, RELOAD_H);
	if (!d->mlx_data->reload_view)
		parsing_end(d, "Error\nCant load images\n", p_data);
	tmp = mlx_load_png("b_assets/muzzle.png");
	if (!tmp)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->muzzle = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
	d->mlx_data->gun_sheet = mlx_load_png("b_assets/gunsheet.png");
	if (!d->mlx_data->gun_sheet)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->reload_sheet = mlx_load_png("b_assets/reloadsheet.png");
	if (!d->mlx_data->reload_sheet)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->fire_sheet = mlx_load_png("b_assets/firesheet.png");
	if (!d->mlx_data->fire_sheet)
		parsing_end(d, "Error\nCant load images\n", p_data);
}

void	load_game_images(t_data *d, t_map_context_h *p_data, mlx_texture_t *tmp)
{
	d->mlx_data->view_3d = mlx_new_image(d->mlx_data->mlx, WIDTH, HEIGHT);
	if (!d->mlx_data->view_3d)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->mini_map = mlx_new_image(d->mlx_data->mlx, M_WIDTH, M_HEIGHT);
	if (!d->mlx_data->mini_map)
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
}

void	load_game_images_2(t_data *d,
	t_map_context_h *p_data, mlx_texture_t *tmp)
{
	tmp = mlx_load_png("b_assets/door.png");
	if (!tmp)
		parsing_end(d, "Error\nCant load images\n", p_data);
	d->mlx_data->door = mlx_texture_to_image(d->mlx_data->mlx, tmp);
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
	load_game_images(d, p_data, NULL);
	load_game_images_2(d, p_data, NULL);
	load_gun_images(d, NULL, p_data);
	if (!d->mlx_data->view_3d || !d->mlx_data->door
		|| !d->mlx_data->gun_view || !d->mlx_data->muzzle
		|| !d->mlx_data->reload_view || !d->mlx_data->fire_view
		|| !d->mlx_data->mini_map || !d->mlx_data->north
		|| !d->mlx_data->south || !d->mlx_data->east
		|| !d->mlx_data->gun_sheet || !d->mlx_data->reload_sheet
		|| !d->mlx_data->fire_sheet || !d->mlx_data->west)
		parsing_end(d, "Error\nCant load images\n", p_data);
	mlx_resize_image(d->mlx_data->south, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->north, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->east, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->door, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->west, HEIGHT, HEIGHT);
}
