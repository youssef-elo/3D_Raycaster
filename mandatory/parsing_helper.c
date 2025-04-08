/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:05:59 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/08 21:05:57 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	size_of_line(char **str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

char	*ft_get_string(int num)
{
	char	*array;
	int		x;

	x = 0;
	array = malloc(num + 1);
	while (num > x)
	{
		array[x] = ' ';
		x++;
	}
	array[num] = '\0';
	return (array);
}

void	ft_look_cub(char *s, t_map_context_h *map)
{
	int		x;
	int		y;
	char	*s1;

	s1 = ".cub";
	x = ft_strlen(s) - 1;
	y = ft_strlen(s1) - 1;
	while (y >= 0)
	{
		if (s[x] != s1[y])
			ft_display_error("Error\nfile should have .cub extension", map);
		x--;
		y--;
	}
}

int	ft_cmpr(char *s, char *s1)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (s[x] != s1[x])
			return (0);
		x++;
	}
	return (1);
}

int	ft_strcmp(char **s, char *s1)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (ft_cmpr(s[x], s1))
			return (x);
		x++;
	}
	return (-1);
}
