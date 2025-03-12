#include "cub3d.h"


int main(int argc, char **argv){
	// parsing(argc , argv);
	data_t data;

	mlx_data_t mlx_data;
	data.mlx_data = &mlx_data;
	data.rays = malloc(sizeof(int) * NUMBER_OF_RAYS);
	bzero(data.rays, sizeof(int) * NUMBER_OF_RAYS);
	data.floor = rgb(0, 0, 0, 255);
	data.ceiling = rgb(0, 0, 0, 255);

	data.map = (char*[]){
"11111111111111111111111  ",
"      100100100100001001 ",
"111111101001001001001    ",
"100100100100100100001 11 ",
"100100100000100100000101 ",
"1000000P00P0000000000001 ",
"100001111111100000001111 ",
"111100000000000111001    ",
"100000010101000000111    ",
"1111111111111111111      "};
	// {
						// "1111111111111111111111111111111",
						// "1000000000001001000000000000001",
						// "1000000000001001000000000000001",
						// "10P0101000000000101000000000001",
						// "10000000000P0000000000000000001",
						// "1000101000000000101000000000001",
						// "1000000000000000000000000000001",
						// "1000000000000010010000000000001",
						// "1000000000000010010000000000001",
						// "1000001000000000000000000000001",
						// "1000000000000000000000000000001",
						// "1000001000000000000000000000001",
						// "1000000000000000000000000000001",
						// "1111111111111111111111111111111"};

	data.width = 0;
	data.height =  10;
	for ( int i =0; data.map[0][i];i++, data.width++);
	int found = 0;
	for ( int i = 0;  ; i++)
	{
		for(int j =  0; data.map[i][j]; j++)
		{
			if (data.map[i][j] == 'P')
			{
				data.player_y = (i * TILE) + (TILE / 2);
				data.player_x = (j * TILE) + (TILE / 2);
				found = 1;
			}
		}
			if (found == 1)
				break;
	}
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

	data.mlx_data->south = mlx_texture_to_image(data.mlx_data->mlx, mlx_load_png("./assets/south.png"));
	data.mlx_data->east = mlx_texture_to_image(data.mlx_data->mlx, mlx_load_png("./assets/east.png"));
	data.mlx_data->west= mlx_texture_to_image(data.mlx_data->mlx, mlx_load_png("./assets/west.png"));
	data.mlx_data->north = mlx_texture_to_image(data.mlx_data->mlx, mlx_load_png("./assets/north.png"));

	// mlx_resize_image(data.mlx_data->south, data.mlx_data->south->width, HEIGHT`

	// mlx_image_to_window(data.mlx_data->mlx, data.mlx_data->south,0, 0);
	data.view_angle = M_PI / 2;

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