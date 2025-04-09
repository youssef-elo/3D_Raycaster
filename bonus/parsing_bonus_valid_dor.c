/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_valid_dor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:23:51 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/09 15:29:58 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_adjust_map_size(t_map_context_h *map)
{
	t_var_size_h	var;

	((1) && (var.x = 0, var.max = 0, var.y = 0, var.i = 0));
	while (map->map[var.i])
	{
		if (var.max < ft_strlen(map->map[var.i]))
			var.max = ft_strlen(map->map[var.i]);
		var.i++;
	}
	while (map->map[var.x])
	{
		if (var.max > ft_strlen(map->map[var.x]))
		{
			var.array = ft_get_string(var.max - ft_strlen(map->map[var.x]));
			map->map[var.x] = ft_strjoin_n(map->map[var.x], var.array, map);
			free(var.array);
		}
		while (map->map[var.x][var.y])
		{
			if (map->map[var.x][var.y] == ' ')
				map->map[var.x][var.y] = ' ';
			var.y++;
		}
		((1) && (var.x++, var.y = 0));
	}
}

void	ft_valid_door(t_map_context_h *map)
{
	int	x;
	int	y;

	((1) && (x = 0, y = 0));
	while (map->map[x])
	{
		while (map->map[x][y])
		{
			if (map->map[x][y] == 'D')
			{
				if (map->map[x][y - 1] != '1' || map->map[x][y + 1] != '1')
				{
					if (map->map[x - 1][y] != '1' || map->map[x + 1][y] != '1')
						ft_display_error("Error", map);
				}
			}
			y++;
		}
		x++;
		y = 0;
	}
}
