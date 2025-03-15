#include "cub3d.h"

void update_position(data_t *data, char c, int i, int j)
{
	if (c == 'N')
		data->view_angle = M_PI / 2;
	if (c == 'S')
		data->view_angle = 3 * (M_PI / 2);
	if (c == 'E')
		data->view_angle = 0;
	if (c == 'W')
		data->view_angle = M_PI;
	data->player_y = (i * TILE) + (TILE / 2);
	data->player_x = (j * TILE) + (TILE / 2);
}

void find_player(data_t *data)
{
	int i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
				update_position(data, data->map[i][j], i, j);
			j++;
		}
		i++;
	}
	data->width = j;
	data->height = i;
}

void link_parsing(data_t *d, map_context_h *p_data, mlx_data_t *mlx_data)
{
	d->map = p_data->map;
	d->ceiling = rgb(p_data->sky[0], p_data->sky[1], p_data->sky[2], 255);
	d->floor = rgb(p_data->floor[0], p_data->floor[1], p_data->floor[2], 255);
	d->mlx_data = mlx_data;
	find_player(d);
	d->mlx_data->mlx = mlx_init(WIDTH_3D, HEIGHT_3D, "Cub3d", false);
	d->mlx_data->view_3d = mlx_new_image(d->mlx_data->mlx, WIDTH_3D, HEIGHT_3D);
	d->mlx_data->south = mlx_texture_to_image(d->mlx_data->mlx,  mlx_load_png(p_data->south));
	d->mlx_data->east = mlx_texture_to_image(d->mlx_data->mlx,  mlx_load_png(p_data->east));
	d->mlx_data->west= mlx_texture_to_image(d->mlx_data->mlx,  mlx_load_png(p_data->west));
	d->mlx_data->north = mlx_texture_to_image(d->mlx_data->mlx,  mlx_load_png(p_data->north));
	d->dir_x = cos(d->view_angle);
	d->dir_y = sin(d->view_angle);
}

int	main(int argc, char **argv){
	data_t			data;
	mlx_data_t		mlx_data;
	map_context_h	p_data;

	parsing(argc , argv, &p_data);
	link_parsing(&data, &p_data, &mlx_data);
	draw_3d(&data);
	mlx_image_to_window(mlx_data.mlx, mlx_data.view_3d,  0, 0);
	mlx_loop_hook(mlx_data.mlx, hook_handler, &data);
	mlx_loop(mlx_data.mlx);
}
