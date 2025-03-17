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


uint32_t apply_fog(uint32_t original_color, float distance) {
    // 1. Extract RGB components
    uint8_t a = (original_color >> 24) & 0xFF;
    uint8_t b = (original_color >> 16) & 0xFF;
    uint8_t g = (original_color >> 8)  & 0xFF;
    uint8_t r = original_color & 0xFF;

	uint32_t fog_color =  0x000000FF ;
    // 2. Extract fog color components
    uint8_t fog_r = (fog_color >> 24) & 0xFF;
    uint8_t fog_g = (fog_color >> 16) & 0xFF;
    uint8_t fog_b = (fog_color >> 8)  & 0xFF;

    // 3. Calculate fog intensity (0.0 = no fog, 1.0 = full fog)
    float fog_intensity = (distance - FOG_START) / (MAX_VIEW - FOG_START);
    fog_intensity = fog_intensity < 0.0f ? 0.0f : (fog_intensity > 1.0f ? 1.0f : fog_intensity);

    // 4. Lerp between original color and fog color
    r = r * (1 - fog_intensity) + fog_r * fog_intensity;
    g = g * (1 - fog_intensity) + fog_g * fog_intensity;
    b = b * (1 - fog_intensity) + fog_b * fog_intensity;

    // 5. Rebuild 32-bit color
    return r | (g << 8) | (b << 16) | (a << 24);
}


void	draw_wall_hor(data_t *data, line_t *line, view_3d_t *d_3d)
{
	wall_3d_t	v;
	int width;

	pre_hor(data, line, d_3d, &v);
	v.i = (v.v_i * data->mlx_data->view_3d->width + line->x0) * 4;
	width = data->mlx_data->view_3d->width * 4;
	while (v.v_i < line->y1 && v.v_i < HEIGHT_3D -1)
	{
		if (v.v_i >= 0 && v.v_i < HEIGHT_3D && v.tex_i < (double)HEIGHT_3D)
		{
			double fog_intensity = 1.0 - ((d_3d->hor - 280) / (MAX_VIEW - 280));
			if (fog_intensity > 1.0) fog_intensity = 1.0; // Clamp max
			if (fog_intensity < 0.0) fog_intensity = 0.0;
			v.col_i = (((int)(v.tex_i)) * v.tx->width) + v.tex_x;
			v.col = ((uint32_t *)v.tx->pixels)[v.col_i];

			v.col = apply_fog(v.col, d_3d->hor);
			
			if (line->x0 >= 0
				&& line->x0 < (int)data->mlx_data->view_3d->width && v.v_i >= 0
				&& v.v_i < (int)data->mlx_data->view_3d->height)
			{
				// v.i = (v.v_i * data->mlx_data->view_3d->width + line->x0) * 4;
				data->mlx_data->view_3d->pixels[v.i + 3] = (v.col >> 24) & 0xFF;
				data->mlx_data->view_3d->pixels[v.i + 2] = (v.col >> 16) & 0xFF;
				data->mlx_data->view_3d->pixels[v.i + 1] = (v.col >> 8) & 0xFF;
				data->mlx_data->view_3d->pixels[v.i + 0] = (v.col) & 0xFF;
			}
		}
		v.tex_i += v.step;
		v.v_i++;
		v.i += width;
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
	int width;

	pre_ver(data, line, d_3d, &v);
	// if (line->x0 >= 0 && line->x0 < (int)data->mlx_data->view_3d->width)
	// 	return ;
	v.i = (v.v_i * data->mlx_data->view_3d->width + line->x0) * 4;
	width = data->mlx_data->view_3d->width * 4;
	while (v.v_i < line->y1 && v.v_i < HEIGHT_3D -1)
	{
		// if (v.tex_i < (double)HEIGHT_3D)
		// {
			v.col_i = (((int)(v.tex_i)) * v.tx->width) + v.tex_x;
			v.col = ((uint32_t *)v.tx->pixels)[v.col_i];

			v.col = apply_fog(v.col, d_3d->ver);
			data->mlx_data->view_3d->pixels[v.i + 3] = (v.col >> 24) & 0xFF;
			data->mlx_data->view_3d->pixels[v.i + 2] = (v.col >> 16) & 0xFF;
			data->mlx_data->view_3d->pixels[v.i + 1] = (v.col >> 8) & 0xFF;
			data->mlx_data->view_3d->pixels[v.i + 0] = (v.col) & 0xFF;
		// }
		v.tex_i += v.step;
		v.v_i++;
		v.i += width;
	}
}
