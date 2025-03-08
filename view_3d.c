#include "cub3d.h"

void	draw_ceiling(data_t *d, int x0, int y0)
{
	int	ceiling;
	int	index;

	ceiling = 0;
	while (ceiling < y0)
	{
		index = (ceiling * d->mlx_data->view_3d->width + x0) * 4;
		d->mlx_data->view_3d->pixels[index + 0] = (d->ceiling >> 24) & 0xFF;
		d->mlx_data->view_3d->pixels[index + 1] = (d->ceiling >> 16) & 0xFF;
		d->mlx_data->view_3d->pixels[index + 2] = (d->ceiling >> 8) & 0xFF;
		d->mlx_data->view_3d->pixels[index + 3] = (d->ceiling) & 0xFF;
		ceiling++;
	}
}

void	draw_line_3d(data_t *data, int x0, int y0, int y1, uint32_t color)
{
	int	index;

	draw_ceiling(data, x0, y0);
	if (y0 < 0)
		y0 = 0;
	if (y1 > HEIGHT_3D)
		y1 = HEIGHT_3D - 1;
	while (y0 < y1)
	{
		index = (y0 * data->mlx_data->view_3d->width + x0) * 4;
		data->mlx_data->view_3d->pixels[index + 0] = (color >> 24) & 0xFF;
		data->mlx_data->view_3d->pixels[index + 1] = (color >> 16) & 0xFF;
		data->mlx_data->view_3d->pixels[index + 2] = (color >> 8) & 0xFF;
		data->mlx_data->view_3d->pixels[index + 3] = (color) & 0xFF;
		y0++;
	}
	while (y0 < data->mlx_data->view_3d->height - 1)
	{
		index = (y0 * data->mlx_data->view_3d->width + x0) * 4;
		data->mlx_data->view_3d->pixels[index + 0] = (data->floor >> 24) & 0xFF;
		data->mlx_data->view_3d->pixels[index + 1] = (data->floor >> 16) & 0xFF;
		data->mlx_data->view_3d->pixels[index + 2] = (data->floor >> 8) & 0xFF;
		data->mlx_data->view_3d->pixels[index + 3] = (data->floor) & 0xFF;
		y0++;
	}
}

void pre_3d(data_t *data, view_3d_t *d_3d, uint32_t *v_color, uint32_t *h_color)
{
	d_3d->scaler  = HEIGHT_3D * 100;
	*v_color = rgb(27, 96, 157, 255);
	*h_color = rgb(15, 76, 129, 255);
	d_3d->fov_half = FOV / 2;
	d_3d->angle_slice = FOV / NUMBER_OF_RAYS;
	d_3d->half_window = HEIGHT_3D / 2;

}

void draw_3d(data_t *data)
{
	int i;
	view_3d_t d_3d;
	uint32_t v_color;
	uint32_t h_color;

	i = 0 ;
	pre_3d(data, &d_3d, &v_color, &h_color);
	while (i < NUMBER_OF_RAYS)
	{
		d_3d.ray_angle = (data->view_angle - d_3d.fov_half) + (i * d_3d.angle_slice);
		d_3d.hor = shoot_horizontal(data, d_3d.ray_angle) ;
		d_3d.ver = shoot_vertical(data, d_3d.ray_angle);
		if (d_3d.ver <= d_3d.hor)
		{
			d_3d.w_height =  (d_3d.scaler / (d_3d.ver * cos(d_3d.ray_angle - data->view_angle)));
			d_3d.wall_half = d_3d.w_height / 2;
			d_3d.s_y = d_3d.half_window - (d_3d.wall_half);
			d_3d.e_y = d_3d.half_window + (d_3d.wall_half);
			draw_line_3d(data, NUMBER_OF_RAYS - i, d_3d.s_y, d_3d.e_y, v_color);
		}
		else 
		{
			d_3d.w_height = (d_3d.scaler / (d_3d.hor * cos(d_3d.ray_angle - data->view_angle)));
			d_3d.wall_half = d_3d.w_height / 2;
			d_3d.s_y = d_3d.half_window - (d_3d.wall_half);
			d_3d.e_y = d_3d.half_window + (d_3d.wall_half);
			draw_line_3d(data, NUMBER_OF_RAYS - i, d_3d.s_y, d_3d.e_y, h_color);
		}
		i++;
	}
}
