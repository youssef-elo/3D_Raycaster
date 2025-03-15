#include "cub3d.h"

void	move_angle(data_t *data, moves_t *moves)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_RIGHT))
	{
		data->p_angle -= 0.05f;
		if (data->p_angle < 0)
			data->p_angle += (2 * M_PI);
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
		draw_3d(data);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
	{
		data->p_angle += 0.05f;
		if (data->p_angle > ((double)2 * M_PI))
			data->p_angle -= (2 * M_PI);
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
		draw_3d(data);
	}
}

void	player_movement(data_t *data, moves_t *m_d)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_W))
	{
		m_d->next_x = data->player_x + (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_y * m_d->speed);
		map_refresh(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_S))
	{
		m_d->next_x = data->player_x - (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_y * m_d->speed);
		map_refresh(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_A))
	{
		m_d->next_x = data->player_x - (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_x * m_d->speed);
		map_refresh(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_D))
	{
		m_d->next_x = data->player_x + (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_x * m_d->speed);
		map_refresh(data, m_d);
	}
}

void	map_refresh(data_t *d, moves_t *m)
{
	if (d->map[(int)((m->next_y) / TILE)][(int)(m->next_x) / TILE] != '1' &&
		d->map[(int)((m->next_y) / TILE)][(int)(m->next_x) / TILE] != ' ')
	{
		d->player_y = m->next_y;
		d->player_x = m->next_x;
		draw_3d(d);
	}	
}

void	hook_handler(void *param)
{
	data_t	*data;
	moves_t	moves;

	moves.update = 0;
	moves.speed = 66 * 4;
	data = (data_t *)param;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT_SHIFT))
		moves.speed = 80 * 4;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_ESCAPE))
		exit(0);
	player_movement(data, &moves);
	move_angle(data, &moves);
}
