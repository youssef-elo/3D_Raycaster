/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:57 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/08 21:27:22 by hchadili         ###   ########.fr       */
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
		(WIDTH / 2) - 120, HEIGHT - FIRE_H);
	d->mlx_data->muzzle->instances->enabled = false;
	mlx_image_to_window(d->mlx_data->mlx, d->mlx_data->gun_view,
		(WIDTH / 2) - 350, HEIGHT - GUN_H);
	mlx_image_to_window(d->mlx_data->mlx, d->mlx_data->reload_view,
		(WIDTH / 2) - 600, HEIGHT - RELOAD_H);
	mlx_image_to_window(d->mlx_data->mlx, d->mlx_data->fire_view,
		(WIDTH / 2) - 350, HEIGHT - FIRE_H);
}

void	load_gun_images(t_data *d, mlx_texture_t *tmp)
{
	d->mlx_data->gun_view = mlx_new_image(d->mlx_data->mlx, GUN_W, GUN_H);
	if (!d->mlx_data->gun_view)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->fire_view = mlx_new_image(d->mlx_data->mlx, FIRE_W, FIRE_H);
	if (!d->mlx_data->fire_view)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->reload_view = mlx_new_image(d->mlx_data->mlx,
			RELOAD_W, RELOAD_H);
	if (!d->mlx_data->reload_view)
		end_game(d, "Error\nCant load images\n");
	tmp = mlx_load_png("b_assets/muzzle.png");
	if (!tmp)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->muzzle = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
	d->mlx_data->gun_sheet = mlx_load_png("b_assets/gunsheet.png");
	if (!d->mlx_data->gun_sheet)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->reload_sheet = mlx_load_png("b_assets/reloadsheet.png");
	if (!d->mlx_data->reload_sheet)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->fire_sheet = mlx_load_png("b_assets/firesheet.png");
	if (!d->mlx_data->fire_sheet)
		end_game(d, "Error\nCant load images\n");
}

void	load_game_images(t_data *d, t_map_context_h *p_data, mlx_texture_t *tmp)
{
	d->mlx_data->view_3d = mlx_new_image(d->mlx_data->mlx, WIDTH, HEIGHT);
	if (!d->mlx_data->view_3d)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->mini_map = mlx_new_image(d->mlx_data->mlx, M_WIDTH, M_HEIGHT);
	if (!d->mlx_data->mini_map)
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
}

void	load_game_images_2(t_data *d,
	t_map_context_h *p_data, mlx_texture_t *tmp)
{
	tmp = mlx_load_png("b_assets/door.png");
	if (!tmp)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->door = mlx_texture_to_image(d->mlx_data->mlx, tmp);
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
	load_game_images(d, p_data, NULL);
	load_game_images_2(d, p_data, NULL);
	load_gun_images(d, NULL);
	if (!d->mlx_data->view_3d || !d->mlx_data->door
		|| !d->mlx_data->gun_view || !d->mlx_data->muzzle
		|| !d->mlx_data->reload_view || !d->mlx_data->fire_view
		|| !d->mlx_data->mini_map || !d->mlx_data->north
		|| !d->mlx_data->south || !d->mlx_data->east
		|| !d->mlx_data->gun_sheet || !d->mlx_data->reload_sheet
		|| !d->mlx_data->fire_sheet || !d->mlx_data->west)
		end_game(d, "Error\nCant load images\n");
	mlx_resize_image(d->mlx_data->south, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->north, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->east, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->door, HEIGHT, HEIGHT);
	mlx_resize_image(d->mlx_data->west, HEIGHT, HEIGHT);
}
