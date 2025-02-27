#include "cub3d.h"
void ft_display_error(char *s)
{
    printf("%s\n", s);
    exit(1);
}
char *ft_strdup_n(char *str, int a)
{
	char	*array;
	int		x;
	int		size;

	x = 0;
	size = ft_strlen(str) + 1;
	array = malloc(size);
	if (!array)
		ft_display_error("Error");
	while (str[x])
	{
		if(str[x] != '\n' && a == 1)
			array[x] = str[x];
		else if (a == 1)
			array[x] = 0;
		if(a == 0)
			array[x] = str[x];
		x++;
	}
	array[x] = '\0';
	return array;
}
char	*ft_strjoin_n(char *s1, char *s2)
{
	int		x;
	int		y;
	char	*array;
	int		size;

	x = 0;
	y = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup_n(s2 , 0));
	if (!s2)
		return (ft_strdup_n(s1, 0));
	size = (ft_strlen(s1) + ft_strlen(s2));
	array = malloc(size + 1);
	if (!array)
		return (0);
	while (s1[x])
	{
		array[x] = s1[x];
		x++;
	}
	while (s2[y])
		array[x++] = s2[y++];
	array[size] = '\0';
	free(s1);
	return (array);
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

void	ft_look_cub(char *s)
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
            ft_display_error("Error\nfile should have .cub extension");
		x--;
		y--;
	}
}

int size_of_line(char **str)
{
	int x;

	x = 0;
	while (str[x])
		x++;
	return x;
}

void ft_fill_struct(map_context_h *map, char **str, int s)
{
	if(s == 0)
		map->nort = ft_strdup_n(str[1] , 1);
	else if(s == 1)
		map->south = ft_strdup_n(str[1] , 1);
	else if(s == 2)
		map->west = ft_strdup_n(str[1] , 1);
	else if(s == 3)
		map->east = ft_strdup_n(str[1] , 1);
	else if(s == 4)
		map->flor_s = ft_strdup_n(str[1] , 1);
	else if(s == 5)
		map->sky_s = ft_strdup_n(str[1] , 1);
}

void ft_read_map(map_context_h *map, char * line)
{
	printf("%s", line);
}

void  ft_test(char *line, map_context_h *map)
{
	char **str;
	static int check[6] = {0, 0, 0, 0, 0, 0};
	char *identifier[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};

	if (map->count == 6)
		map->array = ft_strjoin_n(map->array, line);
	str=NULL;
	str = ft_split(line, 32);
	if (size_of_line(str) >= 3 && map->count < 6)
	{
		if (size_of_line(str) != 3 || ft_strlen(str[2]) != 1 || *str[2] != '\n')
			ft_display_error("Error");
	}
	int s = ft_strcmp(identifier, *str);
	if(check[s] == 0 && s != -1 &&  map->count < 6)
	{
		ft_fill_struct(map, str, s);
		map->count++;
		check[s] = 1;
	}
	else if (map->count != 6)
		ft_display_error("Error");
	
	int x = 0;
	while (str[x])
	{
		free(str[x++]);
	}
	free(str);
}
void ft_check_for_error(char *str)
{
	int x;
	int cont;

	x = 0;
	cont = 0;
	while (str[x])
	{
		if((str[x] ==  ',' && str[x] && str[x + 1] == ','))
			ft_display_error("Error");
		if((str[x] < '0' || str[x] > '9') && str[x]!= ',' && str[x])
			ft_display_error("Error");
		if(str[x] ==  ',')
			cont++;
		x++;
	}
	if(cont != 2 || str[0] == ',' || str[ft_strlen(str) - 1] == ',')
		ft_display_error("Error");
	
}

void print_map(map_context_h map)
{
	// printf("%s\n", map.east);
	// printf("%s\n", map.nort);
	// printf("%s\n", map.south);
	// printf("%s\n", map.west);
	// printf("%s\n", map.flor_s);
	// printf("%s\n", map.sky_s);
	// for (int i = 0; i < 3; i++)
	// {
	// 	printf("%d \t", map.flor[i]);
	// }
	// puts("\n");
	// for (int i = 0; i < 3; i++)
	// {
	// 	printf("%d \t\n", map.sky[i]);
	// }
	// puts("\n");
	// printf("%s", map.array);
}
void ft_fill_color_array(map_context_h *map,char **array,int i)
{
	int x;
	x = 0;
	if(i == 1)
	{
		while (array[x])
		{
			map->flor[x] = ft_atoi(array[x]);
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
void ft_convert_color(map_context_h *map, char *str, int i)
{
	char **array;
	int x;

	x = 0;
	ft_check_for_error(str);
	array = ft_split(str, 44);
	if(!array)
		ft_display_error("Error");
	while (array[x])
	{
		if(ft_strlen(array[x]) > 3)
			ft_display_error("Error");
		x++;
	}
	ft_fill_color_array(map, array,i);
	x=0;
	while (array[x])
		free(array[x++]);
	free(array);
	

}
void ft_set_map(map_context_h *map)
{
	map->array = NULL;
	map->west = NULL;
	map->nort = NULL;
	map->east = NULL;
	map->south= NULL;
	map->sky_s = NULL;
	map->flor_s = NULL;
	map->read_map=0;
	map->count = 0;
	map->map=NULL;
}

void parsing(int argc, char **argv)
{
	int i;
	int fd;
	char *line;
	map_context_h map;

	i = 0;
	ft_set_map(&map);
	if(argc != 2)
		ft_display_error("Error");
	ft_look_cub(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_display_error("Error");
	line = get_next_line(fd);
	while (line)
	{
		if(*line != '\n' && map.count < 6)
			ft_test(line, &map);
		else if(map.count == 6)
		{
			ft_read_map(&map, line);
		}
		
		free(line);
		line = get_next_line(fd);
	}
	
	ft_convert_color(&map, map.flor_s, 1);
	ft_convert_color(&map, map.sky_s, 0);
	print_map(map);
	exit(1);
}