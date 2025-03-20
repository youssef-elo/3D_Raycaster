#include "cub3d.h"

void update_position(data_t *data, char c, int i, int j)
{
	if (c == 'N')
		data->p_angle = M_PI / 2;
	if (c == 'S')
		data->p_angle = 3 * (M_PI / 2);
	if (c == 'E')
		data->p_angle = 0;
	if (c == 'W')
		data->p_angle = M_PI;
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
			{
				update_position(data, data->map[i][j], i, j);
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	data->width = j;
	data->height = i;
}

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
	printf("%s", message);
	exit(0);
}

void load_images(data_t *d, map_context_h *p_data)
{
	mlx_texture_t *tmp;

	d->mlx_data->view_3d = mlx_new_image(d->mlx_data->mlx, WIDTH_3D, HEIGHT_3D);
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
void link_parsing(data_t *d, map_context_h *p_data, mlx_data_t *mlx_data)
{
	d->map = p_data->map;
	d->mlx_data = mlx_data;
	start_mlx(d, p_data);
	d->ceiling = rgb(p_data->sky[0], p_data->sky[1], p_data->sky[2], 255);
	d->floor = rgb(p_data->floor[0], p_data->floor[1], p_data->floor[2], 255);
	find_player(d);
	d->map_x = d->player_x / TILE;
	d->map_y = d->player_y / TILE;
	d->dir_x = cos(d->p_angle);
	d->dir_y = sin(d->p_angle);
	d->offset.n_offset = d->mlx_data->north->width / TILE;
	d->offset.s_offset = d->mlx_data->south->width / TILE;
	d->offset.e_offset = d->mlx_data->east->width / TILE;
	d->offset.w_offset = d->mlx_data->west->width / TILE;
}


void pre_compute(data_t *data)
{
	int i;
	double r_angle;
	double fov_half;
	double angle_i;

	i = 0;
	data->consts.angle_i = FOV / NUMBER_OF_RAYS;
	data->consts.p = (WIDTH_3D / 2) / tan(FOV / 2);
	data->consts.scaler = data->consts.p * TILE;
	data->consts.fov_half = FOV / 2;
	data->consts.half_window = HEIGHT_3D / 2;
	data->cos = malloc( sizeof(double) * NUMBER_OF_RAYS);
	while(i < NUMBER_OF_RAYS)
	{
		r_angle = (data->p_angle - data->consts.fov_half) + (i * data->consts.angle_i);
		data->cos[i] = cos(r_angle - data->p_angle);
		i++;
	}
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

int	main(int argc, char **argv){
	data_t			data;
	mlx_data_t		mlx_data;
	map_context_h	p_data;

	parsing(argc , argv, &p_data);
	ft_bzero(&data, sizeof(data_t));
	link_parsing(&data, &p_data, &mlx_data);
	pre_compute(&data);
	free_parsing(&p_data);
	printf("%f\n", data.player_y);
	draw_3d(&data);
	mlx_image_to_window(mlx_data.mlx, mlx_data.view_3d,  0, 0);
	mlx_loop_hook(mlx_data.mlx, hook_handler, &data);
	mlx_loop_hook(mlx_data.mlx, draw_3d, &data);
	mlx_loop(mlx_data.mlx);
}
