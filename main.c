#include "cub3d.h"


void find_player(data_t *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (1)
	{
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N')
			{
				data->view_angle = M_PI / 2;
				data->player_y = (i * TILE) + (TILE / 2);
				data->player_x = (j * TILE) + (TILE / 2);
				return ;
			}
			if (data->map[i][j] == 'S')
			{
				data->view_angle = 3 * (M_PI / 2);
				data->player_y = (i * TILE) + (TILE / 2);
				data->player_x = (j * TILE) + (TILE / 2);
				return ;
			}
			if (data->map[i][j] == 'E')
			{
				data->view_angle = 0;
				data->player_y = (i * TILE) + (TILE / 2);
				data->player_x = (j * TILE) + (TILE / 2);
				return ;
			}
			if (data->map[i][j] == 'W')
			{
				data->view_angle = M_PI;
				data->player_y = (i * TILE) + (TILE / 2);
				data->player_x = (j * TILE) + (TILE / 2);
				return ;
			}
			j++;
		}
		i++;
	}
}

int main(int argc, char **argv){
	data_t data;
	map_context_h p_data;

	parsing(argc , argv, &p_data);
	data.map = p_data.map;
	data.ceiling = rgb(p_data.sky[0], p_data.sky[1], p_data.sky[2], 255);
	data.floor = rgb(p_data.floor[0], p_data.floor[1], p_data.floor[2], 255);




	mlx_data_t mlx_data;
	data.mlx_data = &mlx_data;
// 	data.map = (char*[]){
// "1111111111111111111111111",
// "1000001001000000100100001",
// "1000001001000000100100001",
// "1000001001000000100100001",
// "1000001001111110100100001",
// "1000001000000000100100001",
// "1000001000000000100100001",
// "1111111111110000111111111",
// "1000000000000000000000001",
// "1000000000000000000000001",
// "1000000000P00000000100001",
// "1000000000000000000000001",
// "1000000000000000000000001",
// "1111111111110000111111111",
// "1000001000000000100100001",
// "1000001000000000100100001",
// "1000001001111110100100001",
// "1000001001000000100100001",
// "1000001001000000100100001",
// "1000001001000000100100001",
// "1111111111111111111111111",
// "1000000000100010000000001",
// "1000000000100010000000001",
// "1000000000100010000000001",
// "1111111111111111111111111"};

// "11111111111111111111111  ",
// "      100100100100001001 ",
// "111111101001001001001    ",
// "100100100100100100001 11 ",
// "100100100000100100000101 ",
// "1000000P00P0000000000001 ",
// "100001111111100000001111 ",
// "111100000000000111001    ",
// "100000010101000000111    ",
// "1111111111111111111      "};

	// data.width = 0;
	// data.height =  25;
	
	if (!CUBE3D)
	{
		mlx_data.mlx = mlx_init(data.width * TILE, data.height * TILE, "Minimap", false);
		mlx_data.view = mlx_new_image(mlx_data.mlx, data.width * TILE, data.height * TILE);
		mlx_data.rays_image = mlx_new_image(mlx_data.mlx, data.width * TILE, data.height * TILE);
	}
	else 
	{
		mlx_data.mlx = mlx_init(WIDTH_3D, HEIGHT_3D, "Cub3d", false);
		mlx_data.view_3d = mlx_new_image(mlx_data.mlx, WIDTH_3D, HEIGHT_3D);
		// mlx_data.floor_ceiling = mlx_new_image(mlx_data.mlx, WIDTH_3D, HEIGHT_3D);
		// floor_ceiling(&data);
	}

	data.mlx_data->south = mlx_texture_to_image(data.mlx_data->mlx, mlx_load_png(p_data.south));
	data.mlx_data->east = mlx_texture_to_image(data.mlx_data->mlx, mlx_load_png(p_data.east));
	data.mlx_data->west= mlx_texture_to_image(data.mlx_data->mlx, mlx_load_png(p_data.west));
	data.mlx_data->north = mlx_texture_to_image(data.mlx_data->mlx, mlx_load_png(p_data.north));

	// mlx_resize_image(data.mlx_data->south, data.mlx_data->south->width, HEIGHT`

	// mlx_image_to_window(data.mlx_data->mlx, data.mlx_data->south,0, 0);

	// important
	data.dir_x = cos(data.view_angle);
	data.dir_y = sin(data.view_angle);
	
	
	// printf("%lf\n", data.view_angle);
	// printf("%lf %lf\n", data.player_x, data.player_y);
	if (!CUBE3D)
	{
		draw_minimap(&data);
		mlx_image_to_window(mlx_data.mlx, mlx_data.view, 0 ,  0);
		minimap(&data, &mlx_data);
		mlx_image_to_window(mlx_data.mlx, mlx_data.rays_image, 0 , 0);
	}
	else{
		draw_3d(&data);
		mlx_image_to_window(mlx_data.mlx, mlx_data.view_3d,  0, 0);
	}
	mlx_loop_hook(mlx_data.mlx, hook_handler, &data);
	mlx_loop(mlx_data.mlx);
}