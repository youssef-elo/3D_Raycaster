#include "cub3d.h"

double	get_delta_time(void)
{
	double			delta;
	double			current_time;
	static double	last_time;
	struct timeval	time;

	last_time = 0;
	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);
	delta = (current_time - last_time) / 1000.0;
	last_time = current_time;
	return (delta);
}

void	display_fps(t_data *data)
{
	char				*str;
	static mlx_image_t	*pre;

	if (pre)
		mlx_delete_image(data->mlx_data->mlx, pre);
	str = ft_itoa(1.0 / get_delta_time());
	pre = mlx_put_string(data->mlx_data->mlx, str, 30, 20);
	free(str);
}

void	draw_3d(void *param)
{
	int			i;
	t_line		line;
	t_view_3d	d_3d;
	t_data		*data;

	i = 0;
	data = (t_data *)param;
	d_3d.r_angle = (data->p_angle - data->con.fov_half);
	while (i < NUMBER_OF_RAYS)
	{
		d_3d.ver_ray = 0;
		d_3d.r_angle += data->con.angle_i;
		d_3d.hor = shoot_horizontal(data, d_3d.r_angle, &d_3d);
		d_3d.ver = shoot_vertical(data, d_3d.r_angle, &d_3d);
		if (d_3d.ver < d_3d.hor)
			d_3d.ver_ray = 1;
		textured_line(data, &d_3d, &line, i);
		i++;
	}
}
