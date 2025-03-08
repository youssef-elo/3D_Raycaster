// #include "cub3d.h"

// double fabs(double n)
// {
// 	if (n < 0)
// 		return (-n);
// 	return (n);
// }
// void put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
// {
//     if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
//     {
//         int index = (y * img->width + x) * 4; 
//         img->pixels[index + 0] = (color >> 24) & 0xFF; 
//         img->pixels[index + 1] = (color >> 16) & 0xFF; 
//         img->pixels[index + 2] = (color >> 8) & 0xFF;  
//         img->pixels[index + 3] = (color) & 0xFF;       
//     }
// }


// void draw_filled_disk(mlx_image_t *img, int xc, int yc, int r, uint32_t color)
// {
//     for (int x = xc - r; x <= xc + r; x++)
//     {
//         int dx = x - xc;
//         int y_max = sqrt(r * r - dx * dx); 

//         for (int y = yc - y_max; y <= yc + y_max; y++)
//             put_pixel(img, x, y, color);
//     }

// }

// uint32_t rgb(int r, int g, int b, int a)
// {
//     return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
// }



// void draw_line_2(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
// {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = (x0 < x1) ? 1 : -1; 
//     int sy = (y0 < y1) ? 1 : -1;  
//     int err = dx - dy;         

//     while (1)
//     {
//         put_pixel(img, x0, y0, color); 
//         if (x0 == x1 && y0 == y1) break;  
//         int e2 = 2 * err; 
//         if (e2 > -dy)
//         {
//             err -= dy;
//             x0 += sx;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             y0 += sy;
//         }
//     }
// }

// double shoot_horizontal(data_t *data, double ray_angle, double *horizontal_x, double *horizontal_y)
// {
// 	int wall_hit;
// 	double hit_x;
// 	double hit_y;
// 	int direction;
// 	double direction_x;
// 	double direction_y;
// 	double scaling_factor;
// 	int map_y;
// 	int step;
// 	int offset;

// 	direction_x = cos(ray_angle);
// 	direction_y = sin(ray_angle);
// 	wall_hit = 0;

// 	if (direction_y == 0)
// 		return (2147483647);
// 	if (direction_y < 0)
// 	{
// 		step = TILE;
// 		offset = 1;
// 		hit_y = ceil(data->player_y / TILE) * TILE;
// 	}
// 	else 
// 	{
// 		step = -TILE;
// 		offset = -1;
// 		hit_y = floor(data->player_y / TILE) * TILE;
// 	}
// 	while(!wall_hit)
// 	{
// 		scaling_factor = ( data->player_y - hit_y) / direction_y;

// 		hit_x = data->player_x + (scaling_factor * direction_x);
// 		if (hit_x < TILE || hit_x > (WIDTH - TILE))
// 			return(2147483647);
// 		if (data->map[(int)((hit_y + (step/ TILE)) / TILE)][(int)hit_x / TILE ] == '1')
// 		{
// 			if (!CUBE3D)
// 			{
// 				*horizontal_x = hit_x;
// 				*horizontal_y = hit_y;
// 			}
// 			return (sqrt(pow(hit_x - data->player_x, 2) + pow(hit_y - data->player_y, 2)));
// 		}
// 		hit_y += step;
// 		if (hit_y < TILE || hit_y > (HEIGHT - TILE))
// 			return(2147483647);
// 	}
// 	return (-1);
// }


// double shoot_vertical(data_t *data, double ray_angle, double *vertical_x, double *vertical_y)
// {
// 	int wall_hit;
// 	double hit_x;
// 	double hit_y;
// 	int direction;
// 	double direction_x;
// 	double direction_y;
// 	double scaling_factor;
// 	int map_y;
// 	int step;
// 	int offset;

// 	direction_x = cos(ray_angle);
// 	direction_y = sin(ray_angle);
	
