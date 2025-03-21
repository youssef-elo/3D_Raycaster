#include "cub3d.h"


void load_images(data_t *d, map_context_h *p_data)
{
	mlx_texture_t *tmp;

	d->mlx_data->view_3d = mlx_new_image(d->mlx_data->mlx, WIDTH_3D, HEIGHT_3D);
	if (!d->mlx_data->view_3d)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->mini_map = mlx_new_image(d->mlx_data->mlx, 6 * TILE_SIZE, 6 * TILE_SIZE);
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
	d->mlx_data->west= mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
	tmp = mlx_load_png(p_data->north);
	if (!tmp)
		end_game(d, "Error\nCant load images\n");
	d->mlx_data->north = mlx_texture_to_image(d->mlx_data->mlx, tmp);
	mlx_delete_texture(tmp);
}

void start_mlx(data_t *d, map_context_h *p_data)
{

	d->mlx_data->mlx = mlx_init(WIDTH_3D, HEIGHT_3D, "Cub3d", false);
	if (!d->mlx_data->mlx)
		end_game(d, "Error\nCant establish connection with the mlx library\n");
	load_images(d, p_data);
	mlx_resize_image(d->mlx_data->south, HEIGHT_3D, HEIGHT_3D);
	mlx_resize_image(d->mlx_data->north, HEIGHT_3D, HEIGHT_3D);
	mlx_resize_image(d->mlx_data->east, HEIGHT_3D, HEIGHT_3D);
	mlx_resize_image(d->mlx_data->west, HEIGHT_3D, HEIGHT_3D);
}
