/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:22:19 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/08 18:22:20 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flashlight(struct mlx_key_data keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
	{
		if (data->fog_m == MAX_VIEW)
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
}

uint32_t	apply_fog(t_data *d, uint32_t original_color, double distance)
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	double		fog_intensity;

	r = original_color & 0xFF;
	g = (original_color >> 8) & 0xFF;
	b = (original_color >> 16) & 0xFF;
	fog_intensity = (distance - d->fog_start) / (d->fog_m - d->fog_start);
	if (fog_intensity < 0.0f)
		fog_intensity = 0.0;
	if (fog_intensity > 1.0f)
		fog_intensity = 1.0f;
	r = r * (1 - fog_intensity);
	g = g * (1 - fog_intensity);
	b = b * (1 - fog_intensity);
	return (r | (g << 8) | (b << 16) | (255 << 24));
}
