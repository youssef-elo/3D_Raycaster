#include "bonus/cub3d_bonus.h"

mlx_image_t **gun;

int x; int y;

void animate(void *conx)
{
	static int i;
	static int first;


	if (first == 0 && i < 50)
	{
		// if (i == 50)
		// {
		// 	first = 1;
		// 	return ;
		// }
		mlx_image_to_window(conx, gun[i], x, y);
		if (i != 0)
			gun[i - 1]->instances[0].enabled = false;
		// printf("%d\n", i);
		i++;
	}
	else
	{
		// puts("there");
		// printf("second %d\n", i);
		i = i % 50;
		first = 1;
		gun[i]->instances[0].enabled = false;
		i++;
		i = i % 50;
		gun[i]->instances[0].enabled = true;
	}
	
}

void ft_exit( void *param){
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))	
		exit(0);
}

int main()
{
	gun = malloc(sizeof(mlx_image_t *) * 50);
	void *conx= mlx_init(WIDTH_3D, HEIGHT_3D, "gun", false);
	char str[30];
	mlx_texture_t *tex;
	int j = 1;
	for ( int i =0; i < 50; i++, j+=2)
	{
		sprintf(str, "render/00%d.png", j);
		tex = mlx_load_png(str);
		gun[i] = mlx_texture_to_image(conx, tex);
		mlx_delete_texture(tex);
	}
	x = (WIDTH_3D  - gun[0]->width)  /2;
	printf("%d")
	x = (HEIGHT_3D  - gun[0]->height) / 2 ;
	mlx_loop_hook(conx, ft_exit, conx);
		// gun[0] = mlx_texture_to_image(conx, mlx_load_png("textures/test.png"));
	// mlx_image_to_window(conx, gun[0], x / 2 , y / 2);
	mlx_loop_hook(conx, animate, conx);
	// sleep(5);
	mlx_loop(conx);
}