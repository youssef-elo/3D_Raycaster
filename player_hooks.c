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
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_SPACE))
		printf("%f\n", data->p_angle);
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_W))
	{
		m_d->next_x = data->player_x + (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_y * m_d->speed);

		
		if (data->map[(int)(m_d->next_y) / TILE][(int)(data->player_x) / TILE] == '1' || data->map[(int)(m_d->next_y + (350 * ((data->p_angle <= M_PI)? - 1 : 1))) / TILE][(int)(data->player_x) / TILE] == '1')
		{
			if ((data->p_angle < M_PI))
				m_d->next_y = (((int)data->player_y / TILE) * TILE) + 350;
			else
				m_d->next_y = ((((int)data->player_y / TILE) * TILE) + ((TILE - 350)));
		}
		if (data->map[(int)(data->player_y) / TILE][(int)(m_d->next_x) / TILE] == '1' || (data->map[(int)(data->player_y ) / TILE][(int)(m_d->next_x + (350 * ((data->p_angle <= (M_PI / 2)) || (data->p_angle >= (3 * ( M_PI / 2)))? 1 : -1))) / TILE] == '1'))
		{
			printf("in\n");
			if ((data->p_angle < (M_PI / 2)) || (data->p_angle > (3 * ( M_PI / 2))))
				m_d->next_x = (((int)data->player_x / TILE) * TILE) + (TILE - 350); 
			else
				m_d->next_x = (((int)data->player_x / TILE) * TILE) + 350;
		}
		map_refresh(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_S))
	{
		m_d->next_x = data->player_x - (data->dir_x * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_y * m_d->speed);
		if (data->map[(int)(m_d->next_y) / TILE][(int)(data->player_x) / TILE] == '1' || data->map[(int)(m_d->next_y + (350 * ((data->p_angle < M_PI)? 1 : -1))) / TILE][(int)(data->player_x) / TILE] == '1')
		{
			if ((data->p_angle < M_PI))
				m_d->next_y = (((int)data->player_y / TILE) * TILE) + ((TILE - 350));
			else
				m_d->next_y = (((int)data->player_y / TILE) * TILE) + 350;
		}
		
		if (data->map[(int)(data->player_y) / TILE][(int)(m_d->next_x) / TILE] == '1'
			|| (data->map[(int)(data->player_y ) / TILE][(int)(m_d->next_x + (350 * ((data->p_angle <= (M_PI / 2)) || (data->p_angle >= (3 * ( M_PI / 2)))? -1 : 1))) / TILE] == '1'))
		{
			if ((data->p_angle < (M_PI / 2)) || (data->p_angle > (3 * ( M_PI / 2))))
				m_d->next_x = (((int)data->player_x / TILE) * TILE) + 350;
			else
				m_d->next_x = (((int)data->player_x / TILE) * TILE) + (TILE - 350); 
		}
		map_refresh(data, m_d);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_A))
	{
		m_d->next_x = data->player_x - (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y - (data->dir_x * m_d->speed);
		if (data->map[(int)(m_d->next_y) / TILE][(int)(data->player_x) / TILE] == '1' 
			|| data->map[(int)(m_d->next_y + (350 * (((data->p_angle >= (M_PI / 2) && data->p_angle <= (3 * (M_PI / 2))))? 1 : -1))) / TILE][(int)(data->player_x) / TILE] == '1')
		{
			if ((data->p_angle >= (M_PI / 2) && data->p_angle <= (3 * (M_PI / 2))))
				m_d->next_y = (((int)data->player_y / TILE) * TILE) + ((TILE - 350));
			else
				m_d->next_y = (((int)data->player_y / TILE) * TILE) + 350;
		}
		if (data->map[(int)(data->player_y) / TILE][(int)(m_d->next_x) / TILE] == '1' 
			|| (data->map[(int)(data->player_y ) / TILE][(int)(m_d->next_x + (350 * ((data->p_angle >= 0 && data->p_angle <= M_PI) ? -1 : 1))) / TILE] == '1'))
		{
			printf("in\n");
			if (data->p_angle >= 0 && data->p_angle <= M_PI)
				m_d->next_x = (((int)data->player_x / TILE) * TILE) + 350;
			else
				m_d->next_x = (((int)data->player_x / TILE) * TILE) + (TILE - 350); 
		}
		map_refresh(data, m_d);      
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_D))
	{
		m_d->next_x = data->player_x + (data->dir_y * m_d->speed);
		m_d->next_y = data->player_y + (data->dir_x * m_d->speed);
		if (data->map[(int)(m_d->next_y) / TILE][(int)(data->player_x) / TILE] == '1' || data->map[(int)(m_d->next_y + (350 * (((data->p_angle >= (M_PI / 2) && data->p_angle <= (3 * (M_PI / 2))))? -1 : 1))) / TILE][(int)(data->player_x) / TILE] == '1')
		{
			if ((data->p_angle >= (M_PI / 2) && data->p_angle <= (3 * (M_PI / 2))))
				m_d->next_y = (((int)data->player_y / TILE) * TILE) + 350;
			else
				m_d->next_y = (((int)data->player_y / TILE) * TILE) + ((TILE - 350));
		}
		if (data->map[(int)(data->player_y) / TILE][(int)(m_d->next_x) / TILE] == '1' 
			|| (data->map[(int)(data->player_y ) / TILE][(int)(m_d->next_x + (350 * (((data->p_angle >= 0 && data->p_angle <= M_PI))? 1 : -1))) / TILE] == '1'))
		{
			printf("in\n");
			if (data->p_angle >= 0 && data->p_angle <= M_PI)
				m_d->next_x = (((int)data->player_x / TILE) * TILE) + (TILE - 350);
			else
				m_d->next_x = (((int)data->player_x / TILE) * TILE) + 350;
		}
		map_refresh(data, m_d);
	}
}

void	map_refresh(data_t *data, moves_t *m_d)
{

	// if (m->next_y < (TILE + 250))
	// 	m->next_y =  TILE + 250;
	// if (m->next_y > (((d->height - 1) * TILE) - 150))
	// 	m->next_y = (((d->height - 1) * TILE) - 150);

	// if ( m->next_x < TILE + 150)
	// 	m->next_x = TILE + 150;
	// if ( m->next_x < (((d->width - 1) * TILE) - 150))
	// 	m->next_x = (((d->width - 1) * TILE) - 150);
	if (data->map[(int)(m_d->next_y) / TILE][(int)(m_d->next_x) / TILE] != '1'
	 && data->map[(int)(m_d->next_y) / TILE][(int)(m_d->next_x) / TILE] != ' ')
	{
		data->player_y = m_d->next_y;
		data->player_x = m_d->next_x;
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
