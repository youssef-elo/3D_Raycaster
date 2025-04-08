#include "cub3d_bonus.h"

void	set_hooks(t_data *data)
{
	mlx_set_cursor_mode(data->mlx_data->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(data->mlx_data->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_key_hook(data->mlx_data->mlx, flashlight, data);
	mlx_cursor_hook(data->mlx_data->mlx, rotate_mouse, data);
	mlx_mouse_hook(data->mlx_data->mlx, open_fire, data);
	mlx_loop_hook(data->mlx_data->mlx, hook_handler, data);
	mlx_loop_hook(data->mlx_data->mlx, draw_3d, data);
	mlx_loop_hook(data->mlx_data->mlx, gun_animation, data);
	data->firing = 0;
	minimap_3d(data);
	gun_frame(data, 0, 0);
}
