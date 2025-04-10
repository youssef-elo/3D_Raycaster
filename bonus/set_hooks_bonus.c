/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:21:12 by yel-ouaz          #+#    #+#             */
/*   Updated: 2025/04/10 14:11:11 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_hooks(t_data *data)
{
	mlx_set_cursor_mode(data->mlx_data->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(data->mlx_data->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_key_hook(data->mlx_data->mlx, flashlight, data);
	mlx_cursor_hook(data->mlx_data->mlx, rotate_mouse, data);
	mlx_mouse_hook(data->mlx_data->mlx, fire, data);
	mlx_loop_hook(data->mlx_data->mlx, hook_handler, data);
	mlx_loop_hook(data->mlx_data->mlx, draw_3d, data);
	mlx_loop_hook(data->mlx_data->mlx, gun_animation, data);
	mlx_close_hook(data->mlx_data->mlx, cross_close, data);
	data->firing = 0;
	minimap_3d(data);
	gun_frame(data, 0, 0);
}
