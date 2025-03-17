#include "cub3d.h"

void	draw_ceiling_3d(data_t *data, line_t *line)
{
	int			index;
	int			ceiling;
	mlx_image_t	*img;	

	ceiling = 0;
	img = data->mlx_data->view_3d;
	while (ceiling < line->y0)
	{
		if (line->x0 >= 0 && line->x0 < (int)img->width
			&& ceiling >= 0 && ceiling < (int)img->height)
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

void	draw_floor_3d(data_t *d, line_t *line)
{
	int	index;
	int	view_i;

	view_i = line->y1;
	while (view_i < HEIGHT_3D -1)
	{
		if (line->x0 >= 0 && line->x0 < (int)d->mlx_data->view_3d->width
	
			&& view_i >= 0
			&& view_i < (int)d->mlx_data->view_3d->height)
		{
			index = (view_i * d->mlx_data->view_3d->width + line->x0) * 4;
			d->mlx_data->view_3d->pixels[index + 0] = (d->floor >> 24) & 0xFF;
			d->mlx_data->view_3d->pixels[index + 1] = (d->floor >> 16) & 0xFF;
			d->mlx_data->view_3d->pixels[index + 2] = (d->floor >> 8) & 0xFF;
			d->mlx_data->view_3d->pixels[index + 3] = (d->floor) & 0xFF;
		}
		view_i++;
	}
}

void	textured_line(data_t *d, view_3d_t *d_3d, line_t *line, int i)
{
	int	tmp;

	if (d_3d->ver_ray)
	{
		tmp = d_3d->ver * d->cos[i];
		d_3d->w_height = (d->consts.scaler / (tmp));
	}
	else if (!d_3d->ver_ray)
	{
		tmp = d_3d->hor * d->cos[i];
		d_3d->w_height = (d->consts.scaler / (tmp));
	}
	d_3d->wall_half = d_3d->w_height / 2;
	line->y0 = d->consts.half_window - (d_3d->wall_half);
	line->y1 = d->consts.half_window + (d_3d->wall_half);
	line->x0 = (NUMBER_OF_RAYS - i);
	draw_ceiling_3d(d, line);
	if (d_3d->ver_ray == 0)
		draw_wall_hor(d, line, d_3d);
	if (d_3d->ver_ray == 1)
		draw_wall_ver(d, line, d_3d);
	draw_floor_3d(d, line);
}


double get_delta_time()
{
    static double last_time = 0;
    struct timeval time;
    gettimeofday(&time, NULL);
    double current_time = (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);
    
    double delta = (current_time - last_time) / 1000.0;
    last_time = current_time;

    return delta;  // Time per frame in seconds
}



void	draw_3d(void *param)
{
	int			i;
	line_t		line;
	view_3d_t	d_3d;
	data_t *data;
	char *str;
	static mlx_image_t *pre;

	data = (data_t *)param;

	i = 0;
	if (pre)
	{
		mlx_delete_image(data->mlx_data->mlx, pre);
	}
	str = ft_itoa(1.0/ get_delta_time());
	pre  = mlx_put_string(data->mlx_data->mlx, str, 30, 20);
	free(str);
	// printf("%f\n", 1.0/ get_delta_time());
	d_3d.r_angle = (data->p_angle - data->consts.fov_half);
	while (i < NUMBER_OF_RAYS)
	{
		d_3d.ver_ray = 0;
		// d_3d.r_angle = (data->p_angle - data->consts.fov_half) + (i * data->consts.angle_i);
		d_3d.r_angle += data->consts.angle_i;
		d_3d.hor = shoot_horizontal(data, d_3d.r_angle, &d_3d);
		d_3d.ver = shoot_vertical(data, d_3d.r_angle, &d_3d);
		if (d_3d.ver < d_3d.hor)
			d_3d.ver_ray = 1;
		textured_line(data, &d_3d, &line, i);
		i++;
	}
}

