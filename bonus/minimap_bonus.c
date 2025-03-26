#include "cub3d_bonus.h"

void minimap_3d( data_t *data)
{
    int x;
	mini_map_h mini_map;
    int y;
    int size_map_row;
    int size_map_col;
	int center_x;
	int center_y;
	int dx; 
	int dy;
	static int a;
	int i;
	int j;

	i = 0;
	matrix_t matrix;

	matrix.x1 = cos(-data->p_angle );
	matrix.y1 = sin(-data->p_angle );

	matrix.x2 = -matrix.y1;
	matrix.y2 = matrix.x1;

    mini_map.player_x = (int)((data->player_x  / 32));
    mini_map.player_y = (int)((data->player_y  / 32));
    x = mini_map.player_x  - (int)(MINI_WIDTH / 2);
    y = mini_map.player_y  - (int)(MINI_WIDTH / 2);
	int r_x;
	int r_y;
    // memset(data->mlx_data->mini_map->pixels, 0, ( data->mlx_data->mini_map->height * data->mlx_data->mini_map->width * BPP));
	center_x = data->mlx_data->mini_map->width / 2;
	center_y =  data->mlx_data->mini_map->height / 2;
    while (i < MINI_HEIGHT)
    {
		j = 0;
        while (j < MINI_WIDTH)
        {
			dx = j - center_x;
			dy = i - center_y;
			if (((dx*dx) + (dy * dy)) <= 120*120)
			{
				r_x = ((dx * matrix.x1) + (dy * matrix.x2));
				r_y = ((dx * matrix.y2) + (dy * matrix.y2));
				if(x < 0 || y < 0 || (x / TILE_SIZE) > data->width - 1 || (y / TILE_SIZE) > (data->height - 1) )
					put_pixel(data->mlx_data->mini_map, r_x + center_x, r_y + center_y, rgb(108,108,108, 255));
				else if (data->map[y / TILE_SIZE][x / TILE_SIZE] == '1' || data->map[y / TILE_SIZE][x / TILE_SIZE] == ' ')
					put_pixel(data->mlx_data->mini_map, r_x + center_x, r_y + center_y, rgb(108,108,108, 255));
				else if (data->map[y / TILE_SIZE][x / TILE_SIZE] == '0')
					put_pixel(data->mlx_data->mini_map, r_x + center_x, r_y + center_y, rgb(211,211,211, 255));
			}
            x++;
			j++;
			// dx++;
        }
        x = mini_map.player_x  - (int)(MINI_WIDTH / 2);
        y++;
		i++;
		// dy++;
    }
    draw_filled_disk(data->mlx_data->mini_map, MINI_WIDTH / 2, MINI_HEIGHT / 2, 7);
}
