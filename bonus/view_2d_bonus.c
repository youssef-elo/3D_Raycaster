#include "cub3d_bonus.h"

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
	{
		ray_angle = (data->p_angle - fov_half) + (i * angle_slice);

		horizontal = shoot_horizontal_2d(data, ray_angle, &horizontal_x, &horizontal_y);
		vertical = shoot_vertical_2d(data, ray_angle, &vertical_x, &vertical_y);
		if (horizontal < vertical)
		{
			draw_line_2(data->mlx_data->rays_image, data->player_x, data->player_y, horizontal_x , horizontal_y, rgb(255, 0  ,0, 255));

		}
		else
		{
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
	while(i < data->height * TILE)
	{
		j = 0;
		while (j < data->width * TILE)
		{
			if ((j != 0 && j % TILE == 0 || (i != 0 && i % TILE == 0)) )
			{
				put_pixel(data->mlx_data->view, j , i, rgb(180, 180, 180, 255));
			}
			else
			{
				if (data->map[i / TILE][j / TILE] == '1')
				{
					put_pixel(data->mlx_data->view, j , i, rgb(128, 128, 128, 255));
				}
				if (data->map[i / TILE][j / TILE] == '0' || data->map[i / TILE][j / TILE] == 'P')
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
		draw_filled_disk(mlx_data->rays_image, data->player_x, data->player_y, 4);
		shoot_rays(data);
	}
}

double	shoot_horizontal_2d(data_t *d, double angle, double *h_x, double *h_y)
{
	raycaster_t	r_d;

	pre_horizontal(&r_d, angle, d);
	while (1)
	{
		r_d.scaling_factor = (d->player_y - r_d.hit_y) / r_d.direction_y;
		r_d.hit_x = d->player_x + (r_d.scaling_factor * r_d.direction_x);
		r_d.map_y = (r_d.hit_y + r_d. offset) / TILE;
		r_d.map_x = r_d.hit_x / TILE;
		if (r_d.hit_x < TILE
			|| r_d.hit_x > ((d->width * TILE) - TILE))
			return (OUT_OF_RANGE);
		if (d->map[r_d.map_y][r_d.map_x] == '1')
		{
			*h_x = r_d.hit_x;
			*h_y = r_d.hit_y;
			return (sqrt((r_d.hit_x - d->player_x) * (r_d.hit_x - d->player_x)
					+ (r_d.hit_y - d->player_y) * (r_d.hit_y - d->player_y)));
		}
		r_d.hit_y += r_d.step;
		if (r_d.hit_y < TILE
			|| r_d.hit_y > ((d->height * TILE) - TILE))
			return (OUT_OF_RANGE);
	}
	return (OUT_OF_RANGE);
}

void	draw_line_2(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		put_pixel(img, x0, y0, color);

		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

double	shoot_vertical_2d(data_t *d, double angle, double *v_x, double *v_y)
{
	raycaster_t	r_d;

	pre_vertical(&r_d, angle, d);
	while (1)
	{
		r_d.scaling_factor = (d->player_x - r_d.hit_x) / r_d.direction_x;
		r_d.hit_y = d->player_y + (r_d.scaling_factor * r_d.direction_y);
		if (r_d.hit_y < TILE || r_d.hit_y > ((d->height * TILE)))
			return (OUT_OF_RANGE);
		r_d.map_y = r_d.hit_y / TILE;
		r_d.map_x = (r_d.hit_x + r_d.offset) / TILE;
		if (d->map[r_d.map_y][r_d.map_x] == '1')
		{
			*v_x = r_d.hit_x;
			*v_y = r_d.hit_y;
			return (sqrt((r_d.hit_x - d->player_x) * (r_d.hit_x - d->player_x)
					+ (r_d.hit_y - d->player_y) * (r_d.hit_y - d->player_y)));
		}
		r_d.hit_x += r_d.step;
		if (r_d.hit_x < 0 || r_d.hit_x > (d->width * TILE))
			return (OUT_OF_RANGE);
	}
	return (OUT_OF_RANGE);
}