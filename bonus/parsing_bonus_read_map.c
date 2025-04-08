/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_read_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:25:35 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/08 20:39:26 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_check_space(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] != 32 && str[x] != '\n')
			return (0);
		x++;
	}
	return (1);
}

void	ft_check_line(char *line, map_context_h *map)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] != '1' && line[x] != '0' && line[x] != 'N'
			&& line[x] != 'W' && line[x] != 'E' && line[x] != 'S'
			&& line[x] != ' ' && line[x] != 'D' && line[x] != '\n')
			ft_display_error("Error", map);
		x++;
	}
}

void	ft_read_map(map_context_h *map, char *line)
{
	static int	start;
	static int	end;

	if (ft_check_space(line) == 0)
		start = 1;
	if (start == 1 && end == 0)
	{
		end = ft_check_space(line);
		ft_check_line(line, map);
		map->array = ft_strjoin_n(map->array, line, map);
	}
	if (end == 1 && ft_check_space(line) == 0)
		ft_display_error("Error", map);
}
