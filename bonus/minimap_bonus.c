#include "cub3d_bonus.h"

void	minimap_3d(data_t *data)
{
	int i;
	int j;
	int dx;
	int dy;
	int rx;
	int ry;
	int map_x;
	int map_y;
	int center_x;
	int center_y;
	static double pre_angle;
	double angle_new;
	matrix_t matrix;

	angle_new = (data->p_angle - (M_PI_2));
	if (angle_new < 0)
			angle_new += (2 * M_PI);
	i = 0;
	j = 0;
	matrix.x1 = cos(-(angle_new));
	matrix.y1 = sin(-(angle_new));
	matrix.x2 = -matrix.y1;
	matrix.y2 = matrix.x1;
	center_x = MINI_WIDTH / 2;
	center_y = MINI_HEIGHT / 2;
	while(i < MINI_HEIGHT)
	{
		j = 0;
		while(j < MINI_WIDTH)
		{
			dy = i - center_y;
			dx = j - center_x;
			if (((dx *dx) + (dy * dy)) <= (100*100))
			{
				rx = (dx * matrix.x1) + (dy * matrix.x2);
				ry = (dx * matrix.y1) + (dy * matrix.y2);
				map_x = (data->player_x + (rx * 48)) / TILE;
				map_y = (data->player_y + (ry * 48)) / TILE;
				if(map_x < 0 || map_y < 0 || map_x > data->width - 1 || map_y > (data->height - 1) )
					put_pixel(data->mlx_data->mini_map, j, i, rgb(108,108,108, 255));
				else if (data->map[map_y][map_x] == '1' || data->map[map_y][map_x] == ' ')
					put_pixel(data->mlx_data->mini_map, j, i, rgb(108,108,108, 255));
				else if (data->map[map_y][map_x] == '0')
					put_pixel(data->mlx_data->mini_map, j, i, rgb(211,211,211, 255));
			}
			j++;
		}
		i++;
	}
    draw_filled_disk(data->mlx_data->mini_map, MINI_WIDTH / 2, MINI_HEIGHT / 2, 7);

}

// void minimap_3d( data_t *data)
// {
//     int x;
// 	mini_map_h mini_map;
//     int y;
//     int size_map_row;
//     int size_map_col;
// 	int center_x;
// 	int center_y;
// 	double r_x;
// 	double r_y;
// 	double dx; 
// 	double dy;
// 	int i;
// 	int j;
// 	static int a;

// 	i = 0;
// 	matrix_t matrix;


// 	double angle_new = (data->p_angle - (M_PI_2));
// 	if (angle_new < 0)
// 			angle_new += (2 * M_PI);
// 	matrix.x1 = cos((angle_new));
// 	matrix.y1 = sin((angle_new));

// 	matrix.x2 = -matrix.y1;
// 	matrix.y2 = matrix.x1;
// 	memset(data->mlx_data->mini_map->pixels, 0, ( data->mlx_data->mini_map->height * data->mlx_data->mini_map->width * BPP));
// 	// printf("x1 %f  x2 %f\ny1 %f  y2 %f\n\n", matrix.x1, matrix.x2, matrix.y1, matrix.y2);
//     mini_map.player_x = (int)((data->player_x / 32));
//     mini_map.player_y = (int)((data->player_y / 32));

//     x = mini_map.player_x - (int)(MINI_WIDTH / 2);
//     y = mini_map.player_y - (int)(MINI_WIDTH / 2);
	
// 	center_x = data->mlx_data->mini_map->width / 2;
// 	center_y = data->mlx_data->mini_map->height / 2;
//     while (i < MINI_HEIGHT)
//     {
// 		j = 0;
//         while (j < MINI_WIDTH)
//         {
// 			dx = j - center_x;
// 			dy = i - center_y;
// 			if (((dx*dx) + (dy*dy)) <= 2000*2000)
// 			{
// 				r_x = ((dx * matrix.x1) + (dy * matrix.x2));
// 				r_y = ((dx * matrix.y1) + (dy * matrix.y2));
// 				if(x < 0 || y < 0 || (x / TILE_SIZE) > data->width - 1 || (y / TILE_SIZE) > (data->height - 1) )
// 					put_pixel(data->mlx_data->mini_map, (r_x) + center_x, (r_y) + center_y, rgb(108,108,108, 255));
// 				else if (data->map[y / TILE_SIZE][x / TILE_SIZE] == '1' || data->map[y / TILE_SIZE][x / TILE_SIZE] == ' ')
// 					put_pixel(data->mlx_data->mini_map, (r_x) + center_x, (r_y) + center_y, rgb(108,108,108, 255));
// 				else if (data->map[y / TILE_SIZE][x / TILE_SIZE] == '0')
// 					put_pixel(data->mlx_data->mini_map, (r_x) + center_x, (r_y) + center_y, rgb(211,211,211, 255));
// 				// printf("%d % d\n", (int)r_x + center_x, (int)r_y + center_y);
// 			}
//             x++;
// 			j++;
//         }
//         x = mini_map.player_x - (int)(MINI_WIDTH / 2);
//         y++;
// 		i++;
//     }
//     draw_filled_disk(data->mlx_data->mini_map, MINI_WIDTH / 2, MINI_HEIGHT / 2, 7);
// }
