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
}

void load_gun(data_t *data)
{
	int i;
	int j = 0;
	mlx_texture_t *tex;


	i = 1;
	j = 0;
	char str[30];
	while(i <= 21)
	{
		sprintf(str, "render/00%d.png", i);
		// printf("%s\n", str);
		tex = mlx_load_png(str);
		data->mlx_data->gun[j] = mlx_texture_to_image(data->mlx_data->mlx, tex);
		i == 0 ? printf("%p\n", data->mlx_data->gun[j]):0;
		mlx_delete_texture(tex);
		i += 2;
		j++;
	}
}

// void gun_animation(void *param)
// {
	
// }

void	gun_animation(void *param)
{
	static double accum = 0.0;
	static int current_frame = -1;
	data_t *data;
	static int last;

	data = (data_t *)param;

	mlx_t *mlx = ((mlx_t *)param);
	double dt = mlx_get_time() - accum; 

	if (dt > 0.1)
	{
		current_frame = (current_frame + 1) % 11;
printf("%d\n", current_frame);
		// Remove previous frame from render queue
		// if (last != -1)
		// 	data->mlx_data->gun[(current_frame - 1) % 11]->instances[last].enabled = false;

		// Draw new frame
		last = mlx_image_to_window(mlx, data->mlx_data->gun[current_frame], 0, 0);
		accum = mlx_get_time();
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
	draw_3d(&data);
	mlx_image_to_window(mlx_data.mlx, mlx_data.view_3d,  0, 0);
	mlx_image_to_window(mlx_data.mlx, mlx_data.mini_map,  0, HEIGHT_3D - data.mlx_data->mini_map->height);
	minimap_3d(&data);
	load_gun(&data);
	mlx_key_hook(data.mlx_data->mlx, flashlight, &data);
	mlx_loop_hook(mlx_data.mlx, hook_handler, &data);
	mlx_loop_hook(mlx_data.mlx, draw_3d, &data);
	mlx_loop_hook(mlx_data.mlx, gun_animation, &data);
	mlx_loop(mlx_data.mlx);
}
