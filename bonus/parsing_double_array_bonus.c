/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_double_array.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:53:35 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/09 15:32:17 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_value_vars(int *x, int *y, int *i)
{
	*x = 0;
	*y = -1;
	*i = -1;
}

void	ft_check_first_last_line(t_map_context_h *map)
{
	int	x;
	int	y;
	int	i;

	set_value_vars(&x, &y, &i);
	while (map->map[x])
		x++;
	while (map->map[0][++y])
	{
		if (map->map[0][y] != '1' && map->map[0][y] != ' ')
			ft_display_error("Error", map);
	}
	((1) && (y = -1, x--));
	while (map->map[x][++y])
	{
		if (map->map[x][y] != '1' && map->map[x][y] != ' ')
			ft_display_error("Error", map);
	}
	while (++i <= x)
	{
		if ((map->map[i][0] != '1' && map->map[i][0] != ' ')
			|| (map->map[i][ft_strlen(map->map[0]) - 1] != ' '
			&& map->map[i][ft_strlen(map->map[0]) - 1] != '1'))
			ft_display_error("Error", map);
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
	ft_valid_door(map);
}
