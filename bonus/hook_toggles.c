#include "cub3d_bonus.h"

void	rotate_mouse(double xpos, double ypos, void *param)
{
	double	dx;
	double	angle;
	data_t	*data;

	data = (data_t *)param;
	dx = WIDTH / 2 - xpos;
	angle = dx * ROTATION_FACTOR;
	data->p_angle += angle;
	if (data->p_angle > ((double)2 * M_PI))
		data->p_angle -= (2 * M_PI);
	if (data->p_angle < 0)
		data->p_angle += (2 * M_PI);
	data->dir_x = cos(data->p_angle);
	data->dir_y = sin(data->p_angle);
	mlx_set_mouse_pos(data->mlx_data->mlx, WIDTH / 2, HEIGHT / 2);
	minimap_3d(data);
}

void	open_fire(mouse_key_t butt, action_t act, modifier_key_t mods, void *p)
{
	data_t	*data;

	data = (data_t *)p;
	if (butt == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS)
	{
		if (!data->reload)
			data->firing = 1;
	}
	if (butt == MLX_MOUSE_BUTTON_LEFT && act == MLX_RELEASE)
		data->firing = 0;
}

void	flashlight(struct mlx_key_data keydata, void *param)
{
	data_t	*data;

	data = (data_t *)param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
	{
		if (data->fog_start == FOG_START)
		{
			data->fog_start = FOG_START_FLASH;
			data->fog_m = MAX_VIEW_FLASH;
		}
		else
		{
			data->fog_start = FOG_START;
			data->fog_m = MAX_VIEW;
		}
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		data->reload = 1;
}
