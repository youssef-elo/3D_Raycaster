#include "cub3d.h"

void	pre_horizontal(t_raycaster *ray_d, double angle, t_data *data)
{
	ray_d->direction_x = cos(angle);
	ray_d->direction_y = sin(angle);
	if (ray_d->direction_y < 0)
	{
		ray_d->step = TILE;
		ray_d->offset = 1;
		ray_d->hit_y = ((int)(data->player_y / TILE) + 1) * TILE;
	}
	else
	{
		ray_d->step = -TILE;
		ray_d->offset = -1;
		ray_d->hit_y = (int)(data->player_y / TILE) * TILE;
	}
}

double	shoot_horizontal(t_data *d, double angle, t_view_3d *d_3d)
{
	t_raycaster	r_d;

	pre_horizontal(&r_d, angle, d);
	while (1)
	{
		r_d.scaling_factor = (d->player_y - r_d.hit_y) / r_d.direction_y;
		r_d.hit_x = d->player_x + (r_d.scaling_factor * r_d.direction_x);
		r_d.map_y = (r_d.hit_y + r_d. offset) / TILE;
		r_d.map_x = r_d.hit_x / TILE;
		if (r_d.hit_x < TILE
			|| r_d.hit_x > ((d->width * TILE) - TILE))
			return (OUT_OF_RANGE);
		if (d->map[r_d.map_y][r_d.map_x] == '1')
		{
			d_3d->hor_x = r_d.hit_x;
			d_3d->hor_y = r_d.hit_y;
			return (sqrt((r_d.hit_x - d->player_x) * (r_d.hit_x - d->player_x)
					+ (r_d.hit_y - d->player_y) * (r_d.hit_y - d->player_y)));
		}
		r_d.hit_y += r_d.step;
		if (r_d.hit_y < TILE
			|| r_d.hit_y > ((d->height * TILE) - TILE))
			return (OUT_OF_RANGE);
	}
	return (OUT_OF_RANGE);
}

void	pre_vertical(t_raycaster *ray_d, double angle, t_data *data)
{
	ray_d->direction_x = cos(angle);
	ray_d->direction_y = sin(angle);
	if (ray_d->direction_x < 0)
	{
		ray_d->step = -TILE;
		ray_d->offset = -1;
		ray_d->hit_x = (int)(data->player_x / TILE) * TILE;
	}
	else
	{
		ray_d->step = TILE;
		ray_d->offset = 1;
		ray_d->hit_x = ((int)(data->player_x / TILE) + 1) * TILE;
	}
}

double	shoot_vertical(t_data *d, double angle, t_view_3d *d_3d)
{
	t_raycaster	r_d;

	pre_vertical(&r_d, angle, d);
	while (1)
	{
		r_d.scaling_factor = (d->player_x - r_d.hit_x) / r_d.direction_x;
		r_d.hit_y = d->player_y + (r_d.scaling_factor * r_d.direction_y);
		if (r_d.hit_y < TILE || r_d.hit_y > ((d->height * TILE)))
			return (OUT_OF_RANGE);
		r_d.map_y = r_d.hit_y / TILE;
		r_d.map_x = (r_d.hit_x + r_d.offset) / TILE;
		if (d->map[r_d.map_y][r_d.map_x] == '1')
		{
			d_3d->ver_x = r_d.hit_x;
			d_3d->ver_y = r_d.hit_y;
			return (sqrt((r_d.hit_x - d->player_x) * (r_d.hit_x - d->player_x)
					+ (r_d.hit_y - d->player_y) * (r_d.hit_y - d->player_y)));
		}
		r_d.hit_x += r_d.step;
		if (r_d.hit_x < 0 || r_d.hit_x > (d->width * TILE))
			return (OUT_OF_RANGE);
	}
	return (OUT_OF_RANGE);
}
