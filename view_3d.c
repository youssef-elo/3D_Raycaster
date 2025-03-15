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

void	draw_ceiling_3d(data_t *data, line_t *line)
{
	int ceiling;
	int index;
	mlx_image_t *img;

	ceiling = 0;
	img = data->mlx_data->view_3d;
	while(ceiling < line->y0)
	{
		if (line->x0 >= 0 && line->x0 < (int)img->width && ceiling >= 0 && ceiling < (int)img->height)
		{
			index = (ceiling * img->width + line->x0) * 4;
			img->pixels[index + 0] = (data->ceiling >> 24) & 0xFF;
			img->pixels[index + 1] = (data->ceiling >> 16) & 0xFF;
			img->pixels[index + 2] = (data->ceiling >> 8) & 0xFF;
			img->pixels[index + 3] = (data->ceiling) & 0xFF;
		}
		ceiling++;
	}
}


void draw_wall_hor(data_t *data, line_t *line, view_3d_t *d_3d)
{
	mlx_image_t *img;
	wall_3d_t var;

	// if ((data->player_y - d_3d->hor_y) > 0)
	// {
		img = data->mlx_data->south;
		var.tex_x = (((int)d_3d->hor_x % TILE)) * (img->width / TILE);
	// }
	// if ((data->player_y - d_3d->hor_y) <= 0)
	// {
	// 	img = data->mlx_data->south;
	// 	var.tex_x = (TILE - ((int)d_3d->hor_x % TILE)) * (img->width / TILE);
		
	// }
	printf("%d\n", var.tex_x);
	var.v_index = line->y0;
	var.t_index = 0;
	var.step = (double)img->height / (double)d_3d->w_height;
	if (var.v_index < 0)
	{
		var.t_index = -(var.v_index * var.step);
		var.v_index  = 0;
	}
	while(var.v_index < line->y1 && var.v_index < HEIGHT_3D -1)
	{
		if (var.v_index >= 0 && var.v_index < HEIGHT_3D && var.t_index < (double)HEIGHT_3D)
		{
			var.col = ((uint32_t *)img->pixels)[(((int)(var.t_index) * img->width) + var.tex_x)];
			if (line->x0 >= 0 && line->x0 < (int)data->mlx_data->view_3d->width && var.v_index >= 0 && var.v_index < (int)data->mlx_data->view_3d->height)
			{
				var.i = (var.v_index * data->mlx_data->view_3d->width + line->x0) * 4;
				data->mlx_data->view_3d->pixels[var.i + 3] = (var.col >> 24) & 0xFF; // b
				data->mlx_data->view_3d->pixels[var.i + 2] = (var.col >> 16) & 0xFF; // g	
				data->mlx_data->view_3d->pixels[var.i + 1] = (var.col >> 8) & 0xFF; // r
				data->mlx_data->view_3d->pixels[var.i + 0] = (var.col) & 0xFF;
			}
		}
		var.t_index += var.step;
		var.v_index++;
	}
}

void draw_wall_ver(data_t *data, line_t *line, view_3d_t *d_3d)
{
	int	index;
	int	v_index;
	int texture_x_v;
	int texture_x_h;
	double	step;
	double	t_index;
	uint32_t color;
	mlx_image_t *img;

	t_index = 0;
	v_index = line->y0;
	if (d_3d->ver_ray && (data->player_x - d_3d->ver_x) > 0)
	{
		img = data->mlx_data->west;
		texture_x_v = (TILE - ((int)d_3d->ver_y % TILE)) * (img->width / TILE);
	}
	else
	{
		img = data->mlx_data->east;
		texture_x_v = (((int)d_3d->ver_y % TILE)) * (img->width / TILE);
	}
	step = (double)img->height / (double)d_3d->w_height;

	// if (d_3d->ver_ray && (data->player_x - d_3d->ver_x) > 0)
	// 	texture_x_v = (TILE - ((int)d_3d->ver_y % TILE)) * (img->width / TILE);
	if (v_index < 0)
	{
		t_index = -(v_index * step);
		v_index  = 0;
	}
	while(v_index < line->y1 && v_index < HEIGHT_3D -1)
	{
		if (v_index >= 0 && v_index < HEIGHT_3D && t_index < (double)HEIGHT_3D)
		{
			color = ((uint32_t *)img->pixels)[(((int)(t_index) * img->width) + texture_x_v)];
			if (line->x0 >= 0 && line->x0 < (int)data->mlx_data->view_3d->width && v_index >= 0 && v_index < (int)data->mlx_data->view_3d->height)
			{
				index = (v_index * data->mlx_data->view_3d->width + line->x0) * 4;
				data->mlx_data->view_3d->pixels[index + 3] = (color >> 24) & 0xFF; // b
				data->mlx_data->view_3d->pixels[index + 2] = (color >> 16) & 0xFF; // g	
				data->mlx_data->view_3d->pixels[index + 1] = (color >> 8) & 0xFF; // r
				data->mlx_data->view_3d->pixels[index + 0] = (color) & 0xFF;
			}
		}
		// if (v_index >= 0 && v_index < HEIGHT_3D && t_index < (double)HEIGHT_3D)
		// {
		// 	color = ((uint32_t *)img->pixels)[(((int)(t_index) * img->width) + texture_x_h)];
		// 	if (line->x0 >= 0 && line->x0 < (int)data->mlx_data->view_3d->width && v_index >= 0 && v_index < (int)data->mlx_data->view_3d->height)
		// 	{
		// 		index = (v_index * data->mlx_data->view_3d->width + line->x0) * 4;
		// 		data->mlx_data->view_3d->pixels[index + 3] = (color >> 24) & 0xFF; // b
		// 		data->mlx_data->view_3d->pixels[index + 2] = (color >> 16) & 0xFF; // g	
		// 		data->mlx_data->view_3d->pixels[index + 1] = (color >> 8) & 0xFF; // r
		// 		data->mlx_data->view_3d->pixels[index + 0] = (color) & 0xFF;
		// 	}
		// }
		t_index += step;
		v_index++;
	}
	// draw_line_3d(data, line->x0, 0, 0, rgb(255, 0, 0, 255));
}

