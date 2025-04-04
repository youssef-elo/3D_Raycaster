#include "cub3d_bonus.h"

void flashlight(struct mlx_key_data keydata, void *param)
{
	data_t *data;

	data = (data_t *)param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
	{
		if (data->fog_start == FOG_START)
		{
			data->fog_start = FOG_START_FLASH;
			data->fog_m = MAX_VIEW_FLASH;
		}
		else
		{
			data->fog_start = FOG_START;
			data->fog_m = MAX_VIEW;
		}
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		data->reload = 1;
	}
}

// void load_gun(data_t *data)
// {
// 	// int i;
// 	int j;
// 	char str[30];
// 	int x;
// 	int y;
// 	int n;

// 	mlx_texture_t *tex;


// 	// i = 1;
// 	j = 1;
// 	n = 3;
// 	data->walking = 1;
// 	data->mlx_data->gun = malloc(sizeof(mlx_image_t *) * 44);
// 	for ( int i = 0; i < 44; i++, j+=5)
// 	{
// 		if ( j > 9)
//             n = 2;
//         if (j > 99) 
//             n = 1;
// 		sprintf(str, "render/%.*s%d.png",n , "000", j);
// 		tex = mlx_load_png(str);
// 		data->mlx_data->gun[i] = mlx_texture_to_image(data->mlx_data->mlx, tex);
// 		mlx_delete_texture(tex);
// 		if (i == 0)
// 		{
// 			x = (WIDTH_3D / 2) - 350;
// 			y = HEIGHT_3D  - data->mlx_data->gun[0]->height ;
// 		}
// 		mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->gun[i], x, y);
// 		data->mlx_data->gun[i]->instances->enabled = false;
// 	}
// 	gun_animation(data);
// }
// void load_gun_reload(data_t *data)
// {
// 	// int i;
// 	int j;
// 	char str[30];
// 	int x;
// 	int y;
// 	int n;

// 	mlx_texture_t *tex;


// 	// i = 1;
// 	j = 1;
// 	n = 3;
// 	data->walking = 1;
// 	data->mlx_data->reload = malloc(sizeof(mlx_image_t *) * 44);
// 	for ( int i = 0; i < 44; i++, j+=5)
// 	{
// 		if ( j > 9)
//             n = 2;
//         if (j > 99) 
//             n = 1;
// 		sprintf(str, "reload/%.*s%d.png",n , "000", j);
// 		tex = mlx_load_png(str);
// 		data->mlx_data->reload[i] = mlx_texture_to_image(data->mlx_data->mlx, tex);
// 		mlx_delete_texture(tex);
// 		if (i == 0)
// 		{
// 			x = (WIDTH_3D / 2) - 600;
// 			y = HEIGHT_3D  - data->mlx_data->reload[0]->height ;
// 		}
// 		mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->reload[i], x, y);
// 		data->mlx_data->reload[i]->instances->enabled = false;
// 	}
// }

void gun_frame(data_t *data, int x, int y)
{
	int i;
	int j;
	int k;
	int v_index;
	int g_index;

	i = 0;
	j = y * GUN_H;
	k = x * GUN_W;
	while(i < GUN_H)
	{
		g_index = (((j) * data->mlx_data->gun_sheet->width) + (k));
		v_index = (i * data->mlx_data->gun_view->width);
		memcpy((uint32_t *) data->mlx_data->gun_view->pixels + v_index, (uint32_t *) data->mlx_data->gun_sheet->pixels + g_index, GUN_W * 4);
		i++;
		j++;
	}
}
void reload_frame(data_t *data, int x, int y)
{
	int i;
	int j;
	int k;
	int v_index;
	int g_index;

	i = 0;
	j = y * RELOAD_H;
	k = x * RELOAD_W;
	while(i < RELOAD_H)
	{
		g_index = (((j) * data->mlx_data->reload_sheet->width) + (k));
		v_index = (i * data->mlx_data->reload_view->width);
		memcpy((uint32_t *) data->mlx_data->reload_view->pixels + v_index, (uint32_t *) data->mlx_data->reload_sheet->pixels + g_index, RELOAD_W * 4);
		i++;
		j++;
	}
}
void fire_frame(data_t *data, int x, int y)
{
	int i;
	int j;
	int k;
	int v_index;
	int g_index;

	i = 0;
	j = y * FIRE_H;
	k = x * FIRE_W;
	while(i < FIRE_H)
	{
		g_index = (((j) * data->mlx_data->fire_sheet->width) + (k));
		v_index = (i * data->mlx_data->fire_view->width);
		memcpy((uint32_t *) data->mlx_data->fire_view->pixels + v_index, (uint32_t *) data->mlx_data->fire_sheet->pixels + g_index, FIRE_W * 4);
		i++;
		j++;
	}
}

