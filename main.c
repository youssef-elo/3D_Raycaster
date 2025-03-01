#include "cub3d.h"

double fabs(double n)
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

void draw_line_2(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;  // Step in the x direction
    int sy = (y0 < y1) ? 1 : -1;  // Step in the y direction
    int err = dx - dy;            // Error term

    while (1)
    {
        put_pixel(img, x0, y0, color); // Draw pixel at (x0, y0)

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

double shoot_horizontal(data_t *data, double ray_angle, double *horizontal_x, double *horizontal_y)
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
	int offset;

	direction_x = cos(ray_angle);
	direction_y = sin(ray_angle);
	// printf("%lf\n", ray_angle);
	wall_hit = 0;

	// if (direction_y == 0)
	// 	return (2147483647);
	if (direction_y < 0)
	{
		step = TILE_SIZE;
		offset = 1;
		// hit_y = data->player_y + (((int)data->player_y  % TILE_SIZE));
		hit_y = ceil(data->player_y / TILE_SIZE) * TILE_SIZE;
	}
	else 
	{
		step = -TILE_SIZE;
		offset = -1;
		hit_y = floor(data->player_y / TILE_SIZE) * TILE_SIZE;
		// hit_y = data->player_y - (((int)data->player_y  % TILE_SIZE));
	}
	// printf("hit_y: %lf step: %d\n", hit_y, step);
	// printf("direction_y: %lf hit_y: %lf step: %d\n",direction_y,  hit_y, step);
	while(!wall_hit)
	{
		scaling_factor = ( data->player_y - hit_y) / direction_y;

		// printf("scaling factor: %lf\n", scaling_factor);
		// printf("dy : %lf dx: %lf scaling factor: %lf\n", fabs(hit_y - data->player_y),fabs(direction_y - data->player_y),scaling_factor);
		hit_x = data->player_x + (scaling_factor * direction_x);
		if (hit_x < TILE_SIZE || hit_x > (WIDTH - TILE_SIZE))
			return(2147483647);
		// printf("hit_x: %lf hit_y: %lf\n", hit_y , hit_x);
		// draw_filled_disk(data->mlx_data->view, hit_x, hit_y, 3, rgb(255, 0  ,0, 255));
		if (data->map[(int)((hit_y + (step/ TILE_SIZE)) / TILE_SIZE)][(int)hit_x / TILE_SIZE ] == '1')
		{
			// draw_line_2(data, data->player_x, data->player_y, hit_x , hit_y, rgb(255, 0  ,0, 255));
			// printf("we have a hit: y : %lf x : %lf char : %c\n", hit_y , hit_x , data->map[(int)(hit_y / TILE_SIZE)][(int)hit_x /TILE_SIZE]);
			// printf("hit\n");
			if (!CUBE3D)
			{
				*horizontal_x = hit_x;
				*horizontal_y = hit_y;
			}
			// printf("x length: %lf y length: %lf magni: %lf\n", hit_x - data->player_x, hit_y - data->player_y, sqrt(pow(hit_x - data->player_x, 2) + pow(hit_y - data->player_y, 2)));
			// return (fabs(hit_y - data->player_y));
			return (sqrt(pow(hit_x - data->player_x, 2) + pow(hit_y - data->player_y, 2)));
		}
		hit_y += step;
		if (hit_y < TILE_SIZE || hit_y > (HEIGHT - TILE_SIZE))
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
	int offset;

	direction_x = cos(ray_angle);
	direction_y = sin(ray_angle);
	
	wall_hit = 0;
	if (direction_x < 0)
	{
		step = -TILE_SIZE;
		offset = -1;
		hit_x = floor(data->player_x / TILE_SIZE) * TILE_SIZE;
	}
	else
	{
		step = TILE_SIZE;
		offset = 1;
		hit_x = ceil(data->player_x / TILE_SIZE) * TILE_SIZE;
	}
	// printf("direction_x: %lf hit_x: %lf step: %d\n",direction_x,  hit_x, step);
	while(!wall_hit)
	{
		scaling_factor = (data->player_x - hit_x) / direction_x;
		hit_y = data->player_y + (scaling_factor * direction_y);
		if (hit_y < TILE_SIZE || hit_y > (HEIGHT - TILE_SIZE))
			return(2147483647);
		if (data->map[(int)(hit_y / TILE_SIZE)][((int)(hit_x + offset) / TILE_SIZE) ] == '1')
		{
			// printf("hit_x: %lf hit_y: %lf map_y: %d map_x : %d step : %d\n", hit_x, hit_y, ((int)hit_y / TILE_SIZE), ((int)hit_x / TILE_SIZE) + (step / TILE_SIZE), step);
			// draw_line_2(data, data->player_x, data->player_y, hit_x , hit_y, rgb(0, 0  ,255, 255));
			if ( !CUBE3D)
			{
				*vertical_x = hit_x;
				*vertical_y = hit_y;

			}
			// printf("x length: %lf y length: %lf magni: %lf\n", hit_x - data->player_x, hit_y - data->player_y, sqrt(pow(hit_x - data->player_x, 2) + pow(hit_y - data->player_y, 2)));
			// return (fabs(hit_x - data->player_x));
			return (sqrt(pow(hit_x - data->player_x, 2) + pow(hit_y - data->player_y, 2)));

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
	double vertical;
	double horizontal;
	double angle_slice = FOV / NUMBER_OF_RAYS;
	double fov_half = FOV / 2;

	i = 0;
	while(i < NUMBER_OF_RAYS)
	// while(i < 1)
	{
		ray_angle = (data->view_angle - fov_half) + (i * angle_slice);
		// printf(" ray_angle: %lf\n", ray_angle);
		// printf("%lf\n", ray_angle);
		horizontal = shoot_horizontal(data, ray_angle, &horizontal_x, &horizontal_y);
		vertical = shoot_vertical(data, ray_angle, &vertical_x, &vertical_y);
		printf("vertical; %lf horizontal: %lf\n", vertical, horizontal);
		if (horizontal < vertical)
		{
			data->rays[i] = horizontal;
			draw_line_2(data->mlx_data->rays_image, data->player_x, data->player_y, horizontal_x , horizontal_y, rgb(255, 0  ,0, 255));

		}
		else
		{
			// printf("%lf %lf\n", vertical, horizontal);
			data->rays[i] = vertical;
			draw_line_2(data->mlx_data->rays_image, data->player_x, data->player_y, vertical_x , vertical_y, rgb(255, 0  ,0, 255));
		}
		i++;
	}
	return (NULL);
}


void draw_minimap(data_t *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if ((j != 0 && j % TILE_SIZE == 0 || (i != 0 && i % TILE_SIZE == 0)) )
			{
				put_pixel(data->mlx_data->view, j , i, rgb(180, 180, 180, 255));
			}
			else
			{
				if (data->map[i / TILE_SIZE][j / TILE_SIZE] == '1')
				{
					put_pixel(data->mlx_data->view, j , i, rgb(128, 128, 128, 255));
				}
				if (data->map[i / TILE_SIZE][j / TILE_SIZE] == '0' || data->map[i / TILE_SIZE][j / TILE_SIZE] == 'P')
				{
					put_pixel(data->mlx_data->view, j , i, rgb(245, 245, 240, 255));
				}
			}
			j++;
		}
		i++;
	}
}
void minimap(data_t *data, mlx_data_t *mlx_data)
{
	if (CUBE3D == 0)
	{
		memset(mlx_data->rays_image->pixels, 0, mlx_data->rays_image->width * mlx_data->rays_image->height * BPP);
		draw_filled_disk(mlx_data->rays_image, data->player_x, data->player_y, 4, rgb(255, 0 , 0 , 255));
		shoot_rays(data);
		// draw_rays(data);
		mlx_image_to_window(mlx_data->mlx, mlx_data->rays_image, 0 , 0);
	}
}



void hook_handler( void *param)
{
	data_t *data;
	double direction_x;
	double direction_y;
	double next_x;
	double next_y;
	double speed;

	speed  = 8;

	data = (data_t *) param;

	if ( mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if ( mlx_is_key_down(data->mlx_data->mlx,  MLX_KEY_W ))
	{
		if (data->map[(int)((data->player_y - 7)  / TILE_SIZE)][(int)(data->player_x / TILE_SIZE)]!= '1')
		{
			direction_x = cos(data->view_angle );
			direction_y = sin(data->view_angle);

			next_x = data->player_x + (direction_x * speed);
			next_y = data->player_y - (direction_y * speed);
			if (data->map[(int)((next_y)  / TILE_SIZE)][(int)(next_x / TILE_SIZE)]!= '1')
			{
				data->player_y = next_y;
				data->player_x = next_x;
			}

		}
		if (!CUBE3D)
			minimap(data, data->mlx_data);
		else
			draw_3d(data);

		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y  - 7)  / TILE_SIZE), (int)(data->player_x) / TILE_SIZE);
		
	}
	if ( mlx_is_key_down(data->mlx_data->mlx,  MLX_KEY_S ))
	{
		direction_x = cos(data->view_angle);
		direction_y = sin(data->view_angle );

		next_x = data->player_x - (direction_x * speed);
		next_y = data->player_y + (direction_y * speed);
		if (data->map[(int)((next_y)  / TILE_SIZE)][(int)(next_x / TILE_SIZE)]!= '1')
		{
			data->player_y = next_y;
			data->player_x = next_x;
		}

		if (!CUBE3D)
			minimap(data, data->mlx_data);
		else
			draw_3d(data);

		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y  + 7)  / TILE_SIZE), (int)(data->player_x) / TILE_SIZE);
	}
	if ( mlx_is_key_down(data->mlx_data->mlx,  MLX_KEY_A ))
	{
		direction_x = cos(data->view_angle);
		direction_y = sin(data->view_angle);
		next_x = data->player_x + (-direction_y) * speed;
		next_y = data->player_y + direction_x * speed;
		if (data->map[(int)((next_y)  / TILE_SIZE)][(int)((next_x) / TILE_SIZE)]!= '1')
		{
			data->player_x = next_x;
			data->player_y = next_y;
		}

		if (!CUBE3D)
			minimap(data, data->mlx_data);
		else
			draw_3d(data);

		// ("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y)  / TILE_SIZE), (int)(data->player_x - 7) / TILE_SIZE);
	}
	if ( mlx_is_key_down(data->mlx_data->mlx,  MLX_KEY_D ))
	{
		// printf("%lf %lf mapx: %d map_y: %d\n", data->player_x, data->player_y ,(int)((data->player_y)  / TILE_SIZE), (int)(data->player_x + 7) / TILE_SIZE);
		direction_x = cos(data->view_angle);
		direction_y = sin(data->view_angle);
		next_x = data->player_x + direction_y * speed;
		next_y = data->player_y + (-direction_x) * speed;
		if (data->map[(int)((next_y)  / TILE_SIZE)][(int)((next_x) / TILE_SIZE)]!= '1')
		{
			data->player_x = next_x;
			data->player_y = next_y;
		}
		if (!CUBE3D)
			minimap(data, data->mlx_data);
		else
			draw_3d(data);

	}

	if ( mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
	{

		data->view_angle -= (M_PI / 36);
		if (data->view_angle < 0)
			data->view_angle += (2 * M_PI);
		if (!CUBE3D)
			minimap(data, data->mlx_data);
		else
			draw_3d(data);

		// data->view_angle = fmod(data->view_angle - (PI / 36), 2 * PI);
	// printf("view_angle %lf\n", data->view_angle);
	}
	if ( mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_RIGHT))
	{
	    // data->view_angle = fmod(data->view_angle + (PI / 36) + 2 * PI, 2 * PI);
		data->view_angle += (M_PI / 36);
		if (data->view_angle > ((double)2 * M_PI))
			data->view_angle -= (2 * M_PI);
		if (!CUBE3D)
			minimap(data, data->mlx_data);
		else
			draw_3d(data);
		// printf("view_angle %lf\n", data->view_angle);
	}
}