void draw_floor_3d(data_t *data, line_t *line)
{
	int index;
	int view_index;

	view_index = line->y1;
	while(view_index < HEIGHT_3D -1)
	{
		if (line->x0 >= 0 && line->x0 < (int)data->mlx_data->view_3d->width && view_index >= 0 && view_index < (int)data->mlx_data->view_3d->height)
		{
			index = (view_index * data->mlx_data->view_3d->width + line->x0) * 4;
			data->mlx_data->view_3d->pixels[index + 0] = (data->floor >> 24) & 0xFF;
			data->mlx_data->view_3d->pixels[index + 1] = (data->floor >> 16) & 0xFF;
			data->mlx_data->view_3d->pixels[index + 2] = (data->floor >> 8) & 0xFF;
			data->mlx_data->view_3d->pixels[index + 3] = (data->floor) & 0xFF;
		}
		// put_pixel(data->mlx_data->view_3d, line->x0, view_index, rgb(136, 152, 178, 255));
		view_index++;
	}
}

void	textured_line(data_t *data, view_3d_t *d_3d, line_t *line)
{
	// int ceiling;

	// double step;
	// int view_index;
	// double texture_index;
	// ceiling = 0;
	// texture_index = 0;
	// view_index = line->y0; 
	// step = (double)data->mlx_data->south->height / (double)d_3d->w_height;
	// if (view_index < 0)
	// {
	// 	texture_index = -(view_index * step);
	// 	view_index  = 0;
	// }
	draw_ceiling_3d(data, line);
	if (!d_3d->ver_ray)
		draw_wall_hor(data, line, d_3d);
	if (d_3d->ver_ray)
		draw_wall_ver(data, line, d_3d);
	draw_floor_3d(data, line);
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
		
		d_3d.ray_angle = (data->view_angle - d_3d.fov_half) + (i * d_3d.angle_slice);
		d_3d.hor = shoot_horizontal(data, d_3d.ray_angle, &d_3d) ;
		d_3d.ver = shoot_vertical(data, d_3d.ray_angle, &d_3d);
		if (d_3d.ver < d_3d.hor)
		{
			d_3d.ver_ray = 1;
			d_3d.w_height =  (d_3d.scaler / (d_3d.ver * cos(d_3d.ray_angle - data->view_angle)));
			d_3d.wall_half = d_3d.w_height / 2;
			line.y0 = d_3d.half_window - (d_3d.wall_half);
			line.y1 = d_3d.half_window + (d_3d.wall_half);
			line.x0 = (NUMBER_OF_RAYS - i) * (WIDTH_3D / NUMBER_OF_RAYS);
			
			// double fog_intensity = 1 -  ((d_3d.ver - 280) / (MAX_VIEW - 280));
			// if (fog_intensity > 1.0) fog_intensity = 1.0; // Clamp max
			// if (fog_intensity < 0.0) fog_intensity = 0.0;
			textured_line(data, &d_3d, &line);
		}
		else
		{
			d_3d.ver_ray = 0;
			d_3d.w_height = (d_3d.scaler / (d_3d.hor * cos(d_3d.ray_angle - data->view_angle)));
			d_3d.wall_half = d_3d.w_height / 2;
			line.y0 = d_3d.half_window - (d_3d.wall_half);
			line.y1 = d_3d.half_window + (d_3d.wall_half);
			line.x0 = (NUMBER_OF_RAYS - i) * (WIDTH_3D / NUMBER_OF_RAYS);
			// double fog_intensity = 1.0 - ((d_3d.hor - 280) / (MAX_VIEW - 280));
			// if (fog_intensity > 1.0) fog_intensity = 1.0; // Clamp max
			// if (fog_intensity < 0.0) fog_intensity = 0.0;
			textured_line(data, &d_3d, &line);
		}
		i++;
	}
}
