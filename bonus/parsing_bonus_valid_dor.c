/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_valid_dor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:23:51 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/08 21:26:16 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
