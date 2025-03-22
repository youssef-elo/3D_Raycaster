#include "cub3d_bonus.h"

void ft_draw_map( data_t *data)
{
    int x;
	mini_map_h mini_map;
    int y;
    int size_map_row;
    int size_map_col;

    mini_map.player_x = (int)((data->player_x  / 32));
    mini_map.player_y = (int)((data->player_y  / 32));
    x = mini_map.player_x  - (int)(3 * (double)TILE_SIZE);
    y = mini_map.player_y  - (int)(3 * (double)TILE_SIZE);
    memset(data->mlx_data->mini_map->pixels, 0, ( data->mlx_data->mini_map->height * data->mlx_data->mini_map->width * BPP));
    for (int i = 0; i < 6 * TILE_SIZE; i++)
    {
        for (int j = 0; j < 6 * TILE_SIZE; j++)
        {
            if(x < 0 || y < 0 || (x / TILE_SIZE) > data->width - 1 || (y / TILE_SIZE) > (data->height - 1 ) )
                put_pixel(data->mlx_data->mini_map, i, j, rgb(0,0,0,255));
            else if (data->map[y / TILE_SIZE][x / TILE_SIZE] == '1' || data->map[y / TILE_SIZE][x / TILE_SIZE] == ' ')
                put_pixel(data->mlx_data->mini_map, i, j, rgb(0,0,0,255));
            else if (data->map[y / TILE_SIZE][x / TILE_SIZE] == '0')
                put_pixel(data->mlx_data->mini_map, i, j, rgb(255, 255,255,255));
            x++;
        }
        x = mini_map.player_x  - (int)(3 * (double)TILE_SIZE);
        y++;
    }
    draw_filled_disk(data->mlx_data->mini_map, data->mlx_data->mini_map->width / 2, data->mlx_data->mini_map->height / 2 , 7);
}
