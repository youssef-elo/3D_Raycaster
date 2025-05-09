/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:22 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/10 17:48:55 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	delete_textures(t_data *d)
{
	if (d->mlx_data->reload_sheet)
		mlx_delete_texture(d->mlx_data->reload_sheet);
	if (d->mlx_data->gun_sheet)
		mlx_delete_texture(d->mlx_data->gun_sheet);
	if (d->mlx_data->fire_sheet)
		mlx_delete_texture(d->mlx_data->fire_sheet);
}

void	delete_images(t_data *d)
{
	if (d->mlx_data->north)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->north);
	if (d->mlx_data->south)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->south);
	if (d->mlx_data->east)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->east);
	if (d->mlx_data->west)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->west);
	if (d->mlx_data->view_3d)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->view_3d);
	if (d->mlx_data->mini_map)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->mini_map);
	if (d->mlx_data->gun_view)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->gun_view);
	if (d->mlx_data->fire_view)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->fire_view);
	if (d->mlx_data->reload_view)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->reload_view);
	if (d->mlx_data->door)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->door);
	if (d->mlx_data->muzzle)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->muzzle);
	if (d->mlx_data->fps)
		mlx_delete_image(d->mlx_data->mlx, d->mlx_data->fps);
	delete_textures(d);
}

void	cross_close(void *param)
{
	end_game(param, "Cross clicked\n");
}

void	end_game(t_data *d, char *message)
{
	int	i;

	delete_images(d);
	if (d->cos)
		free(d->cos);
	i = 0;
	while (i < d->height)
		free(d->map[i++]);
	free(d->map);
	if (d->mlx_data->mlx)
		mlx_terminate(d->mlx_data->mlx);
	printf("%s", message);
	exit(0);
}

void	free_parsing(t_map_context_h *p_data)
{
	free(p_data->array);
	free(p_data->south);
	free(p_data->west);
	free(p_data->north);
	free(p_data->east);
	free(p_data->sky_s);
	free(p_data->floor_s);
}