void	gun_animation(void *param)
{
	static int i;
	static int first;
	static mlx_image_t *pre_gun;
	static int r;
	static int f;
	static double last_time;
	double current_time;

	data_t *data;
	data = (data_t *)param;
	if (!first)
	{
		last_time = mlx_get_time();
		first = 1;
	}
	current_time = mlx_get_time();
	if (current_time - last_time >= 0.0001f && !data->reload)
	{
		if (data->firing || (!data->firing && f != 0))
		{
			puts("fire");
			if (f == 0)
			{
				data->mlx_data->gun_view->instances[0].enabled = false;
				data->mlx_data->fire_view->instances[0].enabled = true;
			}
			fire_frame(data, f % 6, f / 6);
			f++;
			if (f == 30)
			{
				// data->firing = 0;
				f = 0;
				data->mlx_data->gun_view->instances[0].enabled = true;
				data->mlx_data->fire_view->instances[0].enabled = false;
				i = 0;
			last_time = mlx_get_time();
			}
			last_time = mlx_get_time();
		}
		
	}
	current_time = mlx_get_time();
	if (current_time - last_time >= 0.035f)
	{
			puts("in?");
		if (data->walking && !data->reload && (!data->firing && f == 0))
		{
			if (i == 44)
				i = 0;
			gun_frame(data, i % 8, i / 8);
			i++;
			last_time = mlx_get_time();
		}
		if (data->reload && (!data->firing && f == 0))
		{
			if ( r == 0)
			{
				data->mlx_data->reload_view->instances[0].enabled = true;
				data->mlx_data->gun_view->instances[0].enabled = false;
			}
			reload_frame(data, r % 8, r / 8);
			r++;
			if (r == 44)
			{
				data->reload = 0;
				r = 0;
				data->mlx_data->gun_view->instances[0].enabled = true;
				data->mlx_data->reload_view->instances[0].enabled = false;
				i = 0;
			}
			last_time = mlx_get_time();
		}
	}
}

void rotate_mouse(double xpos, double ypos, void* param)
{
	double dx;
	double angle;
	data_t *data;

	data = (data_t *)param;
	dx = WIDTH_3D / 2 - xpos;
	angle = dx * ROTATION_FACTOR;
	data->p_angle += angle;
	if (data->p_angle > ((double)2 * M_PI))
			data->p_angle -= (2 * M_PI);
	if (data->p_angle < 0)
		data->p_angle += (2 * M_PI);
	data->dir_x = cos(data->p_angle);
	data->dir_y = sin(data->p_angle);
	mlx_set_mouse_pos(data->mlx_data->mlx, WIDTH_3D / 2, HEIGHT_3D / 2);
}

void	open_fire(mouse_key_t butt, action_t act, modifier_key_t mods, void* p)
{
	data_t *data;

	data = (data_t *)p;
	if (butt == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS)
		data->firing = 1;
	if (butt == MLX_MOUSE_BUTTON_LEFT && act == MLX_RELEASE)
	{
		data->firing = 0;
	}
}


int	main(int argc, char **argv){
	data_t			data;
	mlx_data_t		mlx_data;
	map_context_h	p_data;

	parsing(argc , argv, &p_data);
	ft_bzero(&data, sizeof(data_t));
	link_parsing(&data, &p_data, &mlx_data);
	pre_compute(&data);
	free_parsing(&p_data);
	mlx_set_cursor_mode(data.mlx_data->mlx, MLX_MOUSE_DISABLED);
	draw_filled_disk(data.mlx_data->mini_map, data.mlx_data->mini_map->width / 2, data.mlx_data->mini_map->height / 2, 104);
	mlx_image_to_window(mlx_data.mlx, mlx_data.view_3d,  0, 0);
	mlx_image_to_window(mlx_data.mlx, mlx_data.mini_map,  0, HEIGHT_3D - data.mlx_data->mini_map->height);
	mlx_image_to_window(mlx_data.mlx, mlx_data.gun_view,  (WIDTH_3D / 2) - 350, HEIGHT_3D - GUN_H);
	mlx_image_to_window(mlx_data.mlx, mlx_data.reload_view,   (WIDTH_3D / 2) - 600, HEIGHT_3D - RELOAD_H);
	mlx_image_to_window(mlx_data.mlx, mlx_data.fire_view,   (WIDTH_3D / 2) - 350, HEIGHT_3D - FIRE_H);
	minimap_3d(&data);
	data.firing = 0;
	mlx_set_mouse_pos(data.mlx_data->mlx, WIDTH_3D / 2, HEIGHT_3D / 2);
	// gun_animation(&data);
	data.mlx_data->gun_sheet = mlx_load_png("render/gunsheet.png");
	data.mlx_data->reload_sheet = mlx_load_png("reload/reloadsheet.png");
	data.mlx_data->fire_sheet = mlx_load_png("fire/firesheet.png");
	gun_frame(&data, 0 ,0);
	mlx_key_hook(data.mlx_data->mlx, flashlight, &data);
	mlx_cursor_hook(data.mlx_data->mlx, rotate_mouse, &data);
	mlx_mouse_hook(data.mlx_data->mlx, open_fire, &data);
	mlx_loop_hook(mlx_data.mlx, hook_handler, &data);
	mlx_loop_hook(mlx_data.mlx, draw_3d, &data);
	mlx_loop_hook(mlx_data.mlx, gun_animation, &data);
	mlx_loop(mlx_data.mlx);
}
