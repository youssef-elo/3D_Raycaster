/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:22:36 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/16 18:42:49 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_mlx_data		mlx_data;
	t_map_context_h	p_data;

	parsing(argc, argv, &p_data);
	ft_bzero(&data, sizeof(t_data));
	link_parsing(&data, &p_data, &mlx_data);
	pre_compute(&data);
	free_parsing(&p_data);
	mlx_image_to_window(mlx_data.mlx, mlx_data.view_3d, 0, 0);
	mlx_key_hook(data.mlx_data->mlx, flashlight, &data);
	mlx_loop_hook(mlx_data.mlx, hook_handler, &data);
	mlx_loop_hook(mlx_data.mlx, draw_3d, &data);
	mlx_close_hook(data.mlx_data->mlx, cross_close, &data);
	mlx_loop(mlx_data.mlx);
}
