#include "bonus/cub3d_bonus.h"

void cursor_hook(double xpos, double ypos, void* param)
{
    mlx_t* mlx = (mlx_t*)param;
    printf("Mouse position: (%.0f, %.0f)\n", xpos, ypos);
}

int main(void)
{
    mlx_t* mlx = mlx_init(WIDTH_3D, HEIGHT_3D, "Cub3d", false);
    mlx_cursor_hook(mlx, cursor_hook, mlx); // Pass mlx as param
    mlx_loop(mlx);
}


// mlx_image_t **gun;

// int x; int y;

// void animate(void *conx)
// {
// 	static int i;
// 	static int first;
// 	static mlx_image_t *pre;


// 	// if (first == 0 && i < 74)
// 	// {
// 	// 	if (i != 0)
// 	// 		gun[i - 1]->instances[0].enabled = false;
// 	// 	pre = gun[i]; 
// 	// 	i++;
// 	// 	if ( i == 74)puts("out");
// 	// }
// 	// else
// 	// {
// 	// 	first = 1;
// 		if (i == 44)
// 			i = 0;
// 		// printf("%d\n", (i - 1) % 74);
// 		if (pre)
// 		pre->instances[0].enabled = false;
// 		gun[i]->instances[0].enabled = true;
// 		pre = gun[i];
// 		i++;
// 	// }
// }

// void ft_exit( void *param){
// 	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))	
// 		exit(0);
// }

// int main()
// {
// 	int n; 
// 	void *conx;
// 	char str[30];

// 	conx= mlx_init(WIDTH_3D, HEIGHT_3D, "gun", false);
// 	n = 3;
// 	gun = malloc(sizeof(mlx_image_t *) * 44);
// 	mlx_texture_t *tex;
// 	int j = 1;
// 	for ( int i =0; i < 44; i++, j+=5)
// 	{
// 		if ( j > 9)
//             n = 2;
//         if (j > 99) 
//             n = 1;
// 		sprintf(str, "reload/%.*s%d.png",n , "000", j);
// 		tex = mlx_load_png(str);
// 		gun[i] = mlx_texture_to_image(conx, tex);
// 		mlx_delete_texture(tex);
// 	if ( i == 0)
// 	{
// 		x = (WIDTH_3D  / 2) - (gun[0]->width /2 );
// 		y = (HEIGHT_3D ) - (gun[0]->height);
// 		// y = 0;
// 	}
// 		mlx_image_to_window(conx, gun[i], x, y);
// 		gun[i]->instances->enabled = false;
// 	}
// 	printf("%d\t%d\n", gun[0]->width, gun[0]->height);
// 	mlx_loop_hook(conx, ft_exit, conx);
// 		// gun[0] = mlx_texture_to_image(conx, mlx_load_png("textures/test.png"));
// 	// mlx_image_to_window(conx, gun[0], x / 2 , y / 2);
// 	mlx_loop_hook(conx, animate, conx);
// 	// sleep(5);
// 	mlx_loop(conx);
// }