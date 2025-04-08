/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:50:52 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/08 19:52:08 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map(map_context_h *map)
{
	int	x;

	x = 0;
	free(map->south);
	free(map->north);
	free(map->east);
	free(map->west);
	free(map->floor_s);
	free(map->sky_s);
	free(map->array);
	if (!map->map)
		return ;
	x = size_of_line(map->map) - 1;
	while (x >= 0)
		free(map->map[x--]);
	free(map->map);
}

void	ft_set_map(map_context_h *map)
{
	map->array = NULL;
	map->west = NULL;
	map->north = NULL;
	map->east = NULL;
	map->south = NULL;
	map->sky_s = NULL;
	map->floor_s = NULL;
	map->read_map = 0;
	map->count = 0;
	map->map = NULL;
}
