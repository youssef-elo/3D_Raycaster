/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:52 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/08 18:20:53 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_mlx_data		mlx_data;
	map_context_h	p_data;

	parsing(argc, argv, &p_data);
	ft_bzero(&data, sizeof(t_data));
	link_parsing(&data, &p_data, &mlx_data);
	pre_compute(&data);
	free_parsing(&p_data);
	put_images(&data);
	set_hooks(&data);
	mlx_loop(mlx_data.mlx);
}
