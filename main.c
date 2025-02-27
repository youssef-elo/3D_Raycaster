#include "youssef.h"

double my_abs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}
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


void    draw_line(data_t *data, double angle, int length)
{
    int     x1, y1;
    int     dx, dy;
    int     step_x, step_y;
    int     error;
    int     color = 0xFFFFFF;  // White color for the line

    // Calculate the endpoint of the line using trigonometry
    x1 = data->player_x + cos(angle) * length;
    y1 = data->player_y + sin(angle) * length;

    // Bresenham's line algorithm
    dx = my_abs(x1 - data->player_x);
    dy = my_abs(y1 - data->player_y);
    step_x = (data->player_x < x1) ? 1 : -1;
    step_y = (data->player_y < y1) ? 1 : -1;
    error = dx - dy;

    while (1)
    {
        put_pixel(data->mlx_data->view, data->player_x, data->player_y, rgb(255, 255, 0, 255));
        if (data->player_x == x1 && data->player_y == y1)
            break;
        int e2 = error * 2;
        if (e2 > -dy)
        {
            error -= dy;
            data->player_x += step_x;
        }
        if (e2 < dx)
        {
            error += dx;
            data->player_y += step_y;
        }
    }
}

// void draw_rays(data_t *data)
// {
// 	int i;

// 	i = 0;
// 	double ray_angle;
// 	while(i < NUMBER_OF_RAYS)
// 	{
// 		ray_angle  = (data->view_angle - (FOV / 2)) + (i * (FOV / NUMBER_OF_RAYS));
// 		// draw_line(data, ray_angle, data->rays[i]);
// 		i++;
// 	}
// }