void draw_3d(data_t *data)
{
	int i;
	double vertical;
	double fov_half;
	double ray_angle;
	double horizontal;
	double angle_slice;
	int wall_height;
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	uint32_t vertical_color;
	uint32_t horizontal_color;
	int half_height = HEIGHT_3D / 2;

	vertical_color = rgb(27, 96, 157, 255);
	horizontal_color = rgb(15, 76, 129, 255);
	// horizontal_color = vertical_color;

	i = 0 ;
	fov_half = FOV / 2;
	angle_slice = FOV / NUMBER_OF_RAYS;
	memset(data->mlx_data->view_3d->pixels, 0, data->mlx_data->view_3d->width * data->mlx_data->view_3d->height * BPP);
	while (i < NUMBER_OF_RAYS)
	{
		ray_angle = (data->view_angle - fov_half) + (i * angle_slice);
		horizontal = shoot_horizontal(data, ray_angle, NULL, NULL) ;
		vertical = shoot_vertical(data, ray_angle, NULL, NULL);
		// printf("verti: %f horizontal: %f\n", vertical, horizontal);
		if (vertical < horizontal)
		{
			wall_height =  (HEIGHT_3D * 70 / (vertical * cos(ray_angle - data->view_angle))) ;
			start_y = half_height - (wall_height  / 2);
			end_y = half_height + (wall_height  / 2);
			// printf("start_y: %d end %d\n", start_y, end_y);
			draw_line_2(data->mlx_data->view_3d, i, start_y, i, end_y, vertical_color);
		}
		else 
		{
			wall_height = (HEIGHT_3D * 70 / (horizontal * cos(ray_angle - data->view_angle))) ;
			start_y = half_height - (wall_height  / 2);
			end_y = half_height + (wall_height  / 2);
			// printf("start_y: %d\n", wall_height);
			// printf("start_y: %d end %d\n", start_y, end_y);

			draw_line_2(data->mlx_data->view_3d, i, start_y, i, end_y, horizontal_color);
			
		}
		i++;
	}
	mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->view_3d, 0 ,0);
}

