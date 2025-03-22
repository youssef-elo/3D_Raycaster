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
			&& view_i >= 0 && view_i < (int)d->mlx_data->view_3d->height)
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
		d_3d->w_height = (d->con.scaler / (tmp));
	}
	else if (!d_3d->ver_ray)
	{
		tmp = d_3d->hor * d->cos[i];
		d_3d->w_height = (d->con.scaler / (tmp));
	}
	d_3d->wall_half = d_3d->w_height / 2;
	line->y0 = d->con.half_window - (d_3d->wall_half);
	line->y1 = d->con.half_window + (d_3d->wall_half);
	line->x0 = (NUMBER_OF_RAYS - i);
	draw_ceiling_3d(d, line);
	if (d_3d->ver_ray == 0)
		draw_wall_hor(d, line, d_3d);
	if (d_3d->ver_ray == 1)
		draw_wall_ver(d, line, d_3d);
	draw_floor_3d(d, line);
}
