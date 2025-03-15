#include "cub3d.h"

void	pre_hor(data_t *data, line_t *line, view_3d_t *d_3d, wall_3d_t *v)
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

void	draw_wall_hor(data_t *data, line_t *line, view_3d_t *d_3d)
{
	wall_3d_t	v;

	pre_hor(data, line, d_3d, &v);
	while (v.v_i < line->y1 && v.v_i < HEIGHT_3D -1)
	{
		if (v.v_i >= 0 && v.v_i < HEIGHT_3D && v.tex_i < (double)HEIGHT_3D)
		{
			v.col_i = (((int)(v.tex_i)) * v.tx->width) + v.tex_x;
			v.col = ((uint32_t *)v.tx->pixels)[v.col_i];
			if (line->x0 >= 0
				&& line->x0 < (int)data->mlx_data->view_3d->width && v.v_i >= 0
				&& v.v_i < (int)data->mlx_data->view_3d->height)
			{
				v.i = (v.v_i * data->mlx_data->view_3d->width + line->x0) * 4;
				data->mlx_data->view_3d->pixels[v.i + 3] = (v.col >> 24) & 0xFF;
				data->mlx_data->view_3d->pixels[v.i + 2] = (v.col >> 16) & 0xFF;
				data->mlx_data->view_3d->pixels[v.i + 1] = (v.col >> 8) & 0xFF;
				data->mlx_data->view_3d->pixels[v.i + 0] = (v.col) & 0xFF;
			}
		}
		v.tex_i += v.step;
		v.v_i++;
	}
}

void	pre_ver(data_t *data, line_t *line, view_3d_t *d_3d, wall_3d_t *v)
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

void	draw_wall_ver(data_t *data, line_t *line, view_3d_t *d_3d)
{
	wall_3d_t	v;

	pre_ver(data, line, d_3d, &v);
	while (v.v_i < line->y1 && v.v_i < HEIGHT_3D -1)
	{
		if (v.v_i >= 0 && v.v_i < HEIGHT_3D
			&& v.tex_i < (double)HEIGHT_3D)
		{
			v.col_i = (((int)(v.tex_i)) * v.tx->width) + v.tex_x;
			v.col = ((uint32_t *)v.tx->pixels)[v.col_i];
			if (line->x0 >= 0 && line->x0 < (int)data->mlx_data->view_3d->width
				&& v.v_i >= 0 && v.v_i < (int)data->mlx_data->view_3d->height)
			{
				v.i = (v.v_i * data->mlx_data->view_3d->width + line->x0) * 4;
				data->mlx_data->view_3d->pixels[v.i + 3] = (v.col >> 24) & 0xFF;
				data->mlx_data->view_3d->pixels[v.i + 2] = (v.col >> 16) & 0xFF;
				data->mlx_data->view_3d->pixels[v.i + 1] = (v.col >> 8) & 0xFF;
				data->mlx_data->view_3d->pixels[v.i + 0] = (v.col) & 0xFF;
			}
		}
		v.tex_i += v.step;
		v.v_i++;
	}
}