// 	wall_hit = 0;
// 	if (direction_x < 0)
// 	{
// 		step = -TILE;
// 		offset = -1;
// 		hit_x = floor(data->player_x / TILE) * TILE;
// 	}
// 	else
// 	{
// 		step = TILE;
// 		offset = 1;
// 		hit_x = ceil(data->player_x / TILE) * TILE;
// 	}
// 	while(!wall_hit)
// 	{
// 		scaling_factor = (data->player_x - hit_x) / direction_x;
// 		hit_y = data->player_y + (scaling_factor * direction_y);
// 		if (hit_y < TILE || hit_y > (HEIGHT - TILE))
// 			return(2147483647);
// 		if (data->map[(int)(hit_y / TILE)][((int)(hit_x + offset) / TILE) ] == '1')
// 		{
// 			if ( !CUBE3D)
// 			{
// 				*vertical_x = hit_x;
// 				*vertical_y = hit_y;

// 			}
// 			return (sqrt(pow(hit_x - data->player_x, 2) + pow(hit_y - data->player_y, 2)));
// 		}
// 		hit_x += step;
// 		if (hit_x < 0 || hit_x > (WIDTH))
// 			return(2147483647);
// 	}
// 	return (2147483647);
// }


// int *shoot_rays(data_t *data)
// {
// 	int i;
// 	double ray_angle;
// 	double horizontal_y;
// 	double horizontal_x;
// 	double vertical_x;
// 	double vertical_y;
// 	double vertical;
// 	double horizontal;
// 	double angle_slice = FOV / NUMBER_OF_RAYS;
// 	double fov_half = FOV / 2;

// 	i = 0;
// 	while(i < NUMBER_OF_RAYS)
// 	{
// 		ray_angle = (data->view_angle - fov_half) + (i * angle_slice);
// 		horizontal = shoot_horizontal(data, ray_angle, &horizontal_x, &horizontal_y);
// 		vertical = shoot_vertical(data, ray_angle, &vertical_x, &vertical_y);
// 		if (horizontal < vertical)
// 		{
// 			data->rays[i] = horizontal;
// 			draw_line_2(data->mlx_data->rays_image, data->player_x, data->player_y, horizontal_x , horizontal_y, rgb(255, 0  ,0, 255));

// 		}
// 		else
// 		{
// 			data->rays[i] = vertical;
// 			draw_line_2(data->mlx_data->rays_image, data->player_x, data->player_y, vertical_x , vertical_y, rgb(255, 0  ,0, 255));
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }


// void draw_minimap(data_t *data)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while(i < HEIGHT)
// 	{
// 		j = 0;
// 		while (j < WIDTH)
// 		{
// 			if ((j != 0 && j % TILE == 0 || (i != 0 && i % TILE == 0)) )
// 			{
// 				put_pixel(data->mlx_data->view, j , i, rgb(180, 180, 180, 255));
// 			}
// 			else
// 			{
// 				if (data->map[i / TILE][j / TILE] == '1')
// 				{
// 					put_pixel(data->mlx_data->view, j , i, rgb(128, 128, 128, 255));
// 				}
// 				if (data->map[i / TILE][j / TILE] == '0' || data->map[i / TILE][j / TILE] == 'P')
// 				{
// 					put_pixel(data->mlx_data->view, j , i, rgb(245, 245, 240, 255));
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
// void minimap(data_t *data, mlx_data_t *mlx_data)
// {
// 	if (CUBE3D == 0)
// 	{
// 		memset(mlx_data->rays_image->pixels, 0, mlx_data->rays_image->width * mlx_data->rays_image->height * BPP);
// 		draw_filled_disk(mlx_data->rays_image, data->player_x, data->player_y, 4, rgb(255, 0 , 0 , 255));
// 		shoot_rays(data);
// 		mlx_image_to_window(mlx_data->mlx, mlx_data->rays_image, 0 , 0);
// 	}
// }



// void hook_handler( void *param)
// {
// 	data_t *data;
// 	double direction_x;
// 	double direction_y;
// 	double next_x;
// 	double next_y;
// 	double speed;

// 	speed  = 8;

// 	data = (data_t *) param;

