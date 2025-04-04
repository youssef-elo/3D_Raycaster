#include "cub3d_bonus.h"

void end_game(data_t *d, char *message)
{
	int i;

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
	free(d->cos);
	i = 0;
	while(i < d->height)
		free(d->map[i++]);
	free(d->map);
	if (d->mlx_data->reload_sheet)
	mlx_delete_texture(d->mlx_data->reload_sheet);
	if (d->mlx_data->gun_sheet)
	mlx_delete_texture(d->mlx_data->gun_sheet);
	if (d->mlx_data->fire_sheet)
	mlx_delete_texture(d->mlx_data->fire_sheet);
	if (d->mlx_data->gun_view)
	mlx_delete_image(d->mlx_data->mlx, d->mlx_data->gun_view);
	if (d->mlx_data->fire_view)
	mlx_delete_image(d->mlx_data->mlx, d->mlx_data->fire_view);
	if (d->mlx_data->fire_view)
	mlx_delete_image(d->mlx_data->mlx, d->mlx_data->fire_view);
	printf("%s", message);
	exit(0);
}

void free_parsing(map_context_h *p_data)
{
	free(p_data->array);
	free(p_data->south);
	free(p_data->west);
	free(p_data->north);
	free(p_data->east);
	free(p_data->sky_s);
	free(p_data->floor_s);
}