/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_convert_color.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:00:58 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/08 20:39:00 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_check_for_error(char *str, map_context_h *map)
{
	int	x;
	int	cont;

	x = 0;
	cont = 0;
	while (str[x])
	{
		if ((str[x] == ',' && str[x] && str[x + 1] == ','))
			ft_display_error("Error", map);
		if ((str[x] < '0' || str[x] > '9') && str[x] != ',' && str[x])
			ft_display_error("Error", map);
		if (str[x] == ',')
			cont++;
		x++;
	}
	if (cont != 2 || str[0] == ',' || str[ft_strlen(str) - 1] == ',')
		ft_display_error("Error", map);
}

void	ft_fill_color_array(map_context_h *map, char **array, int i)
{
	int	x;

	x = 0;
	if (i == 1)
	{
		while (array[x])
		{
			map->floor[x] = ft_atoi(array[x]);
			x++;
		}
	}
	else
	{
		while (array[x])
		{
			map->sky[x] = ft_atoi(array[x]);
			x++;
		}
	}
}

void	ft_convert_color(map_context_h *map, char *str, int i)
{
	char	**array;
	int		x;

	x = 0;
	ft_check_for_error(str, map);
	array = ft_split(str, 44);
	if (!array)
		ft_display_error("Error", map);
	while (array[x])
	{
		if (ft_strlen(array[x]) > 3)
			ft_display_error("Error", map);
		x++;
	}
	ft_fill_color_array(map, array, i);
	x = 0;
	while (array[x])
		free(array[x++]);
	free(array);
}
