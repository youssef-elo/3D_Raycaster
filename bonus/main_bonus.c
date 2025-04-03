#include "cub3d_bonus.h"

void flashlight(struct mlx_key_data keydata, void *param)
{
	data_t *data;

	data = (data_t *)param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
	{
		if (data->fog_start == FOG_START)
		{
			data->fog_start = FOG_START_FLASH;
			data->fog_m = MAX_VIEW_FLASH;
		}
		else
		{
			data->fog_start = FOG_START;
			data->fog_m = MAX_VIEW;
		}
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		data->reload = 1;
	}
}

void load_gun(data_t *data)
{
	// int i;
	int j;
	char str[30];
	int x;
	int y;
	int n;

	mlx_texture_t *tex;


	// i = 1;
	j = 1;
	n = 3;
	data->walking = 1;
	data->mlx_data->gun = malloc(sizeof(mlx_image_t *) * 44);
	for ( int i = 0; i < 44; i++, j+=5)
	{
		if ( j > 9)
            n = 2;
        if (j > 99) 
            n = 1;
		sprintf(str, "render/%.*s%d.png",n , "000", j);
		tex = mlx_load_png(str);
		data->mlx_data->gun[i] = mlx_texture_to_image(data->mlx_data->mlx, tex);
		mlx_delete_texture(tex);
		if (i == 0)
		{
			x = (WIDTH_3D / 2) - 350;
			y = HEIGHT_3D  - data->mlx_data->gun[0]->height ;
		}
		mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->gun[i], x, y);
		data->mlx_data->gun[i]->instances->enabled = false;
	}
	gun_animation(data);
}
void load_gun_reload(data_t *data)
{
	// int i;
	int j;
	char str[30];
	int x;
	int y;
	int n;

	mlx_texture_t *tex;


	// i = 1;
	j = 1;
	n = 3;
	data->walking = 1;
	data->mlx_data->reload = malloc(sizeof(mlx_image_t *) * 44);
	for ( int i = 0; i < 44; i++, j+=5)
	{
		if ( j > 9)
            n = 2;
        if (j > 99) 
            n = 1;
		sprintf(str, "reload/%.*s%d.png",n , "000", j);
		tex = mlx_load_png(str);
		data->mlx_data->reload[i] = mlx_texture_to_image(data->mlx_data->mlx, tex);
		mlx_delete_texture(tex);
		if (i == 0)
		{
			x = (WIDTH_3D / 2) - 600;
			y = HEIGHT_3D  - data->mlx_data->reload[0]->height ;
		}
		mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->reload[i], x, y);
		data->mlx_data->reload[i]->instances->enabled = false;
	}
}

// void gun_animation(void *param)
// {
	
// }

void	gun_animation(void *param)
{
	static int i;
	static int first;
	static mlx_image_t *pre_gun;
	static int r;
	static double last_time;
	double current_time;

	data_t *data;
	data = (data_t *)param;
	if (!first)
	{
		last_time = mlx_get_time();
		first = 1;
	}
	current_time = mlx_get_time();
	
	// printf("%d\n", data->walking);
	if (current_time - last_time >= 0.02f)
	{
		if (data->walking && !data->reload)
		{
			if (i == 44)
				i = 0;
			if (pre_gun)
				pre_gun->instances[0].enabled = false;
			((data_t *)param)->mlx_data->gun[i]->instances[0].enabled = true;
			pre_gun = ((data_t *)param)->mlx_data->gun[i];
			i++;
		}
		if (data->reload)
		{
			pre_gun->instances[0].enabled = false;
			if (r != 0)
				data->mlx_data->reload[r - 1]->instances[0].enabled = false;
			data->mlx_data->reload[r]->instances[0].enabled = true;
			r++;
			if (r == 44)
			{
				data->reload = 0;
				data->mlx_data->reload[r - 1]->instances[0].enabled = false;
				r = 0;
				pre_gun->instances[0].enabled = true;
				i = 0;
			}
		}
		last_time = mlx_get_time();
	}
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
	draw_filled_disk(data.mlx_data->mini_map, data.mlx_data->mini_map->width / 2, data.mlx_data->mini_map->height / 2, 104);
	// draw_3d(&data);
	mlx_image_to_window(mlx_data.mlx, mlx_data.view_3d,  0, 0);
	mlx_image_to_window(mlx_data.mlx, mlx_data.mini_map,  0, HEIGHT_3D - data.mlx_data->mini_map->height);
	minimap_3d(&data);
	load_gun(&data);
	load_gun_reload(&data);
	mlx_key_hook(data.mlx_data->mlx, flashlight, &data);
	mlx_loop_hook(mlx_data.mlx, hook_handler, &data);
	mlx_loop_hook(mlx_data.mlx, draw_3d, &data);
	mlx_loop_hook(mlx_data.mlx, gun_animation, &data);
	mlx_loop(mlx_data.mlx);
}
