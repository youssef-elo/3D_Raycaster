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
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
	{
		data->p_angle += 0.05f;
		if (data->p_angle > ((double)2 * M_PI))
			data->p_angle -= (2 * M_PI);
		data->dir_x = cos(data->p_angle);
		data->dir_y = sin(data->p_angle);
	}
}

void	move_up(data_t *data, moves_t *m_d)
{
	int	check;

	check = 350;
	if (data->p_angle <= M_PI)
		check = -350;
	if (data->map[(int)m_d->next_y / TILE][data->map_x] == '1'
		|| data->map[(int)(m_d->next_y + check) / TILE][data->map_x] == '1')
	{
		if (check == -350)
			m_d->next_y = (data->map_y * TILE) + 350;
		else
			m_d->next_y = ((data->map_y * TILE) + ((TILE - 350)));
	}
	check = -350;
	if ((data->p_angle <= (M_PI / 2)) || (data->p_angle >= (3 * (M_PI / 2))))
		check = 350;
	if (data->map[data->map_y][(int)m_d->next_x / TILE] == '1'
		|| (data->map[data->map_y][(int)(m_d->next_x + check) / TILE] == '1'))
	{
		if (check == 350)
			m_d->next_x = (data->map_x * TILE) + (TILE - 350);
		else
			m_d->next_x = (data->map_x * TILE) + 350;
	}
	map_refresh(data, m_d);
}

void	move_down(data_t *data, moves_t *m_d)
{
	int	check;

	check = -350;
	if (data->p_angle < M_PI)
		check = 350;
	if (data->map[(int)(m_d->next_y) / TILE][data->map_x] == '1'
		|| data->map[(int)(m_d->next_y + check) / TILE][data->map_x] == '1')
	{
		if (check == 350)
			m_d->next_y = (data->map_y * TILE) + ((TILE - 350));
		else
			m_d->next_y = (data->map_y * TILE) + 350;
	}
	check = 350;
	if (data->p_angle <= (M_PI / 2) || data->p_angle >= (3 * (M_PI / 2)))
		check = -350;
	if (data->map[data->map_y][(int)(m_d->next_x) / TILE] == '1'
		|| (data->map[data->map_y][(int)(m_d->next_x + check) / TILE] == '1'))
	{
		if (check == -350)
			m_d->next_x = (data->map_x * TILE) + 350;
		else
			m_d->next_x = (data->map_x * TILE) + (TILE - 350);
	}
	map_refresh(data, m_d);
}

void	move_left(data_t *data, moves_t *m_d)
{
	int	check;

	check = -350;
	if (data->p_angle >= (M_PI / 2) && data->p_angle <= (3 * (M_PI / 2)))
		check = 350;
	if (data->map[(int)(m_d->next_y) / TILE][data->map_x] == '1'
		|| data->map[(int)(m_d->next_y + check) / TILE][data->map_x] == '1')
	{
		if (check == 350)
			m_d->next_y = (data->map_y * TILE) + ((TILE - 350));
		else
			m_d->next_y = (data->map_y * TILE) + 350;
	}
	check = 350;
	if (data->p_angle >= 0 && data->p_angle <= M_PI)
		check = -350;
	if (data->map[data->map_y][(int)(m_d->next_x) / TILE] == '1'
		|| (data->map[data->map_y][(int)(m_d->next_x + check) / TILE] == '1'))
	{
		if (check == -350)
			m_d->next_x = (data->map_x * TILE) + 350;
		else
			m_d->next_x = (data->map_x * TILE) + (TILE - 350);
	}
	map_refresh(data, m_d);
}

void	move_right(data_t *data, moves_t *m_d)
{
	int	check;

	check = 350;
	if (data->p_angle >= (M_PI / 2) && data->p_angle <= (3 * (M_PI / 2)))
		check = -350;
	if (data->map[(int)(m_d->next_y) / TILE][data->map_x] == '1'
		|| data->map[(int)(m_d->next_y + check) / TILE][data->map_x] == '1')
	{
		if (check == -350)
			m_d->next_y = ((data->map_y) * TILE) + 350;
		else
			m_d->next_y = ((data->map_y) * TILE) + ((TILE - 350));
	}
	check = -350;
	if (data->p_angle >= 0 && data->p_angle <= M_PI)
		check = 350;
	if (data->map[data->map_y][(int)(m_d->next_x) / TILE] == '1'
		|| (data->map[data->map_y][(int)(m_d->next_x + check) / TILE] == '1'))
	{
		if (check == 350)
			m_d->next_x = (data->map_x * TILE) + (TILE - 350);
		else
			m_d->next_x = (data->map_x * TILE) + 350;
	}
	map_refresh(data, m_d);
}

void	player_movement(data_t *data, moves_t *m_d)
{
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_W))
	{
		m_d->next_x = data->player_x + (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_y * m_d->speed);
		move_up(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_S))
	{
		m_d->next_x = data->player_x - (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_y * m_d->speed);
		move_down(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_A))
	{
		m_d->next_x = data->player_x - (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_x * m_d->speed);
		move_left(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_D))
	{
		m_d->next_x = data->player_x + (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_x * m_d->speed);
		move_right(data, m_d);
	}
}

void	map_refresh(data_t *data, moves_t *m_d)
{
	int	map_x;
	int	map_y;

	map_x = (int)(m_d->next_x) / TILE;
	map_y = (int)(m_d->next_y) / TILE;
	if (data->map[map_y][map_x] != '1' && data->map[map_y][map_x] != ' ')
	{
		data->player_y = m_d->next_y;
		data->player_x = m_d->next_x;
		data->map_x = map_x;
		data->map_y = map_y;
	}	
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
