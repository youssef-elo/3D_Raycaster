/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:53:35 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/08 21:06:56 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_check_first_last_line(t_map_context_h *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->map[x])
		x++;
	while (map->map[0][y])
	{
		if (map->map[0][y] != '1' && map->map[0][y] != ' ')
			ft_display_error("Error", map);
		y++;
	}
	y = 0;
	x--;
	while (map->map[x][y])
	{
		if (map->map[x][y] != '1' && map->map[x][y] != ' ')
			ft_display_error("Error", map);
		y++;
	}
}

void	ft_check_player(t_map_context_h *map)
{
	int	x;
	int	y;
	int	check;

	check = 0;
	x = 0;
	y = 0;
	while (map->map[x])
	{
		while (map->map[x][y])
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'W'
					|| map->map[x][y] == 'E' || map->map[x][y] == 'S')
				check ++;
			y++;
		}
		x++;
		y = 0;
	}
	if (check != 1)
		ft_display_error("Error", map);
}

void	ft_valid_path(t_map_context_h *map)
{
	int	x;
	int	y;

	((1) && (x = 0, y = 0));
	ft_check_first_last_line(map);
	ft_check_player(map);
	while (map->map[x])
	{	
		while (map->map[x][y])
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'W'
				|| map->map[x][y] == 'E' || map->map[x][y] == 'S'
				|| map->map[x][y] == '0')
			{
				if ((map->map[x][y + 1] == ' ' || !map->map[x][y + 1])
					|| map->map[x][y - 1] == ' ' || !map->map[x][y - 1])
					ft_display_error("Error", map);
				else if ((map->map[x + 1][y] == ' ' || !map->map[x + 1][y])
					|| (map->map[x - 1][y] == ' ' || !map->map[x - 1][y]))
					ft_display_error("Error", map);
			}
			y++;
		}
		((1) && (x++, y = 0));
	}
}

void	ft_double_array(t_map_context_h *map)
{
	map->map = ft_split(map->array, 10);
	if (!map->map)
		ft_display_error("Error", map);
	ft_adjust_map_size(map);
	ft_valid_path(map);
}
