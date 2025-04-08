#include "cub3d.h"

char	*ft_getline_wnl(char *garbage, int len)
{
	char	*array;
	int		x;

	x = 0;
	if (!garbage)
		return (0);
	array = malloc(len + 1);
	if (!array)
		return (0);
	while (garbage[x])
	{
		if (garbage[x] == 10)
		{
			array[x] = 10;
			break ;
		}
		else
			array[x] = garbage[x];
		x++;
	}
	array[x + 1] = '\0';
	return (array);
}

void	ft_clear(char *garbage)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!garbage)
		return ;
	while (garbage[x])
	{
		if (garbage[x] == 10)
		{
			x++;
			break ;
		}
		x++;
	}
	while (garbage[x])
	{
		garbage[y++] = garbage[x];
		x++;
	}
	ft_bzero(garbage + y, x - y);
}

char	*ft_check_garbege(char *garbage, char *all, int *n)
{
	int	len;

	len = 0;
	*n = new_line_check(garbage, &len);
	if (*n)
	{
		all = ft_getline_wnl(garbage, len);
		ft_clear(garbage);
		return (all);
	}
	else if (*n == 0 && len > 0)
	{
		all = ft_strjoin(all, garbage);
		ft_clear(garbage);
		return (all);
	}
	return (all);
}

char	*ft_getline(char *garbage, char *all, int fd)
{
	int		n;
	int		len;
	char	*holder;

	len = 0;
	while ((read(fd, garbage, BUFFER_SIZE)) > 0)
	{
		n = new_line_check(garbage, &len);
		if (n)
		{
			holder = ft_getline_wnl(garbage, len);
			ft_clear(garbage);
			all = ft_strjoin(all, holder);
			return (free(holder), all);
		}
		else
		{
			all = ft_strjoin(all, garbage);
			ft_clear(garbage);
		}
	}
	return (all);
}

char	*get_next_line(int fd)
{
	static char	garbage[(unsigned int)BUFFER_SIZE + 1];
	char		*all;
	int			n;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (ft_bzero(garbage, BUFFER_SIZE), NULL);
	n = 0;
	all = NULL;
	all = ft_check_garbege(garbage, all, &n);
	if (n && all)
		return (all);
	all = ft_getline(garbage, all, fd);
	if (all)
		return (all);
	return (NULL);
}
