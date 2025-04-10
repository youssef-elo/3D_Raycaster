/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_helpful_func.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:48:39 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/10 15:44:13 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_strdup_n(char *str, int a, t_map_context_h *map)
{
	char	*array;
	int		x;
	int		size;

	x = 0;
	if (!str)
		return (0);
	size = ft_strlen(str) + 1;
	array = malloc(size);
	if (!array)
		ft_display_error("Error", map);
	while (str[x])
	{
		if (str[x] != '\n' && a == 1)
			array[x] = str[x];
		else if (a == 1)
			array[x] = 0;
		if (a == 0)
			array[x] = str[x];
		x++;
	}
	array[x] = '\0';
	return (array);
}

char	*ft_strjoin_n(char *s1, char *s2, t_map_context_h *map)
{
	int		x;
	int		y;
	char	*array;
	int		size;

	((1) && (x = 0, y = 0));
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup_n(s2, 0, map));
	if (!s2)
		return (ft_strdup_n(s1, 0, map));
	size = (ft_strlen(s1) + ft_strlen(s2));
	array = malloc(size + 1);
	if (!array)
		ft_display_error("Error", map);
	while (s1[x])
	{
		array[x] = s1[x];
		x++;
	}
	while (s2[y])
		array[x++] = s2[y++];
	array[size] = '\0';
	return (free(s1), array);
}

long	ft_atoi(const char *str)
{
	int					x;
	int					sin;
	unsigned long long	res;

	((1) && (x = 0, sin = 1, res = 0));
	if (str[x] == '-' || str[x] == '+' )
	{
		if (str[x] == '-')
			sin *= -1;
		x++;
	}
	while (str[x] >= '0' && str[x] <= '9')
	{
		res = res * 10 + str[x++] - 48;
	}
	return (res * sin);
}
