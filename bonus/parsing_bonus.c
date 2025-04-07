#include "cub3d_bonus.h"

int size_of_line(char **str)
{
	int x;

	x = 0;
	while (str[x])
		x++;
	return x;
}

 void ft_free_map(map_context_h *map)
{
	int x;

	x = 0;
	free(map->south);
	free(map->north);
	free(map->east);
	free(map->west);
	free(map->floor_s);
	free(map->sky_s);
	free(map->array);
	if(!map->map)
		return;
	x = size_of_line(map->map) - 1;
	while (x >= 0)
		free(map->map[x--]);
	free(map->map);
}

void ft_display_error(char *s, map_context_h *map)
{
	ft_free_map(map);
    printf("%s\n", s);
    exit(1);
}
int ft_check_space(char *str)
{
	int x;

	x = 0;
	while(str[x])
	{
		if(str[x] != 32 && str[x] != '\n')
			return 0;
		x++;
	}
	return 1;
}
char *ft_strdup_n(char *str, int a, map_context_h *map)
{
	char	*array;
	int		x;
	int		size;

	x = 0;
	size = ft_strlen(str) + 1;
	array = malloc(size);
	if (!array)
		ft_display_error("Error", map);
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
char	*ft_strjoin_n(char *s1, char *s2, map_context_h *map)
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
		return (ft_strdup_n(s2 , 0, map));
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

void	ft_look_cub(char *s, map_context_h *map)
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



void ft_fill_struct(map_context_h *map, char **str, int s)
{
	if(s == 0)
		map->north = ft_strdup_n(str[1] , 1, map);
	else if(s == 1)
		map->south = ft_strdup_n(str[1] , 1, map);
	else if(s == 2)
		map->west = ft_strdup_n(str[1] , 1, map);
	else if(s == 3)
		map->east = ft_strdup_n(str[1] , 1, map);
	else if(s == 4)
		map->floor_s = ft_strdup_n(str[1] , 1, map);
	else if(s == 5)
		map->sky_s = ft_strdup_n(str[1] , 1, map);
}
void	ft_check_line(char *line, map_context_h *map)
{
	int x;

	x = 0;
	while (line[x])
	{
		if (line[x] != '1' && line[x] != '0' && line[x] != 'N' && line[x] != 'W' && line[x] != 'E' && line[x] != 'S' && line[x] != 'D' && line[x] != ' ' && line[x] != '\n')
			ft_display_error("Error", map);
		x++;
	}
	
}

void ft_read_map(map_context_h *map, char *line)
{
	static int start;
	static int end;

	if (ft_check_space(line) == 0) 
		start = 1;
	if(start == 1 && end == 0)
	{
		end = ft_check_space(line);
		ft_check_line(line, map);
		map->array = ft_strjoin_n(map->array, line, map);
	}
	if (end == 1 && ft_check_space(line) == 0)
		ft_display_error("Error", map);
}

void  ft_test(char *line, map_context_h *map)
{
	char **str;
	static int check[6] = {0, 0, 0, 0, 0, 0};
	char *identifier[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int x;

	x = 0;
	str = NULL;
	str = ft_split(line, 32);
	if (size_of_line(str) >= 3 && map->count < 6)
	{
		if (size_of_line(str) != 3 || ft_strlen(str[2]) != 1 || *str[2] != '\n')
			ft_display_error("Error", map);
	}
	int s = ft_strcmp(identifier, *str);
	if(check[s] == 0 && s != -1 &&  map->count < 6)
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
void ft_check_for_error(char *str, map_context_h *map)
{
	int x;
	int cont;

	x = 0;
	cont = 0;
	while (str[x])
	{
		if((str[x] ==  ',' && str[x] && str[x + 1] == ','))
			ft_display_error("Error", map);
		if((str[x] < '0' || str[x] > '9') && str[x]!= ',' && str[x])
			ft_display_error("Error", map);
		if(str[x] ==  ',')
			cont++;
		x++;
	}
	if(cont != 2 || str[0] == ',' || str[ft_strlen(str) - 1] == ',')
		ft_display_error("Error", map);
	
}

// 
void ft_fill_color_array(map_context_h *map,char **array,int i)
{
	int x;
	x = 0;
	if(i == 1)
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
void ft_convert_color(map_context_h *map, char *str, int i)
{
	char **array;
	int x;

	x = 0;
	ft_check_for_error(str, map);
	array = ft_split(str, 44);
	if(!array)
		ft_display_error("Error", map);
	while (array[x])
	{
		if(ft_strlen(array[x]) > 3)
			ft_display_error("Error", map);
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
	map->north = NULL;
	map->east = NULL;
	map->south= NULL;
	map->sky_s = NULL;
	map->floor_s = NULL;
	map->read_map=0;
	map->count = 0;
	map->map=NULL;
}
char *ft_get_string(int num)
{
	char *array;
	int x;

	x = 0;
	array = malloc(num+1);
	while (num > x)
	{
		array[x] = ' ';
		x++;
	}
	array[num] = '\0';
	return array;
}

void	ft_adjust_map_size(map_context_h *map)
{
	int x;
	int y;
	int max;
	char *array;

	((1) && (x = 0, max = 0, y = 0));
	while (map->map[x])
	{
		if (max < ft_strlen(map->map[x]))
			max = ft_strlen(map->map[x]);
		x++;
	}
	x = 0;
	while (map->map[x])
	{
		if (max > ft_strlen(map->map[x]))
		{
			array = ft_get_string(max - ft_strlen(map->map[x]));
			map->map[x] = ft_strjoin_n(map->map[x], array, map);
			free(array);
		}
		while (map->map[x][y])
		{
			if(map->map[x][y] == ' ')
				map->map[x][y] = ' ';
			y++;
		}
		x++;
		y = 0;
	}
}
void ft_check_first_Last_line(map_context_h *map)
{
	int x;
	int y;
	int i;

	x = 0;
	y = 0;
	i = 0;

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
	while (i <= x)
	{
		if ((map->map[i][0] != '1' && map->map[i][0] != ' ')  || (map->map[i][ft_strlen(map->map[0] )- 1] != ' ' && map->map[i][ft_strlen(map->map[0])-1] != '1'))
			ft_display_error("Error", map);
		i++;
	}
		
}
void ft_check_player(map_context_h *map)
{
	int x;
	int y;
	int check;

	check = 0;
	x = 0;
	y = 0;

	while (map->map[x])
	{
		
		while (map->map[x][y])
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'W' || map->map[x][y] == 'E' || map->map[x][y] == 'S')
				check ++;
			y++;
		}
		x++;
		y = 0;
	}
	if(check != 1)
		ft_display_error("Error", map);
}

void ft_valid_path(map_context_h *map)
{
	int x;
	int y;

	x = 0;
	y = 0;

	ft_check_first_Last_line(map);
	ft_check_player(map);


	while (map->map[x])
	{
		
		while (map->map[x][y])
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'W' || map->map[x][y] == 'E' || map->map[x][y] == 'S' || map->map[x][y] == '0')
			{
				if((map->map[x][y + 1] == ' '|| !map->map[x][y + 1])  || map->map[x][y - 1] == ' ' || !map->map[x][y - 1])
					ft_display_error("Error", map);
				else if((map->map[x + 1][y] == ' ' ||  !map->map[x + 1][y]) || (map->map[x - 1][y] == ' ' ||  !map->map[x - 1][y]))
					ft_display_error("Error", map);
			}
			y++;
		}
		x++;
		y = 0;
	}
	
}
void ft_valid_door(map_context_h *map)
{
	int x = 0;
	int y = 0;
	while (map->map[x])
	{
		while (map->map[x][y])
		{
			if(map->map[x][y] == 'D')
			{
				if(map->map[x][y - 1] != '1' || map->map[x][y + 1] != '1'){
					if(map->map[x - 1][y] != '1' || map->map[x + 1][y] != '1')
					ft_display_error("Error", map);
				}
			}
			y++;
		}
		x++;
		y = 0;
	}
	
}

void ft_double_array(map_context_h *map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	map->map = ft_split(map->array, 10);
	if (!map->map)
		ft_display_error("Error", map);
	ft_adjust_map_size(map);
	ft_valid_path(map);
	ft_valid_door(map);
}


void parsing(int argc, char **argv, map_context_h *map)
{
	int i;
	int fd;
	char *line;

	i = 0;
	ft_set_map(map);
	if(argc != 2)
		ft_display_error("Error\nRequired arguments : ./cub3d map_name", map);
	ft_look_cub(argv[1], map);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_display_error("Error\ncant open file", map);
	line = get_next_line(fd);
	int k = 0;
	while (line)
	{
		if(*line != '\n' && map->count < 6)
			ft_test(line, map);
		else if(map->count == 6)
			ft_read_map(map, line);
		free(line);
		line = get_next_line(fd);
	}
	ft_convert_color(map, map->floor_s, 1);
	ft_convert_color(map, map->sky_s, 0);
	ft_double_array(map);
	// print_map(*map);
}
// void print_map(map_context_h map)
// {
// 	// printf("%s\n", map.east);
// 	// printf("%s\n", map.nort);
// 	// printf("%s\n", map.south);
// 	// printf("%s\n", map.west);
// 	// printf("%s\n", map.floor_s);
// 	// printf("%s\n", map.sky_s);
// 	// for (int i = 0; i < 3; i++)
// 	// {
// 	// 	printf("%d \t", map.floor[i]);
// 	// }
// 	// puts("\n");
// 	// for (int i = 0; i < 3; i++)
// 	// {
// 	// 	printf("%d \t\n", map.sky[i]);
// 	// }
// 	// puts("\n");
// 	// printf("\n%s", map.array);
// }


// free(p_data.south);
// free(p_data.north);
// free(p_data.east);
// free(p_data.west);
// free(p_data.floor_s);
// free(p_data.sky_s);
// free(p_data.array);
// free(p_data.map);