#include "youssef.h"


void put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
    if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
    {
        int index = (y * img->width + x) * 4; 
        img->pixels[index + 0] = (color >> 24) & 0xFF; 
        img->pixels[index + 1] = (color >> 16) & 0xFF; 
        img->pixels[index + 2] = (color >> 8) & 0xFF;  
        img->pixels[index + 3] = (color) & 0xFF;       
    }
}


void draw_filled_disk(mlx_image_t *img, int xc, int yc, int r, uint32_t color)
{
    for (int x = xc - r; x <= xc + r; x++)
    {
        int dx = x - xc;
        int y_max = sqrt(r * r - dx * dx); 

        for (int y = yc - y_max; y <= yc + y_max; y++)
            put_pixel(img, x, y, color);
    }

}

uint32_t rgb(int r, int g, int b, int a)
{
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

void minimap(data_t *data, mlx_data_t *mlx_data)
{
	int y;
	int x;

	for ( int i = 0; i < HEIGHT; i++)
	{
		for ( int j = 0 ; j < WIDTH; j++)
		{
			if ((j != 0 && j % TILE_SIZE == 0 || (i != 0 && i % TILE_SIZE == 0)) )
			{
				put_pixel(mlx_data->view, j , i, rgb(180, 180, 180, 255));
			}
			else
			{
				if (data->map[i / TILE_SIZE][j / TILE_SIZE] == '1')
				{
					put_pixel(mlx_data->view, j , i, rgb(128, 128, 128, 255));
				}
				if (data->map[i / TILE_SIZE][j / TILE_SIZE] == '0' || data->map[i / TILE_SIZE][j / TILE_SIZE] == 'P')
				{
					put_pixel(mlx_data->view, j , i, rgb(245, 245, 240, 255));
				}
			}
			
		}
	}
	draw_filled_disk(mlx_data->view, data->player_x, data->player_y, 4, rgb(255, 0 , 0 , 255));
	mlx_image_to_window(mlx_data->mlx, mlx_data->view, 0 , 0);
}



void hook_handler(mlx_key_data_t keydata, void *param)
{
	data_t *data;

	data =( data_t *) param;

	if ( keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	if ( keydata.key ==  MLX_KEY_UP && keydata.action == MLX_RELEASE)
	{
		if (data->map[(int)((data->player_y - 8)  / TILE_SIZE)][(int)(data->player_x / TILE_SIZE)]!= '1')
			data->player_y -= 8;
		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y  - 8)  / TILE_SIZE), (int)(data->player_x) / TILE_SIZE);
		
	}
	if ( keydata.key ==  MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
	{
		if (data->map[(int)((data->player_y + 7)  / TILE_SIZE)][(int)(data->player_x / TILE_SIZE)]!= '1')
			data->player_y += 8;
		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y  + 7)  / TILE_SIZE), (int)(data->player_x) / TILE_SIZE);
	}
	if ( keydata.key ==  MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
	{
		if (data->map[(int)((data->player_y)  / TILE_SIZE)][(int)((data->player_x - 8) / TILE_SIZE)]!= '1')
			data->player_x -= 8;
		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y)  / TILE_SIZE), (int)(data->player_x - 8) / TILE_SIZE);
	}
	if ( keydata.key ==  MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
	{
		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y)  / TILE_SIZE), (int)(data->player_x + 7) / TILE_SIZE);
		if (data->map[(int)((data->player_y)  / TILE_SIZE)][(int)((data->player_x + 7) / TILE_SIZE)]!= '1')
			data->player_x += 8;
	}
	minimap(data, data->mlx_data);
}



int *shoot_rays(data_t *data)
{
	int i;

	i = 0;
	double ray_angle;
	while(i < NUMBER_OF_RAYS)
	{
		ray_angle = (data->view_angle - (FOV / 2)) + (i * (FOV / NUMBER_OF_RAYS));
		i++;
	}
}



int main(){
	data_t data;

	mlx_data_t mlx_data;
	data.mlx_data = &mlx_data;

	mlx_data.mlx = mlx_init(WIDTH, HEIGHT, "Minimap", true);
	mlx_data.view = mlx_new_image(mlx_data.mlx, WIDTH, HEIGHT);

	data.view_angle = PI  / 2;
	data.map = (char*[]){
						"111111111111111111111",
						"1P0000000000100100001",
						"100011100000000001101",
						"100000000000000000001",
						"100000000000001110001",
						"100000100000000000001",
						"100000000000000000001",
						"111111111111111111111"};

	for ( int i = 0; i < HEIGHT / TILE_SIZE; i++)
	{
		for(int j =  0; j < WIDTH / TILE_SIZE; j++)
		{
			if (data.map[i][j] == 'P')
			{
				data.player_y = (i * TILE_SIZE) + (TILE_SIZE / 2);
				data.player_x = (j * TILE_SIZE) + (TILE_SIZE / 2);
			}
		}
	}
	// printf("%lf %lf\n", data.player_x, data.player_y);
	minimap(&data, &mlx_data);
	mlx_key_hook(mlx_data.mlx, hook_handler, &data);
	mlx_loop(mlx_data.mlx);
}