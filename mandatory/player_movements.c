#include "cub3d.h"

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
	if (data->map[(int)m_d->next_y / TILE][(int)m_d->next_x / TILE] == '1'
		|| (data->map[(int)m_d->next_y / TILE][(int)(m_d->next_x + check) / TILE] == '1'))
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