void draw_line_2(data_t *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;  // Step in the x direction
    int sy = (y0 < y1) ? 1 : -1;  // Step in the y direction
    int err = dx - dy;            // Error term

    while (1)
    {
        put_pixel(data->mlx_data->view, x0, y0, color); // Draw pixel at (x0, y0)

        if (x0 == x1 && y0 == y1) break;  // If we have reached the end point

        int e2 = 2 * err; // Double the error term for comparison

        // Move along x if the error is greater than the y difference
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        // Move along y if the error is less than the x difference
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

int shoot_horizontal(data_t *data, double ray_angle, double *horizontal_x, double *horizontal_y)
{
	int wall_hit;
	double hit_x;
	double hit_y;
	int direction;
	double direction_x;
	double direction_y;
	double scaling_factor;
	int map_y;
	int step;

	direction_x = cos(ray_angle);
	direction_y = sin(ray_angle);
	
	wall_hit = 0;
	if (direction_y < 0)
	{
		step = TILE_SIZE;
		hit_y = data->player_y + (((int)data->player_y  % TILE_SIZE));
	}
	else 
	{
		step = -TILE_SIZE;
		hit_y = data->player_y - (((int)data->player_y  % TILE_SIZE));
	}
	while(!wall_hit)
	{
		scaling_factor =  (hit_y - data->player_y) / direction_y;
		printf("scaling factor: %lf\n", scaling_factor);
		// printf("dy : %lf dx: %lf scaling factor: %lf\n", my_abs(hit_y - data->player_y),my_abs(direction_y - data->player_y),scaling_factor);
		hit_x = data->player_x + (scaling_factor * direction_x);
		if (hit_x < TILE_SIZE || hit_x > (WIDTH - TILE_SIZE))
			return(2147483647);
		// printf("hit_x: %lf hit_y: %lf\n", hit_y , hit_x);
		// draw_filled_disk(data->mlx_data->view, hit_x, hit_y, 3, rgb(255, 0  ,0, 255));
		if (data->map[(int)(hit_y / TILE_SIZE)][(int)hit_x /TILE_SIZE] == '1')
		{
			draw_line_2(data, data->player_x, data->player_y, hit_x , hit_y, rgb(255, 0  ,0, 255));
			// printf("we have a hit: y : %lf x : %lf char : %c\n", hit_y , hit_x , data->map[(int)(hit_y / TILE_SIZE)][(int)hit_x /TILE_SIZE]);
			// printf("hit\n");
			*horizontal_x = hit_x;
			*horizontal_y = hit_y;
			return sqrt(pow(hit_x - data->player_x, 2) + pow(hit_y - data->player_y, 2));
		}
		hit_y += step;
		if (hit_y < TILE_SIZE || hit_y > (HEIGHT  -TILE_SIZE))
			return(2147483647);
	}
	return (-1);
}


double shoot_vertical(data_t *data, double ray_angle, double *vertical_x, double *vertical_y)
{
	int wall_hit;
	double hit_x;
	double hit_y;
	int direction;
	double direction_x;
	double direction_y;
	double scaling_factor;
	int map_y;
	int step;

	direction_x = cos(ray_angle);
	direction_y = sin(ray_angle);
	
	wall_hit = 0;
	if (direction_x < 0)
	{
		step = TILE_SIZE;
		hit_x = data->player_x + (((int)data->player_x  % TILE_SIZE));
	}
	else 
	{
		step = -TILE_SIZE;
		hit_x = data->player_x - (((int)data->player_x  % TILE_SIZE));
	}
	// printf("hit_x: %lf step: %d\n", hit_x, step);
	while(!wall_hit)
	{
		scaling_factor = (hit_x - data->player_x) / direction_x;
		hit_y = data->player_y + (scaling_factor * direction_y);
		if (hit_y < 0 || hit_y > (HEIGHT))
			return(2147483647);
		if (data->map[(int)(hit_y / TILE_SIZE)][((int)hit_x / TILE_SIZE) ] == '1')
		{
			// printf("hit_x: %lf hit_y: %lf map_y: %d map_x : %d step : %d\n", hit_x, hit_y, ((int)hit_y / TILE_SIZE), ((int)hit_x / TILE_SIZE) + (step / TILE_SIZE), step);
			draw_line_2(data, data->player_x, data->player_y, hit_x , hit_y, rgb(0, 0  ,255, 255));
			*vertical_x = hit_x;
			*vertical_y = hit_y;
			return sqrt(pow(hit_x - data->player_x, 2) + pow(hit_y - data->player_y, 2));
		}
		hit_x += step;
		if (hit_x < 0 || hit_x > (WIDTH))
			return(2147483647);
	}
	return (2147483647);
}


int *shoot_rays(data_t *data)
{
	int i;
	double ray_angle;
	double horizontal_y;
	double horizontal_x;
	double vertical_x;
	double vertical_y;
	int vertical;
	int horizontal;

	i = 0;
	while(i < NUMBER_OF_RAYS)
	{
		ray_angle = (data->view_angle - (FOV / 2)) + (i * (FOV / NUMBER_OF_RAYS));
		// printf(" ray_angle: %lf\n", ray_angle);
		// printf("%lf\n", ray_angle);
		horizontal = shoot_horizontal(data, ray_angle, &horizontal_x, &horizontal_y);
		// vertical = shoot_vertical(data, ray_angle, &vertical_x, &vertical_y);
		// if (horizontal < vertical)
		// {
		// 	data->rays[i] = horizontal;
		// 	draw_line_2(data, data->player_x, data->player_y, horizontal_x , horizontal_y, rgb(255, 0  ,0, 255));

		// }
		// else if (vertical > horizontal)
		// {
		// 	printf("%d %d\n", vertical, horizontal);
		// 	data->rays[i] = vertical;
		// 	draw_line_2(data, data->player_x, data->player_y, vertical_x , vertical_y, rgb(0, 0  ,255, 255));
		// }
		i++;
	}
	return (NULL);
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
	shoot_rays(data);
	draw_filled_disk(mlx_data->view, data->player_x, data->player_y, 4, rgb(255, 0 , 0 , 255));
	// draw_rays(data);
	mlx_image_to_window(mlx_data->mlx, mlx_data->view, 0 , 0);
}



void hook_handler(mlx_key_data_t keydata, void *param)
{
	data_t *data;

	data =( data_t *) param;

	if ( keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	if ( keydata.key ==  MLX_KEY_W )
	{
		if (data->map[(int)((data->player_y - 7)  / TILE_SIZE)][(int)(data->player_x / TILE_SIZE)]!= '1')
			data->player_y -= 7;
		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y  - 7)  / TILE_SIZE), (int)(data->player_x) / TILE_SIZE);
		
	}
	if ( keydata.key ==  MLX_KEY_S )
	{
		if (data->map[(int)((data->player_y + 7)  / TILE_SIZE)][(int)(data->player_x / TILE_SIZE)]!= '1')
			data->player_y += 7;
		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y  + 7)  / TILE_SIZE), (int)(data->player_x) / TILE_SIZE);
	}
	if ( keydata.key ==  MLX_KEY_A )
	{
		if (data->map[(int)((data->player_y)  / TILE_SIZE)][(int)((data->player_x - 7) / TILE_SIZE)]!= '1')
			data->player_x -= 7;
		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y)  / TILE_SIZE), (int)(data->player_x - 7) / TILE_SIZE);
	}
	if ( keydata.key ==  MLX_KEY_D )
	{
		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y)  / TILE_SIZE), (int)(data->player_x + 7) / TILE_SIZE);
		if (data->map[(int)((data->player_y)  / TILE_SIZE)][(int)((data->player_x + 7) / TILE_SIZE)]!= '1')
			data->player_x += 7;
	}

	if ( keydata.key == MLX_KEY_LEFT)
	{

		data->view_angle += PI / 36;
		if (data->view_angle > ((double)2 * PI))
			data->view_angle -= (2 * PI);
		// data->view_angle = fmod(data->view_angle - (PI / 36), 2 * PI);
	printf("%lf\n", data->view_angle);
	}
	if ( keydata.key == MLX_KEY_RIGHT)
	{
	    // data->view_angle = fmod(data->view_angle + (PI / 36) + 2 * PI, 2 * PI);
		data->view_angle -= PI / 36;
		if (data->view_angle < 0)
			data->view_angle += (2 * PI);
		printf("%lf\n", data->view_angle);
	}
	minimap(data, data->mlx_data);
}











int main(int argc, char **argv){
	parsing(argc , argv);
	data_t data;

	mlx_data_t mlx_data;
	data.mlx_data = &mlx_data;
	data.rays = malloc(sizeof(int) * NUMBER_OF_RAYS);
	bzero(data.rays, sizeof(int) * NUMBER_OF_RAYS);

	mlx_data.mlx = mlx_init(WIDTH, HEIGHT, "Minimap", true);
	mlx_data.view = mlx_new_image(mlx_data.mlx, WIDTH, HEIGHT);

	data.view_angle =PI  / 2;
	printf("%lf\n", data.view_angle);
	data.map = (char*[]){
						"111111111111111111111",
						"100000000000100100001",
						"10P011100000000001101",
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