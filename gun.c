#include "bonus/cub3d_bonus.h"

mlx_image_t **gun;

int x; int y;

void animate(void *conx)
{
	static int i;
	static int first;
	static mlx_image_t *pre;


	// if (first == 0 && i < 74)
	// {
	// 	if (i != 0)
	// 		gun[i - 1]->instances[0].enabled = false;
	// 	pre = gun[i]; 
	// 	i++;
	// 	if ( i == 74)puts("out");
	// }
	// else
	// {
	// 	first = 1;
		if (i == 44)
			i = 0;
		// printf("%d\n", (i - 1) % 74);
		if (pre)
		pre->instances[0].enabled = false;
		gun[i]->instances[0].enabled = true;
		pre = gun[i];
		i++;
	// }
}

void ft_exit( void *param){
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))	
		exit(0);
}

int main()
{
	int n; 
	void *conx;
	char str[30];

	conx= mlx_init(WIDTH, HEIGHT, "gun", false);
	
	mlx_loop(conx);
}