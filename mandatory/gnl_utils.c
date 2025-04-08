/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:00:41 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/08 21:00:42 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

void	ft_bzero(void *s, size_t n)
{
	char			*p;
	unsigned int	x;

	x = 0;
	p = (char *)s;
	while (n > x)
	{
		p[x] = '\0';
		x++;
	}
}

char	*ft_strdup(char *s1, int b)
{
	char	*array;
	int		x;
	int		size;

	x = 0;
	size = ft_strlen(s1) + 1;
	array = malloc(size);
	if (!array)
	{
		if (b)
			return (free(s1), NULL);
		return (NULL);
	}
	while (s1[x])
	{
		array[x] = s1[x];
		x++;
	}
	array[x] = '\0';
	if (b)
		return (free(s1), array);
	return (array);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		x;
	int		y;
	char	*array;

	x = 0;
	y = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2, 0));
	if (!s2)
		return (ft_strdup(s1, 1));
	array = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!array)
		return (free(s1), NULL);
	while (s1[x])
	{
		array[x] = s1[x];
		x++;
	}
	while (s2[y])
		array[x++] = s2[y++];
	array[x] = '\0';
	return (free(s1), array);
}

int	new_line_check(char *str, int *len)
{
	while (*str)
	{
		if (*str == 10)
		{
			*len += 1;
			return (1);
		}
		*len += 1;
		str++;
	}
	return (0);
}
