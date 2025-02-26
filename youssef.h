#ifndef YOUSSEF_H
 # define YOUSSEF_H

#include "./MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "hamza.h"
#include <strings.h>

#define PI 3.141592653589793
#define FOV 1.1519
#define NUMBER_OF_RAYS 320



// 8 21
#define TILE_SIZE 80
#define WIDTH 21 * TILE_SIZE
#define HEIGHT 8 * TILE_SIZE
#define BPP sizeof(int32_t)

typedef struct mlx_data_s{
	mlx_t *mlx;
	mlx_image_t *view;
	mlx_image_t *empty;
	mlx_image_t *wall;
} mlx_data_t;

typedef struct data_s{
	mlx_data_t *mlx_data;
	double player_x;
	double player_y;
	double view_angle;
	char **map;
    int *rays;

} data_t;

#endif