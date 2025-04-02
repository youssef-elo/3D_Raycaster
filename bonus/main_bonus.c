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
	int j;
	char str[30];
	int x;
	int y;
	int n;

	mlx_texture_t *tex;


	i = 1;
	j = 1;
	n = 3;
	// x = (WIDTH_3D  - data->mlx_data->gun[0]->width)  /2;
	// y = (HEIGHT_3D  - data->mlx_data->gun[0]->height) / 2 ;

	data->mlx_data->gun = malloc(sizeof(mlx_image_t *) * 74);
	for ( int i =0; i < 74; i++, j+=3)
	{
		if ( j > 9)
            n = 2;
        if (j > 99) 
            n = 1;
		sprintf(str, "render/%.*s%d.png",n , "000", j);
		tex = mlx_load_png(str);
		data->mlx_data->gun[i] = mlx_texture_to_image(data->mlx_data->mlx, tex);
		mlx_delete_texture(tex);
		mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->gun[i], 0, 0);
		data->mlx_data->gun[i]->instances->enabled = false;
	}
}

// void gun_animation(void *param)
// {
	
// }

void	gun_animation(void *param)
{
	static int i;
	static int first;
	static mlx_image_t *pre;


	// if (first == 0 && i < 74)
	// {
	// 	if (i != 0)
	// 		gun[i - 1]->instances[0].enabled = false;
	// 	pre = gun[i]; 
	// 	i++;
	// 	if ( i == 74)puts("out");
	// }
	// else
	// {
	// 	first = 1;
		if (i == 74)
			i = 0;
		// printf("%d\n", (i - 1) % 74);
		if (pre)
		pre->instances[0].enabled = false;
		((data_t *)param)->mlx_data->gun[i]->instances[0].enabled = true;
		pre = ((data_t *)param)->mlx_data->gun[i];
		i++;
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
