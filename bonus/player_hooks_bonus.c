#include "cub3d_bonus.h"

void	move_angle(data_t *data, moves_t *moves)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_RIGHT))
	{
		data->p_angle -= 0.05f;
		if (data->p_angle < 0)
			data->p_angle += (2 * M_PI);
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
		minimap_3d(data);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
	{
		data->p_angle += 0.05f;
		if (data->p_angle > ((double)2 * M_PI))
			data->p_angle -= (2 * M_PI);
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
		minimap_3d(data);
	}
}

void	player_movement(data_t *data, moves_t *m_d)
{
	// data->walking = 0;
	int moving = 0;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_SPACE))
		printf("%f\n", data->p_angle);	
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_W))
	{
		m_d->next_x = data->player_x + (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_y * m_d->speed);
		moving = 1;
		data->walking = 1;
		move_up(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_S))
	{
		m_d->next_x = data->player_x - (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_y * m_d->speed);
		data->walking = 1;
		moving = 1;
		move_down(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_A))
	{
		m_d->next_x = data->player_x - (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_x * m_d->speed);
		data->walking = 1;
		moving = 1;
		move_left(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_D))
	{
		m_d->next_x = data->player_x + (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_x * m_d->speed);
		data->walking = 1;
		moving = 1;
		move_right(data, m_d);
	}
	if (!moving)
	{
		data->walking = 0;
	}
}

void	map_refresh(data_t *data, moves_t *m_d)
{
	int	map_x;
	int	map_y;
	double pre_y;
	int changed;

	changed = 0;
	pre_y = data->player_y;
	map_x = (int)(m_d->next_x) / TILE;
	map_y = (int)(m_d->next_y) / TILE;
	if ( data->map[map_y][data->map_x] == '0')
	{
		data->player_y = m_d->next_y;
		data->map_y = map_y;
		changed = 1;
	}
	if (data->map[data->map_y][map_x] == '0')
	{
		data->player_x = m_d->next_x;
		data->map_x = map_x;
		changed = 1;
	}
	if (data->map[data->map_y][data->map_x] == '1')
	{
		data->player_y = pre_y;
		data->map_y = pre_y / TILE;
		changed = 1;
	}
	if ( changed)
		minimap_3d(data);
}

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
