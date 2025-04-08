/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:26 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/08 18:20:27 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint32_t	apply_fog(t_data *d, uint32_t original_color, double distance)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	double	fog_intensity;

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
