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

int	main(int argc, char **argv){
	data_t			data;
	mlx_data_t		mlx_data;
	map_context_h	p_data;

	parsing(argc , argv, &p_data);
	ft_bzero(&data, sizeof(data_t));
	link_parsing(&data, &p_data, &mlx_data);
	pre_compute(&data);
	free_parsing(&p_data);
	draw_3d(&data);
	mlx_image_to_window(mlx_data.mlx, mlx_data.view_3d,  0, 0);
	mlx_image_to_window(mlx_data.mlx, mlx_data.mini_map,  0, HEIGHT_3D - data.mlx_data->mini_map->height);
	minimap_3d(&data);
	mlx_key_hook(data.mlx_data->mlx, flashlight, &data);
	mlx_loop_hook(mlx_data.mlx, hook_handler, &data);
	mlx_loop_hook(mlx_data.mlx, draw_3d, &data);
	mlx_loop(mlx_data.mlx);
}
