#include "cub3d.h"

void	move_angle(data_t *data, moves_t *moves)
{
	int	i;

	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_RIGHT))
	{
		i = 0;
		while(i < 500)
		{

			data->p_angle -= 0.0001f;
			if (data->p_angle < 0)
				data->p_angle += (2 * M_PI);
			i++;
		}
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
	{
		i = 0;
		while(i < 500)
		{
			data->p_angle += 0.0001f;
			if (data->p_angle > ((double)2 * M_PI))
				data->p_angle -= (2 * M_PI);
			i++;
		}
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
	}
}

void	player_movement(data_t *data, moves_t *m_d)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_W))
	{
		m_d->next_x = data->player_x + (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_y * m_d->speed);
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
	if (d->map[(int)(m->next_y) / TILE][(int)(m->next_x) / TILE] != '1'
	 && d->map[(int)(m->next_y) / TILE][(int)(m->next_x) / TILE] != ' ')
	{
		d->player_y = m->next_y;
		d->player_x = m->next_x;
		printf("x: %f y: %f char: %c\n", d->player_x, d->player_y ,d->map[(int)((m->next_y) / TILE)][(int)(m->next_x) / TILE]);
	}	
}
// x: 21233.997993 y: 8959.691772
// >>> 21233 / 1280
// 16.58828125
// >>> 8959 / 1280
// 6.99921875

void	hook_handler(void *param)
{
	data_t	*data;
	moves_t	moves;

	moves.update = 0;
	moves.speed = 170;
	data = (data_t *)param;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT_SHIFT))
		moves.speed = 280;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_ESCAPE))
		end_game(data, "Game ended\n");
	player_movement(data, &moves);
	move_angle(data, &moves);
}