// 	if ( mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_ESCAPE))
// 		exit(0);
// 	if ( mlx_is_key_down(data->mlx_data->mlx,  MLX_KEY_W ))
// 	{
// 		if (data->map[(int)((data->player_y - 7)  / TILE)][(int)(data->player_x / TILE)]!= '1')
// 		{
// 			direction_x = cos(data->view_angle );
// 			direction_y = sin(data->view_angle);

// 			next_x = data->player_x + (direction_x * speed);
// 			next_y = data->player_y - (direction_y * speed);
// 			if (data->map[(int)((next_y)  / TILE)][(int)(next_x / TILE)]!= '1')
// 			{
// 				data->player_y = next_y;
// 				data->player_x = next_x;
// 			}

// 		}
// 		if (!CUBE3D)
// 			minimap(data, data->mlx_data);
// 		else
// 			draw_3d(data);
// 	}
// 	if ( mlx_is_key_down(data->mlx_data->mlx,  MLX_KEY_S ))
// 	{
// 		direction_x = cos(data->view_angle);
// 		direction_y = sin(data->view_angle );

// 		next_x = data->player_x - (direction_x * speed);
// 		next_y = data->player_y + (direction_y * speed);
// 		if (data->map[(int)((next_y)  / TILE)][(int)(next_x / TILE)]!= '1')
// 		{
// 			data->player_y = next_y;
// 			data->player_x = next_x;
// 		}

// 		if (!CUBE3D)
// 			minimap(data, data->mlx_data);
// 		else
// 			draw_3d(data);
// 	}
// 	if ( mlx_is_key_down(data->mlx_data->mlx,  MLX_KEY_A ))
// 	{
// 		if (data->map[(int)((data->player_y)  / TILE)][(int)((data->player_x - 7) / TILE)]!= '1')
// 		{
// 			direction_x = cos(data->view_angle);
// 			direction_y = sin(data->view_angle);
// 		}
// 		if (!CUBE3D)
// 			minimap(data, data->mlx_data);
// 		else
// 			draw_3d(data);
// 	}
// 	if ( mlx_is_key_down(data->mlx_data->mlx,  MLX_KEY_D ))
// 	{
// 		if (data->map[(int)((data->player_y)  / TILE)][(int)((data->player_x + 7) / TILE)]!= '1')
// 			data->player_x += 7;
// 		if (!CUBE3D)
// 			minimap(data, data->mlx_data);
// 		else
// 			draw_3d(data);
// 	}
// 	if ( mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
// 	{
// 		data->view_angle -= (M_PI / 36);
// 		if (data->view_angle > ((double)2 * M_PI))
// 			data->view_angle -= (2 * M_PI);
// 		if (!CUBE3D)
// 			minimap(data, data->mlx_data);
// 		else
// 			draw_3d(data);
// 	}
// 	if ( mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_RIGHT))
// 	{
// 		if (!CUBE3D)
// 			minimap(data, data->mlx_data);
// 				else
// 					draw_3d(data);
// 		data->view_angle += (M_PI / 36);
// 		if (data->view_angle < 0)
// 			data->view_angle += (2 * M_PI);
// 	}
// }


// void draw_3d(data_t *data)
// {
// 	int i;
// 	double vertical;
// 	double fov_half;
// 	double ray_angle;
// 	double horizontal;
// 	double angle_slice;
// 	int wall_height;
// 	int start_x;
// 	int start_y;
// 	int end_x;
// 	int end_y;
// 	uint32_t vertical_color;
// 	uint32_t horizontal_color;
// 	int half_height = HEIGHT_3D / 2;

// 	vertical_color = rgb(169, 169, 169, 255);
// 	horizontal_color = rgb(186, 142, 75, 255);

