#include "cub3d_bonus.h"

void update_position(data_t *data, char c, int i, int j)
{
	if (c == 'N')
		data->p_angle = M_PI_2;
	if (c == 'S')
		data->p_angle = 3 * (M_PI_2);
	if (c == 'E')
		data->p_angle = 0;
	if (c == 'W')
		data->p_angle = M_PI;
	data->player_y = (i * TILE) + (TILE / 2);
	data->player_x = (j * TILE) + (TILE / 2);
}

void find_player(data_t *data)
{
	int i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				update_position(data, data->map[i][j], i, j);
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	data->width = j;
	data->height = i;
}

void link_parsing(data_t *d, map_context_h *p_data, mlx_data_t *mlx_data)
{
	d->map = p_data->map;
	d->mlx_data = mlx_data;
	start_mlx(d, p_data);
	d->ceiling = rgb(p_data->sky[0], p_data->sky[1], p_data->sky[2], 255);
	d->floor = rgb(p_data->floor[0], p_data->floor[1], p_data->floor[2], 255);
	find_player(d);
	d->map_x = d->player_x / TILE;
	d->map_y = d->player_y / TILE;
	d->dir_x = cos(d->p_angle);
	d->dir_y = sin(d->p_angle);
	d->offset.n_offset = d->mlx_data->north->width / TILE;
	d->offset.s_offset = d->mlx_data->south->width / TILE;
	d->offset.e_offset = d->mlx_data->east->width / TILE;
	d->offset.w_offset = d->mlx_data->west->width / TILE;
}


void pre_compute(data_t *data)
{
	int i;
	double r_angle;
	double fov_half;
	double angle_i;

	i = 0;
	data->con.angle_i = FOV / NUMBER_OF_RAYS;
	data->con.p = (WIDTH / 2) / tan(FOV / 2);
	data->con.scaler = data->con.p * TILE;
	data->con.fov_half = FOV / 2;
	data->con.half_window = HEIGHT / 2;
	data->cos = malloc( sizeof(double) * NUMBER_OF_RAYS);
	while(i < NUMBER_OF_RAYS)
	{
		r_angle = (data->p_angle - data->con.fov_half) + (i * data->con.angle_i);
		data->cos[i] = cos(r_angle - data->p_angle);
		i++;
	}
	data->fog_start = FOG_START;
	data->fog_m = MAX_VIEW;	
}