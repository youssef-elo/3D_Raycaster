/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:14 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/08 18:20:30 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	get_delta_time(void)
{
	static double	last_time;
	struct timeval	time;
	double			current_time;
	double			delta;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);
	delta = (current_time - last_time) / 1000.0;
	last_time = current_time;
	return (delta);
}

void	put_fps(t_data *data)
{
	char	*str;

	if (data->mlx_data->fps)
	{
		mlx_delete_image(data->mlx_data->mlx, data->mlx_data->fps);
		data->mlx_data->fps = NULL;
	}
	str = ft_itoa(1.0 / get_delta_time());
	data->mlx_data->fps = mlx_put_string(data->mlx_data->mlx, str, 30, 20);
	free(str);
}
