#include "cub3d_bonus.h"

void	move_up(t_data *d, t_moves *m_d)
{
	int	check;

	check = 350;
	if (d->p_angle <= M_PI)
		check = -350;
	if (strchr("D1", d->map[(int)m_d->next_y / TILE][d->map_x])
		|| strchr("1D", d->map[(int)(m_d->next_y + check) / TILE][d->map_x]))
	{
		if (check == -350)
			m_d->next_y = (d->map_y * TILE) + 350;
		else
			m_d->next_y = ((d->map_y * TILE) + ((TILE - 350)));
	}
	check = -350;
	if ((d->p_angle <= (M_PI_2)) || (d->p_angle >= (3 * (M_PI_2))))
		check = 350;
	if (strchr("D1", d->map[d->map_y][(int)m_d->next_x / TILE])
		|| strchr("D1", d->map[d->map_y][(int)(m_d->next_x + check) / TILE]))
	{
		if (check == 350)
			m_d->next_x = (d->map_x * TILE) + (TILE - 350);
		else
			m_d->next_x = (d->map_x * TILE) + 350;
	}
	map_refresh(d, m_d);
}

void	move_down(t_data *d, t_moves *m_d)
{
	int	check;

	check = -350;
	if (d->p_angle < M_PI)
		check = 350;
	if (strchr("D1", d->map[(int)(m_d->next_y) / TILE][d->map_x])
		|| strchr("D1", d->map[(int)(m_d->next_y + check) / TILE][d->map_x]))
	{
		if (check == 350)
			m_d->next_y = (d->map_y * TILE) + ((TILE - 350));
		else
			m_d->next_y = (d->map_y * TILE) + 350;
	}
	check = 350;
	if (d->p_angle <= (M_PI_2) || d->p_angle >= (3 * (M_PI_2)))
		check = -350;
	if (strchr("D1", d->map[d->map_y][(int)(m_d->next_x) / TILE])
		|| strchr("D1", d->map[d->map_y][(int)(m_d->next_x + check) / TILE]))
	{
		if (check == -350)
			m_d->next_x = (d->map_x * TILE) + 350;
		else
			m_d->next_x = (d->map_x * TILE) + (TILE - 350);
	}
	map_refresh(d, m_d);
}

void	move_left(t_data *d, t_moves *m_d)
{
	int	check;

	check = -350;
	if (d->p_angle >= (M_PI_2) && d->p_angle <= (3 * (M_PI_2)))
		check = 350;
	if (strchr("D1", d->map[(int)(m_d->next_y) / TILE][d->map_x])
		|| strchr("D1", d->map[(int)(m_d->next_y + check) / TILE][d->map_x]))
	{
		if (check == 350)
			m_d->next_y = (d->map_y * TILE) + ((TILE - 350));
		else
			m_d->next_y = (d->map_y * TILE) + 350;
	}
	check = 350;
	if (d->p_angle >= 0 && d->p_angle <= M_PI)
		check = -350;
	if (strchr("D1", d->map[d->map_y][(int)(m_d->next_x) / TILE])
		|| strchr("D1", d->map[d->map_y][(int)(m_d->next_x + check) / TILE]))
	{
		if (check == -350)
			m_d->next_x = (d->map_x * TILE) + 350;
		else
			m_d->next_x = (d->map_x * TILE) + (TILE - 350);
	}
	map_refresh(d, m_d);
}

void	move_right(t_data *d, t_moves *m_d)
{
	int	check;

	check = 350;
	if (d->p_angle >= (M_PI_2) && d->p_angle <= (3 * (M_PI_2)))
		check = -350;
	if (strchr("D1", d->map[(int)(m_d->next_y) / TILE][d->map_x])
		|| strchr("D1", d->map[(int)(m_d->next_y + check) / TILE][d->map_x]))
	{
		if (check == -350)
			m_d->next_y = ((d->map_y) * TILE) + 350;
		else
			m_d->next_y = ((d->map_y) * TILE) + ((TILE - 350));
	}
	check = -350;
	if (d->p_angle >= 0 && d->p_angle <= M_PI)
		check = 350;
	if (strchr("D1", d->map[d->map_y][(int)(m_d->next_x) / TILE])
		|| strchr("D1", d->map[d->map_y][(int)(m_d->next_x + check) / TILE]))
	{
		if (check == 350)
			m_d->next_x = (d->map_x * TILE) + (TILE - 350);
		else
			m_d->next_x = (d->map_x * TILE) + 350;
	}
	map_refresh(d, m_d);
}

void	player_movement(t_data *data, t_moves *m_d)
{
	int	moving;

	moving = 0;
	vertical_movement(data, m_d, &moving);
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
		data->walking = 0;
}
