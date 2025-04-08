/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:23:57 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/08 19:24:48 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing(int argc, char **argv, map_context_h *map)
{
	int		fd;
	char	*line;

	ft_set_map(map);
	if (argc != 2)
		ft_display_error("Error\nRequired arguments : ./cub3d map_name", map);
	ft_look_cub(argv[1], map);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_display_error("Error\ncant open file", map);
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n' && map->count < 6)
			ft_read_file(line, map);
		else if (map->count == 6)
			ft_read_map(map, line);
		free(line);
		line = get_next_line(fd);
	}
	ft_convert_color(map, map->floor_s, 1);
	ft_convert_color(map, map->sky_s, 0);
	ft_double_array(map);
}
