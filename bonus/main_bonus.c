#include "cub3d_bonus.h"

int	main(int argc, char **argv){
	data_t			data;
	mlx_data_t		mlx_data;
	map_context_h	p_data;

	parsing(argc , argv, &p_data);
	ft_bzero(&data, sizeof(data_t));
	link_parsing(&data, &p_data, &mlx_data);
	pre_compute(&data);
	free_parsing(&p_data);
	put_images(&data);
	set_hooks(&data);
	mlx_loop(mlx_data.mlx);
}
