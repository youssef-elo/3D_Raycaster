#include "cub3d.h"

void	draw_ceiling(t_data *d, int x0, int y0)
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

void	pre_hor(t_data *data, t_line *line, t_view_3d *d_3d, t_wall_3d *v)
{
	if ((data->player_y - d_3d->hor_y) > 0)
	{
		v->tx = data->mlx_data->north;
		v->tex_x = (((int)d_3d->hor_x % TILE)) * data->offset.n_offset;
	}
	if ((data->player_y - d_3d->hor_y) <= 0)
	{
		v->tx = data->mlx_data->south;
		v->tex_x = (TILE - ((int)d_3d->hor_x % TILE)) * data->offset.s_offset;
	}
	v->v_i = line->y0;
	v->tex_i = 0;
	v->step = (double)v->tx->height / (double)d_3d->w_height;
	if (v->v_i < 0)
	{
		v->tex_i = -(v->v_i * v->step);
		v->v_i = 0;
	}
}

void	draw_wall_hor(t_data *data, t_line *line, t_view_3d *d_3d)
{
	t_wall_3d	v;
	int			width;

	pre_hor(data, line, d_3d, &v);
	v.i = (v.v_i * data->mlx_data->view_3d->width + line->x0) * 4;
	width = data->mlx_data->view_3d->width * 4;
	while (v.v_i < line->y1 && v.v_i < HEIGHT -1)
	{
		if (v.v_i >= 0 && v.v_i < HEIGHT && v.tex_i < (double)HEIGHT)
		{
			v.col_i = (((int)(v.tex_i)) * v.tx->width) + v.tex_x;
			v.col = ((uint32_t *)v.tx->pixels)[v.col_i];
			if (data->ceiling == 255 && data->floor == 255)
				v.col = apply_fog(data, v.col, d_3d->hor);
			data->mlx_data->view_3d->pixels[v.i + 3] = (v.col >> 24) & 0xFF;
			data->mlx_data->view_3d->pixels[v.i + 2] = (v.col >> 16) & 0xFF;
			data->mlx_data->view_3d->pixels[v.i + 1] = (v.col >> 8) & 0xFF;
			data->mlx_data->view_3d->pixels[v.i + 0] = (v.col) & 0xFF;
		}
		v.tex_i += v.step;
		v.v_i++;
		v.i += width;
	}
}

void	pre_ver(t_data *data, t_line *line, t_view_3d *d_3d, t_wall_3d *v)
{
	v->tex_i = 0;
	v->v_i = line->y0;
	if (d_3d->ver_ray && (data->player_x - d_3d->ver_x) > 0)
	{
		v->tx = data->mlx_data->west;
		v->tex_x = (TILE - ((int)d_3d->ver_y % TILE)) * data->offset.w_offset;
	}
	if (d_3d->ver_ray && (data->player_x - d_3d->ver_x) <= 0)
	{
		v->tx = data->mlx_data->east;
		v->tex_x = (((int)d_3d->ver_y % TILE)) * data->offset.e_offset;
	}
	v->step = (double)v->tx->height / (double)d_3d->w_height;
	if (v->v_i < 0)
	{
		v->tex_i = -(v->v_i * v->step);
		v->v_i = 0;
	}
}

void	draw_wall_ver(t_data *data, t_line *line, t_view_3d *d_3d)
{
	t_wall_3d	v;
	int			width;

	pre_ver(data, line, d_3d, &v);
	v.i = (v.v_i * data->mlx_data->view_3d->width + line->x0) * 4;
	width = data->mlx_data->view_3d->width * 4;
	while (v.v_i < line->y1 && v.v_i < HEIGHT -1)
	{
		v.col_i = (((int)(v.tex_i)) * v.tx->width) + v.tex_x;
		v.col = ((uint32_t *)v.tx->pixels)[v.col_i];
		if (data->ceiling == 255 && data->floor == 255)
			v.col = apply_fog(data, v.col, d_3d->ver);
		data->mlx_data->view_3d->pixels[v.i + 3] = (v.col >> 24) & 0xFF;
		data->mlx_data->view_3d->pixels[v.i + 2] = (v.col >> 16) & 0xFF;
		data->mlx_data->view_3d->pixels[v.i + 1] = (v.col >> 8) & 0xFF;
		data->mlx_data->view_3d->pixels[v.i + 0] = (v.col) & 0xFF;
		v.tex_i += v.step;
		v.v_i++;
		v.i += width;
	}
}
