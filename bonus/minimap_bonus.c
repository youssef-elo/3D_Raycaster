/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:55 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/08 18:20:56 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	minimap_pixel(int j, int i, t_matrix *matrix, t_data *data)
{
	int	map_x;
	int	map_y;

	matrix->rx = (matrix->dx * matrix->x1) + (matrix->dy * matrix->x2);
	matrix->ry = (matrix->dx * matrix->y1) + (matrix->dy * matrix->y2);
	map_x = (data->player_x + (matrix->rx * 48)) / TILE;
	map_y = (data->player_y + (matrix->ry * 48)) / TILE;
	if (map_x < 0 || map_y < 0 || map_x > data->width - 1
		|| map_y > (data->height - 1))
		put_pixel(data->mlx_data->mini_map, j, i, rgb(108, 108, 108, 255));
	else if (data->map[map_y][map_x] == '1' || data->map[map_y][map_x] == ' ')
		put_pixel(data->mlx_data->mini_map, j, i, rgb(108, 108, 108, 255));
	else if (data->map[map_y][map_x] == '0')
		put_pixel(data->mlx_data->mini_map, j, i, rgb(211, 211, 211, 255));
	else if (data->map[map_y][map_x] == 'D')
		put_pixel(data->mlx_data->mini_map, j, i, rgb(255, 0, 0, 255));
	else if (data->map[map_y][map_x] == 'O')
		put_pixel(data->mlx_data->mini_map, j, i, rgb(150, 0, 0, 255));
}

void	pre_minimap(t_data *data, t_matrix *matrix)
{
	double	angle_new;

	angle_new = (data->p_angle - (M_PI_2));
	if (angle_new < 0)
		angle_new += (2 * M_PI);
	matrix->x1 = cos(-(angle_new));
	matrix->y1 = sin(-(angle_new));
	matrix->x2 = -matrix->y1;
	matrix->y2 = matrix->x1;
}

void	minimap_3d(t_data *data)
{
	int			i;
	int			j;
	t_matrix	matrix;

	i = 0;
	j = 0;
	pre_minimap(data, &matrix);
	matrix.dy = i - M_H_HEIGHT;
	while (i < M_HEIGHT)
	{
		j = 0;
		matrix.dx = -M_H_WIDTH;
		while (j < M_WIDTH)
		{
			if (((matrix.dx * matrix.dx) + (matrix.dy * matrix.dy)) <= (10000))
				minimap_pixel(j, i, &matrix, data);
			j++;
			matrix.dx++;
		}
		i++;
		matrix.dy++;
	}
	draw_filled_disk(data->mlx_data->mini_map, M_H_WIDTH, M_H_HEIGHT, 7);
}
