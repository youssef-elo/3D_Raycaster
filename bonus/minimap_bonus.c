#include "cub3d_bonus.h"

void ft_draw_map( data_t *data)
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
    mini_map.player_x = (int)((data->player_x  / 32));
    mini_map.player_y = (int)((data->player_y  / 32));
    x = mini_map.player_x  - (int)(MINI_WIDTH / 2);
    y = mini_map.player_y  - (int)(MINI_WIDTH / 2);
    // memset(data->mlx_data->mini_map->pixels, 0, ( data->mlx_data->mini_map->height * data->mlx_data->mini_map->width * BPP));
	center_x = data->mlx_data->mini_map->width / 2;
	center_y =  data->mlx_data->mini_map->height / 2;
    for (int i = 0; i < MINI_HEIGHT; i++)
    {
        for (int j = 0; j < MINI_WIDTH; j++)
        {
			dx = center_x - j;
			dy = center_y - i;
			if (((dx*dx) + (dy * dy)) <= 120*120)
			{
				if(x < 0 || y < 0 || (x / TILE_SIZE) > data->width - 1 || (y / TILE_SIZE) > (data->height - 1) )
					put_pixel(data->mlx_data->mini_map, i, j, rgb(108,108,108, 255));
					// put_pixel(data->mlx_data->mini_map, i, j, rgb(203,144,77,255));
				else if (data->map[y / TILE_SIZE][x / TILE_SIZE] == '1' || data->map[y / TILE_SIZE][x / TILE_SIZE] == ' ')
					put_pixel(data->mlx_data->mini_map, i, j, rgb(108,108,108, 255));
					// put_pixel(data->mlx_data->mini_map, i, j, rgb(203,144,77,255));
				else if (data->map[y / TILE_SIZE][x / TILE_SIZE] == '0')
					put_pixel(data->mlx_data->mini_map, i, j, rgb(211,211,211, 255));
					// put_pixel(data->mlx_data->mini_map, i, j, rgb(243, 249,210,255));
			}
            x++;
			// dx++;
        }
        x = mini_map.player_x  - (int)(MINI_WIDTH / 2);
        y++;
		// dy++;
    }
    draw_filled_disk(data->mlx_data->mini_map, MINI_WIDTH / 2, MINI_HEIGHT / 2, 7);
}
