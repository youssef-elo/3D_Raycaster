#include "cub3d.h"

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
