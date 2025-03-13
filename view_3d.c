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
	d_3d->scaler  = HEIGHT_3D * 850 * 2;
	*v_color = rgb(27, 96, 157, 255);
	*h_color = rgb(15, 76, 129, 255);
	d_3d->fov_half = FOV / 2;
	d_3d->angle_slice = FOV / NUMBER_OF_RAYS;
	d_3d->half_window = HEIGHT_3D / 2;

}


void	textured_line(data_t *data, view_3d_t *d_3d, line_t *line)
{
	double step;
	int view_index;
	double texture_index;
	int ceiling;

	ceiling = 0;
	texture_index = 0;
	view_index = line->y0; 
	step = (double)data->mlx_data->south->height / (double)d_3d->w_height;
	// step = (double)HEIGHT_3D / (double)d_3d->w_height;
	// printf("step : %f start: %d\n", step, line->y0);

	while(ceiling < line->y0)
	{
		put_pixel(data->mlx_data->view_3d, line->x0, ceiling, data->ceiling);
		ceiling++;
	}
	if (view_index < 0)
	{
		texture_index = -(view_index * step);
		view_index  = 0;
	}
	while(view_index < line->y1 && view_index < HEIGHT_3D -1)
	{
		
		
		if (view_index >= 0 && view_index < HEIGHT_3D && texture_index < (double)HEIGHT_3D && d_3d->ver_ray)
			re_put_pixel(data->mlx_data->view_3d, line->x0, view_index, 
		 	((uint32_t *)data->mlx_data->south->pixels)[(((int)(texture_index) * data->mlx_data->south->width) + (TILE - ((int)d_3d->ver_y % TILE)) * (data->mlx_data->south->width / TILE))]);
		if (view_index >= 0 && view_index < HEIGHT_3D && texture_index < (double)HEIGHT_3D && !d_3d->ver_ray)
			re_put_pixel(data->mlx_data->view_3d, line->x0, view_index, 
			((uint32_t *)data->mlx_data->south->pixels)[(((int)(texture_index) * data->mlx_data->south->width) + (((int)d_3d->hor_x % TILE)) * (data->mlx_data->south->width / TILE))]);
		texture_index += step;
		view_index++;
		// printf("view_index : %d texture_index : %f wall_height %d\n", view_index, texture_index, d_3d->w_height);
		
	}
	while(view_index < HEIGHT_3D -1)
	{
		put_pixel(data->mlx_data->view_3d, line->x0, view_index, data->ceiling);
		view_index++;
	}
}

void draw_3d(data_t *data)
{
	int i;
	view_3d_t d_3d;
	uint32_t v_color;
	uint32_t h_color;
	line_t line;

	i = 0;
	pre_3d(data, &d_3d, &v_color, &h_color);
	while (i < NUMBER_OF_RAYS)
	{
		d_3d.ver_ray = 0;
		d_3d.ray_angle = (data->view_angle - d_3d.fov_half) + (i * d_3d.angle_slice);
		d_3d.hor = shoot_horizontal(data, d_3d.ray_angle, &d_3d) ;
		d_3d.ver = shoot_vertical(data, d_3d.ray_angle, &d_3d);
		if (d_3d.ver <= d_3d.hor)
		{
			d_3d.ver_ray = 1;
			d_3d.w_height =  (d_3d.scaler / (d_3d.ver * cos(d_3d.ray_angle - data->view_angle)));
			d_3d.wall_half = d_3d.w_height / 2;
			line.y0 = d_3d.half_window - (d_3d.wall_half);
			line.y1 = d_3d.half_window + (d_3d.wall_half);
			line.x0 = NUMBER_OF_RAYS - i;
			// double fog_intensity = 1 -  ((d_3d.ver - 280) / (MAX_VIEW - 280));
			// if (fog_intensity > 1.0) fog_intensity = 1.0; // Clamp max
			// if (fog_intensity < 0.0) fog_intensity = 0.0;
			textured_line(data, &d_3d, &line);
			// draw_line_3d(data, NUMBER_OF_RAYS - i, d_3d.s_y, d_3d.e_y, rgb(27 * fog_intensity, 96 * fog_intensity, 157 * fog_intensity, 255));
		}
		else
		{
			d_3d.w_height = (d_3d.scaler / (d_3d.hor * cos(d_3d.ray_angle - data->view_angle)));
			d_3d.wall_half = d_3d.w_height / 2;
			line.y0 = d_3d.half_window - (d_3d.wall_half);
			line.y1 = d_3d.half_window + (d_3d.wall_half);
			line.x0 = NUMBER_OF_RAYS - i;
			// double fog_intensity = 1.0 - ((d_3d.hor - 280) / (MAX_VIEW - 280));
			// if (fog_intensity > 1.0) fog_intensity = 1.0; // Clamp max
			// if (fog_intensity < 0.0) fog_intensity = 0.0;
			textured_line(data, &d_3d, &line);
			// draw_line_3d(data, NUMBER_OF_RAYS - i, d_3d.s_y, d_3d.e_y, rgb(15 * fog_intensity, 76 * fog_intensity, 129 * fog_intensity, 255 ));
		}
		i++;
	}
}