// 	i = 0 ;
// 	fov_half = FOV / 2;
// 	angle_slice = FOV / NUMBER_OF_RAYS;
// 	memset(data->mlx_data->view_3d->pixels, 0, data->mlx_data->view_3d->width * data->mlx_data->view_3d->height * BPP);
// 	while (i < NUMBER_OF_RAYS)
// 	{
// 		ray_angle = (data->view_angle - fov_half) + (i * angle_slice);
// 		horizontal = shoot_horizontal(data, ray_angle, NULL, NULL) ;
// 		vertical = shoot_vertical(data, ray_angle, NULL, NULL);
// 		if (vertical < horizontal)
// 		{
// 			wall_height =  HEIGHT_3D * TILE / vertical  / cos(ray_angle - data->view_angle);
// 			start_y = half_height - (wall_height  / 2);
// 			end_y = half_height + (wall_height  / 2);
// 			draw_line_2(data->mlx_data->view_3d, i, start_y, i, end_y, vertical_color);
// 		}
// 		else 
// 		{
// 			wall_height = HEIGHT_3D * TILE  /  horizontal / cos(ray_angle - data->view_angle);
// 			start_y = half_height - (wall_height  / 2);
// 			end_y = half_height + (wall_height  / 2);
// 			draw_line_2(data->mlx_data->view_3d, i, start_y, i, end_y, horizontal_color);
			
// 		}
// 		i++;
// 	}
// 	mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->view_3d, 0 ,0);
// }

// void floor_ceiling(data_t *data)
// {
// 	int i;
// 	int j;
// 	uint32_t color; 

// 	color = 0;
// 	i = 0;
// 	j = 0;
// 	while(i < HEIGHT_3D)
// 	{
// 		j = 0;
// 		while(j < WIDTH_3D)
// 		{
// 			put_pixel(data->mlx_data->floor_ceiling, j, i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->floor_ceiling, 0 , 0);
// }


// int main(int argc, char **argv){
// 	data_t data;

// 	mlx_data_t mlx_data;
// 	data.mlx_data = &mlx_data;
// 	data.rays = malloc(sizeof(int) * NUMBER_OF_RAYS);
// 	bzero(data.rays, sizeof(int) * NUMBER_OF_RAYS);

// 	if (!CUBE3D)
// 	{
// 		mlx_data.mlx = mlx_init(WIDTH, HEIGHT, "Minimap", true);
// 		mlx_data.view = mlx_new_image(mlx_data.mlx, WIDTH, HEIGHT);
// 		mlx_data.rays_image = mlx_new_image(mlx_data.mlx, WIDTH, HEIGHT);
// 	}
// 	else 
// 	{
// 		mlx_data.mlx = mlx_init(WIDTH_3D, HEIGHT_3D, "Cub3d", true);
// 		mlx_data.view_3d = mlx_new_image(mlx_data.mlx, WIDTH_3D, HEIGHT_3D);
// 		mlx_data.floor_ceiling = mlx_new_image(mlx_data.mlx, WIDTH_3D, HEIGHT_3D);
// 		floor_ceiling(&data);
// 	}

// 	data.view_angle = (M_PI / 2 );
// 	data.map = (char*[]){
// 						"11111111111111111111111111111",
// 						"10000000000010010000000000001",
// 						"100P1110000000000110000000001",
// 						"10000000000000000000000000001",
// 						"10000000000000111000000000001",
// 						"10000010000000000000000000001",
// 						"10000000000000000000000000001",
// 						"11111111111111111111111111111"};

// 	for ( int i = 0; i < HEIGHT / TILE; i++)
// 	{
// 		for(int j =  0; j < WIDTH / TILE; j++)
// 		{
// 			if (data.map[i][j] == 'P')
// 			{
// 				data.player_y = (i * TILE) + (TILE / 2);
// 				data.player_x = (j * TILE) + (TILE / 2);
// 			}
// 		}
// 	}
// 	printf("%lf %lf\n", data.player_x, data.player_y);
// 	if (!CUBE3D)
// 	{
// 		draw_minimap(&data);
// 		mlx_image_to_window(mlx_data.mlx, mlx_data.view, 0 ,  0);
// 		minimap(&data, &mlx_data);
// 	}
// 	else{
// 		draw_3d(&data);
// 	}
// 	mlx_loop_hook(mlx_data.mlx, hook_handler, &data);
// 	mlx_loop(mlx_data.mlx);
// }