void floor_ceiling(data_t *data)
{
	int i;
	int j;
	uint32_t color; 

	color = 0;
	i = 0;
	j = 0;
	while(i < HEIGHT_3D)
	{
		j = 0;
		// if (i == HEIGHT_3D / 2)			
		// 	color = rgb(139, 69, 19, 255);
		while(j < WIDTH_3D)
		{
			put_pixel(data->mlx_data->floor_ceiling, j, i, color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->floor_ceiling, 0 , 0);
}


int main(int argc, char **argv){
	// parsing(argc , argv);
	data_t data;

	mlx_data_t mlx_data;
	data.mlx_data = &mlx_data;
	data.rays = malloc(sizeof(int) * NUMBER_OF_RAYS);
	bzero(data.rays, sizeof(int) * NUMBER_OF_RAYS);

	if (!CUBE3D)
	{
		mlx_data.mlx = mlx_init(WIDTH, HEIGHT, "Minimap", true);
		mlx_data.view = mlx_new_image(mlx_data.mlx, WIDTH, HEIGHT);
		mlx_data.rays_image = mlx_new_image(mlx_data.mlx, WIDTH, HEIGHT);
	}
	else 
	{
		mlx_data.mlx = mlx_init(WIDTH_3D, HEIGHT_3D, "Cub3d", true);
		mlx_data.view_3d = mlx_new_image(mlx_data.mlx, WIDTH_3D, HEIGHT_3D);
		mlx_data.floor_ceiling = mlx_new_image(mlx_data.mlx, WIDTH_3D, HEIGHT_3D);
		floor_ceiling(&data);
	}

	data.view_angle = (M_PI / 2);
	// printf("%lf\n", data.view_angle);
	data.map = (char*[]){
						"11111111111111111111111111111",
						"10000000000010010000000000001",
						"10P01010000000001010000000001",
						"10000000000000000000000000001",
						"10000000000000101100000000001",
						"10000010000000000000000000001",
						"10000000000000000000000000001",
						"11111111111111111111111111111"};

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
	if (!CUBE3D)
	{
		draw_minimap(&data);
		mlx_image_to_window(mlx_data.mlx, mlx_data.view, 0 ,  0);
		minimap(&data, &mlx_data);
	}
	else{
		draw_3d(&data);
	}
	mlx_loop_hook(mlx_data.mlx, hook_handler, &data);
	mlx_loop(mlx_data.mlx);
}