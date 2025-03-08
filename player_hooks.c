#include "cub3d.h"

void	move_angle(data_t *data, moves_t *moves)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_RIGHT))
	{
		data->view_angle -= (M_PI / 44);
		if (data->view_angle < 0)
			data->view_angle += (2 * M_PI);
		data->dir_x = cos(data->view_angle);
		data->dir_y = sin(data->view_angle);
		moves->update = 1;
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
	{
		data->view_angle += (M_PI / 44);
		if (data->view_angle > ((double)2 * M_PI))
			data->view_angle -= (2 * M_PI);
		data->dir_x = cos(data->view_angle);
		data->dir_y = sin(data->view_angle);
		moves->update = 1;
	}
}

void	player_movement(data_t *data, moves_t *m_d)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_W))
	{
		m_d->next_x = data->player_x + (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_y * m_d->speed);
		m_d->update = 2;
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_S))
	{
		m_d->next_x = data->player_x - (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_y * m_d->speed);
		m_d->update = 2;
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_A))
	{
		m_d->next_x = data->player_x - (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_x * m_d->speed);
		m_d->update = 2;
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_D))
	{
		m_d->next_x = data->player_x + (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_x * m_d->speed);
		m_d->update = 2;
	}
}

void	map_refresh(data_t *d, moves_t *m)
{
	if (m->update == 2)
	{
		if (d->map[(int)((m->next_y) / TILE)][(int)(m->next_x) / TILE] == '0'
			|| d->map[(int)m->next_y / TILE][(int)m->next_x / TILE] == 'P')
		{
			d->player_y = m->next_y;
			d->player_x = m->next_x;
		}
	}
	if (m->update)
	{
		if (!CUBE3D)
			minimap(d, d->mlx_data);
		else
			draw_3d(d);
		// remove for push
	}
}

void	hook_handler(void *param)
{
	data_t	*data;
	moves_t	moves;

	moves.update = 0;
	moves.speed = 3;
	data = (data_t *)param;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT_SHIFT))
		moves.speed = 9;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_ESCAPE))
		exit(0);
	player_movement(data, &moves);
	move_angle(data, &moves);
	map_refresh(data, &moves);
}
