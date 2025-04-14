/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_read_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:27:36 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/13 16:01:15 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_struct(t_map_context_h *map, char **str, int s)
{
	if (s == 0)
		map->north = ft_strdup_n(str[1], 1, map);
	else if (s == 1)
		map->south = ft_strdup_n(str[1], 1, map);
	else if (s == 2)
		map->west = ft_strdup_n(str[1], 1, map);
	else if (s == 3)
		map->east = ft_strdup_n(str[1], 1, map);
	else if (s == 4)
		map->floor_s = ft_strdup_n(str[1], 1, map);
	else if (s == 5)
		map->sky_s = ft_strdup_n(str[1], 1, map);
}

void	ft_read_file(char *line, t_map_context_h *map)
{
	char			**str;
	static int		check[6] = {0, 0, 0, 0, 0, 0};
	static char		*identifier[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int				x;
	int				s;

	((1) && (x = 0, str = NULL));
	str = ft_split(line, 32);
	if (size_of_line(str) >= 3 && map->count < 6)
	{
		if (size_of_line(str) != 3 || ft_strlen(str[2]) != 1 || *str[2] != '\n')
			ft_display_error("Error", map);
	}
	s = ft_strcmp(identifier, *str);
	if (s != -1 && check[s] == 0 && map->count < 6)
	{
		ft_fill_struct(map, str, s);
		map->count++;
		check[s] = 1;
	}
	else if (map->count != 6)
		ft_display_error("Error", map);
	while (str[x])
		free(str[x++]);
	free(str);
}
